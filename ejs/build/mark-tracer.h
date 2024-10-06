/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

/*
 * Tracer
 *
 *  process_edge, process_edge_XXX
 *    If the destination node is not marked, mark it and process the
 *    destination node. XXX is specialised version for type XXX.
 *  scan_XXX
 *    Scan static structure XXX.
 *  process_node_XXX
 *    Scan object of type XXX in the heap.  Move it if nencessary.
 */

#ifdef CXX_TRACER_CBV
class MarkTracer : public BaseTracer<MarkTracer> {
 public:
  static constexpr bool is_single_object_scanner = false;
  static constexpr bool is_hcg_mutator = true;
  static void process_edge(JSValue v);
  static void process_edge(void *p);
  static void process_edge_function_frame(JSValue v) {
    void *p = jsv_to_function_frame(v);
    process_edge(p);
  }
  template <typename T>
  static void process_edge_ex_JSValue_array(T p_, size_t n) {
    JSValue *p = (JSValue *) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return;
    for (size_t i = 0; i < n; i++)
      process_edge(p[i]);
  }
  template <typename T>
  static void process_edge_ex_ptr_array(T p_, size_t n) {
    void **p = (void **) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return;
    for (size_t i = 0; i < n; i++)
      if (p[i] != NULL)
	process_edge(p[i]);
  }
  static void process_node_JSValue_array(JSValue *p) { LOG_ASSERT_NOT_REACHED(); }
  static void process_node_ptr_array(void **p) { LOG_ASSERT_NOT_REACHED(); }

  static void process_weak_edge(JSValue v) {}
  static void process_weak_edge(void *p) {}
  static bool is_marked_cell(void *p) {
    return ::is_marked_cell(p);
  }
};
#else /* CXX_TRACER_CBV */
#ifdef CXX_TRACER_RV
class RVTracer : public MarkTracer<RVTracer> {
public:
  static constexpr bool is_single_object_scanner = false;
  static constexpr bool is_hcg_mutator = true;
  static JSValue process_edge(JSValue v);
  static void *process_edge(void *p);
  static JSValue process_edge_function_frame(JSValue v) {
    void *p = jsv_to_function_frame(v);
    return (JSValue) (uintjsv_t) (uintptr_t) process_edge(p);
  }
  template <typename T>
  static T process_edge_ex_JSValue_array(T p_, size_t n) {
    JSValue *p = (JSValue *) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return (T) p;
    for (size_t i = 0; i < n; i++)
      p[i] = process_edge(p[i]);
    return (T) p;
  }
  template <typename T>
  static T process_edge_ex_ptr_array(T p_, size_t n) {
    void **p = (void **) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return (T) p;
    for (size_t i = 0; i < n; i++)
      if (p[i] != NULL)
	p[i] = process_edge(p[i]);
    return (T) p;
  }
  static JSValue *process_node_JSValue_array(JSValue *p) { LOG_ASSERT_NOT_REACHED(); }
  static void **process_node_ptr_array(void **p) { LOG_ASSERT_NOT_REACHED(); }

  static JSValue process_weak_edge(JSValue v) { return v; }
  static void *process_weak_edge(void *p) { return p; }
  static bool is_marked_cell(void *p) {
    return ::is_marked_cell(p);
  }
};
#else /* CXX_TRACER_RV */
template <void(*live_object_hook)(void*)>
class RefMarkTracer : public BaseTracer<RefMarkTracer<live_object_hook> > {
 public:
  static constexpr bool is_single_object_scanner = false;
  static constexpr bool is_hcg_mutator = true;
  static void process_edge(JSValue &v);
  static void process_edge(void *&p);
  static void process_edge_function_frame(JSValue &v) {
    FunctionFrame *frame = jsv_to_function_frame(v);
    process_edge(reinterpret_cast<void *&>(frame));
    v = (JSValue) (uintjsv_t) (uintptr_t) frame;
  }
  template<typename T>
  static void process_edge_ex_JSValue_array(T &p_, size_t n) {
    JSValue *&p = (JSValue *&) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return;
    for (size_t i = 0; i < n; i++)
      process_edge(p[i]);
  }
  template<typename T>
  static void process_edge_ex_ptr_array(T &p_, size_t n) {
    void **&p = (void **&) p_;
    if (in_js_space(p) && ::test_and_mark_cell(p))
      return;
    for (size_t i = 0; i < n; i++)
      if (p[i] != NULL)
	process_edge(p[i]);
  }
  template <typename T>
  static void process_node_JSValue_array(T &p) { LOG_ASSERT_NOT_REACHED(); }
  template <typename T>
  static void process_node_ptr_array(T &p) { LOG_ASSERT_NOT_REACHED(); }

