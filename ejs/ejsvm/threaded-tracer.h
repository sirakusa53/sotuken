/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifdef CXX_TRACER_CBV
#error "Threaded tracer does not except macro; CXX_TRACER_CBV."
#endif /* CXX_TRACER_CBV */
#ifdef CXX_TRACER_RV
#error "Threaded tracer does not except macro; CXX_TRACER_RV."
#endif /* CXX_TRACER_RV */

// Defined at threaded-functions-inl.h
static void thread_reference(void **ref);

class ThreadTracer {
public:
  static constexpr bool is_single_object_scanner = true;
  static constexpr bool is_hcg_mutator = false;
  static void process_edge(JSValue &v) {
    if (is_fixnum(v) || is_special(v))
      return;

    uintjsv_t ptr = clear_ptag(v);
    assert((void *) ptr != NULL);

#ifdef USE_EMBEDDED_INSTRUCTION
    /* Constant table of embedded instruction is allocated on FLASH. */
    if (in_mbed_flash((void *) ptr))
      return;
#endif /* USE_EMBEDDED_INSTRUCTION */

    v = (JSValue) ptr;

    assert(in_js_space((void *) v));

    thread_reference((void **) &v);
  }
  static void process_edge(void *&p) {
    assert(p != NULL);

    assert(in_js_space((void *) p));

    thread_reference(&p);
  }
  static void process_edge_function_frame(JSValue &v) {
    if ((void *) v == NULL)
      return;

    assert(in_obj_space((void *) v));

    thread_reference((void **) &v);
  }
  template <typename T>
  static void process_edge_ex_JSValue_array(T &p, size_t n) {
    if ((void *) p == NULL)
      return;

    assert(in_obj_space((void *) p));

    thread_reference((void **) &p);
  }
  template <typename T>
  static void process_edge_ex_ptr_array(T &p, size_t n) {
    if ((void *) p == NULL)
      return;
    assert(in_js_space((void *) p));

    thread_reference((void **) &p);
  }
  static void process_node_JSValue_array(JSValue *p) {
    if (p == NULL)
      return;

    assert(in_js_space((void *) p));
    assert(!in_hc_space((void *) p));

    header_t *hdrp = payload_to_header(p);
    size_t payload_granules = hdrp->size - HEADER_GRANULES;
    size_t slots = payload_granules <<
      (LOG_BYTES_IN_GRANULE - LOG_BYTES_IN_JSVALUE);
    for (size_t i = 0; i < slots; i++)
      process_edge(p[i]);
  }
  static void process_node_ptr_array(void **&p) {
    if (p == NULL)
      return;

    assert(gc_phase == PHASE_FWDREF);
    assert(!in_js_space((void *) &p) || in_hc_space((void *) &p));

    assert(in_js_space((void *) p));
    assert(in_hc_space((void *) p));

    header_t *hdrp = payload_to_header(p);
#ifdef JONKERS
    size_t payload_granules = hdrp->size - HEADER_GRANULES;
#else /* JONKERS */
    size_t payload_granules = hdrp->hc.size_lo - HEADER_GRANULES;
#endif /* JONKERS */
    size_t slots = payload_granules * (BYTES_IN_GRANULE / sizeof(void *));
    for (size_t i = 0; i < slots; i++) {
      if (p[i] != NULL)
        thread_reference(&p[i]);
    }
  }
  static void process_weak_edge(JSValue &v) { process_edge(v); }
  static void process_weak_edge(void *&p) { process_edge(p); }

  static void process_mark_stack(void) {}
};