  static void process_weak_edge(JSValue &v) {}
  static void process_weak_edge(void *&p) {}
  static bool is_marked_cell(void *p) {
    return ::is_marked_cell(p);
  }
};
#endif /* CXX_TRACER_RV */
#endif /* CXX_TRACER_CBV */

#if defined CXX_TRACER_CBV
typedef MarkTracer DefaultTracer;
template<void(*live_object_hook)(void*)>
using DefaultTracerWithHook = DefaultTracer;
#elif defined(CXX_TRACER_RV)
typedef RVTracer DefaultTracer;
template<void(*live_object_hook)(void*)>
using DefaultTracerWithHook = DefaultTracer;
#else /* CXX_TRACER_CBV/RV */
typedef RefMarkTracer<nullptr> DefaultTracer;
template<void(*live_object_hook)(void*)>
using DefaultTracerWithHook = RefMarkTracer<live_object_hook>;
#endif /* CXX_TRACER_CBV/RV */

#ifdef CXX_TRACER_CBV
void MarkTracer::process_edge(void *p)
{
  assert(p != NULL);

  if (in_js_space(p) && ::test_and_mark_cell(p))
    return;

#ifdef MARK_STACK
  mark_stack_push((uintptr_t) p);
#else /* MARK_STACK */
  process_node<MarkTracer>((uintptr_t) p);
#endif /* MARK_STACK */
}

void MarkTracer::process_edge(JSValue v)
{
  if (is_fixnum(v) || is_special(v))
    return;
  void *p = (void *)(uintptr_t) clear_ptag(v);
  assert(p != NULL);

  process_edge(p);
}
#else /* CXX_TRACER_CBV */
#ifdef CXX_TRACER_RV
void *RVTracer::process_edge(void *p)
{
  assert(p != NULL);

  if (in_js_space(p) && ::test_and_mark_cell(p))
    return p;

#ifdef MARK_STACK
  mark_stack_push((uintptr_t) p);
#else /* MARK_STACK */
  process_node<RVTracer>((uintptr_t) p);
#endif /* MARK_STACK */
  return p;
}

JSValue RVTracer::process_edge(JSValue v)
{
  if (is_fixnum(v) || is_special(v))
    return v;

  void *p = (void *)(uintptr_t) clear_ptag(v);
  assert(p != NULL);

  if (in_js_space(p) && ::test_and_mark_cell(p))
    return v;

#ifdef MARK_STACK
  mark_stack_push((uintptr_t) p);
#else /* MARK_STACK */
  process_node<RVTracer>((uintptr_t) p);
#endif /* MARK_STACK */
  return v;
}
#else /* CXX_TRACER_RV */
template <void(*live_object_hook)(void*)>
void RefMarkTracer<live_object_hook>::process_edge(void *&p)
{
  assert(p != NULL);

  if (in_js_space(p) && ::test_and_mark_cell(p))
    return;

  if (live_object_hook != nullptr)
    live_object_hook(p);

#ifdef MARK_STACK
  BaseTracer<RefMarkTracer>::mark_stack_push((uintptr_t) p);
#else /* MARK_STACK */
  process_node<RefMarkTracer>((uintptr_t) p);
#endif /* MARK_STACK */
}

template <void(*live_object_hook)(void*)>
void RefMarkTracer<live_object_hook>::process_edge(JSValue &v)
{
  if (is_fixnum(v) || is_special(v))
    return;

  void *p = (void *)(uintptr_t) clear_ptag(v);
  assert(p != NULL);

  if (in_js_space(p) && ::test_and_mark_cell(p))
    return;

  if (live_object_hook != nullptr)
    live_object_hook(p);

#ifdef MARK_STACK
  BaseTracer<RefMarkTracer>::mark_stack_push((uintptr_t) p);
#else /* MARK_STACK */
  process_node<RefMarkTracer>((uintptr_t) p);
#endif /* MARK_STACK */
}
#endif /* CXX_TRACER_RV */
#endif /* CXX_TRACER_CBV */

