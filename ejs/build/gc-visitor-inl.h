#include <type_traits>

#define ACCEPTOR template<typename Tracer>

#if defined(HC_SKIP_INTERNAL) || defined(ALLOC_SITE_CACHE)
STATIC PropertyMap* get_transition_dest(PropertyMap *pm);
#endif /* HC_SKIP_INTERNAL || ALLOC_SITE_CACHE */

template<typename T>
static inline void *&
cast_process_edge_arg(T *&x) { return reinterpret_cast<void *&>(x); }
static inline JSValue &cast_process_edge_arg(JSValue &x) { return x; }

#ifdef CXX_TRACER_RV

template <typename Tracer, typename T>
static inline void process_edge_wrapper(T &x) {
  x = Tracer::process_edge(x);
}
template <typename Tracer, typename T>
static inline void process_weak_edge_wrapper(T &x) {
  x = Tracer::process_weak_edge(x);
}
template <typename Tracer, typename T>
static inline void process_edge_ex_JSValue_array_wrapper(T &x, size_t s) {
  x = Tracer::process_edge_ex_JSValue_array(x, s);
}
template <typename Tracer, typename T>
static inline void process_edge_ex_ptr_array_wrapper(T &x, size_t s) {
  x = Tracer::process_edge_ex_ptr_array(x, s);
}
template<typename Tracer>
static inline void process_edge_function_frame_wrapper(JSValue &x) {
  x = Tracer::process_edge_function_frame(x);
}

#define PROCESS_EDGE(x)						\
  process_edge_wrapper<Tracer>(cast_process_edge_arg(x))
#define PROCESS_WEAK_EDGE(x)					\
  process_weak_edge_wrapper<Tracer>(cast_process_edge_arg(x))
#define PROCESS_EDGE_EX_JSVALUE_ARRAY(x,s)				\
  process_edge_ex_JSValue_array_wrapper<Tracer>((x),(s))
#define PROCESS_EDGE_EX_PTR_ARRAY(x,s)					\
  process_edge_ex_ptr_array_wrapper<Tracer>((x), (s))
#define PROCESS_EDGE_FUNCTION_FRAME(x)					\
  process_edge_function_frame_wrapper<Tracer>(reinterpret_cast<JSValue &>(x))

#else /* CXX_TRACER_RV */

#define PROCESS_EDGE(x) Tracer::process_edge(cast_process_edge_arg(x))

#define PROCESS_WEAK_EDGE(x) Tracer::process_weak_edge(cast_process_edge_arg(x))

#define PROCESS_EDGE_EX_JSVALUE_ARRAY(x,s)				\
  Tracer::process_edge_ex_JSValue_array((x),(s))

#define PROCESS_EDGE_EX_PTR_ARRAY(x,s)					\
  Tracer::process_edge_ex_ptr_array(reinterpret_cast<void **&>(x),(s))

#define PROCESS_EDGE_FUNCTION_FRAME(x)					\
  Tracer::process_edge_function_frame(reinterpret_cast<JSValue &>(x))
#endif /* CXX_TRACER_RV */

ACCEPTOR STATIC_INLINE void process_node(uintptr_t ptr);
ACCEPTOR STATIC_INLINE void process_node(cell_type_t type, uintptr_t ptr);
ACCEPTOR STATIC void scan_Context(Context *context);
ACCEPTOR STATIC void scan_function_table_entry(FunctionTable *p);
ACCEPTOR STATIC void scan_stack(JSValue* stack, int sp, int fp);
ACCEPTOR STATIC void scan_string_table(StrTable *p);
ACCEPTOR STATIC void scan_roots(Context *ctx);
ACCEPTOR STATIC void weak_clear_StrTable(StrTable *table);
#ifdef WEAK_SHAPE_LIST
ACCEPTOR STATIC void weak_clear_shape_recursive(PropertyMap *pm);
ACCEPTOR STATIC void weak_clear_shapes();
#endif /* WEAK_SHAPE_LIST */
#ifdef HC_SKIP_INTERNAL
ACCEPTOR STATIC void weak_clear_property_map_recursive(PropertyMap *pm);
ACCEPTOR STATIC void weak_clear_property_maps();
#endif /* HC_SKIP_INTERNAL */
ACCEPTOR STATIC void weak_clear(Context *ctx);

/********* Tracer *********/

class CoreTracer {
 public:
#ifdef MARK_STACK
#define MARK_STACK_SIZE 1000 * 1000
  static uintptr_t mark_stack[MARK_STACK_SIZE];
  static int mark_stack_ptr;
#endif /* MARK_STACK */
};

template<typename Tracer>
class BaseTracer : protected CoreTracer {
 public:
#ifdef MARK_STACK
  static void mark_stack_push(uintptr_t ptr){
    assert(mark_stack_ptr < MARK_STACK_SIZE);
    mark_stack[mark_stack_ptr++] = ptr;
  }
  static uintptr_t mark_stack_pop(void) {
    return mark_stack[--mark_stack_ptr];
  }
  static bool mark_stack_is_empty(void) {
    return mark_stack_ptr == 0;
  }
  static void process_mark_stack(void) {
    while (!mark_stack_is_empty()) {
      uintptr_t ptr = mark_stack_pop();
      process_node<Tracer>(ptr);
    }
  }
#else /* MARK_STACK */
  static void process_mark_stack(void) {}
#endif /* MARK_STACK */
};

#ifdef MARK_STACK
uintptr_t CoreTracer::mark_stack[MARK_STACK_SIZE];
int CoreTracer::mark_stack_ptr;
#endif /* MARK_STACK */

/******** Scanner *********/

extern JSValue *gc_root_stack[];
extern int gc_root_stack_ptr;
#ifdef ALLOC_SITE_CACHE
extern void alloc_site_update_info(JSObject *p);
#endif /* ALLOC_SITE_CACHE */

class NodeScanner {
  ACCEPTOR static void scan_object_properties(JSObject *p) {
    Shape *os;
#ifndef COPY
    os = p->shape;
#endif /* !COPY */

    /* 1. shape */
    PROCESS_EDGE(p->shape);

#ifdef COPY
    os = p->shape;
#endif /* COPY */

    /* 2. embedded propertyes */
    int n_extension = os->n_extension_slots;
    size_t actual_embedded = os->n_embedded_slots - (n_extension == 0 ? 0 : 1);
    for (size_t i = os->pm->n_special_props; i < actual_embedded; i++)
      PROCESS_EDGE(p->eprop[i]);

    /* 3. extension */
    if (n_extension != 0)
      PROCESS_EDGE_EX_JSVALUE_ARRAY(p->eprop[actual_embedded],
				    os->pm->n_props - actual_embedded);
  }
  
 public:
  ACCEPTOR static void scan_String(StringCell *p) {}
  ACCEPTOR static void scan_Flonum(FlonumCell *p) {}
  ACCEPTOR static void scan_SimpleObject(JSObject *p) {
    scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_Array(JSObject *p) {
    JSValue *a_body = get_array_ptr_body(p);
    if (a_body != NULL) {
      size_t a_size = get_array_ptr_size(p);
      size_t a_length = (size_t) number_to_double(get_array_ptr_length(p));
      size_t len = a_length < a_size ? a_length : a_size;
      PROCESS_EDGE_EX_JSVALUE_ARRAY(p->eprop[array_body_index], len);
      PROCESS_EDGE(p->eprop[array_length_index]);
    }	
    scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_Function(JSObject *p) {
    /* FunctionTable *ftentry = function_ptr_table_entry(p);
     * scan_function_table_entry(ftentry);
     *    All function table entries are scanned through Context
     */
    PROCESS_EDGE(p->eprop[function_environment_index]);
    scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_Builtin(JSObject *p) {
    scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_BoxedNumber(JSObject *p) {
      PROCESS_EDGE(p->eprop[number_object_value_index]);
      scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_BoxedString(JSObject *p) {
    PROCESS_EDGE(p->eprop[string_object_value_index]);
    scan_object_properties<Tracer>(p);
  }
  ACCEPTOR static void scan_BoxedBoolean(JSObject *p) {
    assert(is_boolean(get_number_object_ptr_value(p)));
    scan_object_properties<Tracer>(p);
  }
#ifdef USE_REGEXP
  ACCEPTOR static void scan_Regexp(JSObject *p) {
    scan_object_properties<Tracer>(p);
  }    
#endif /* USE_REGEXP */
  ACCEPTOR static void scan_Iterator(Iterator *p) {
    if (p->size > 0)
      PROCESS_EDGE_EX_JSVALUE_ARRAY(p->body, p->size);
  }
  ACCEPTOR static void scan_Prop(JSValue *p) {
    Tracer::process_node_JSValue_array(p);
  }
  ACCEPTOR static void scan_ArrayData(JSValue *p) {
    Tracer::process_node_JSValue_array(p);
  }    
  ACCEPTOR static void scan_ByteArray(char *p) {}
  ACCEPTOR static void scan_FunctionFrame(FunctionFrame *p) {
    if (p->prev_frame != NULL)
      PROCESS_EDGE(p->prev_frame);
    PROCESS_EDGE(p->arguments);
    for (int i = 0; i < p->nlocals; i++)
      PROCESS_EDGE(p->locals[i]);
#ifdef DEBUG
    assert(p->locals[p->nlocals - 1] == JS_UNDEFINED);
#endif /* DEBUG */
  }
  ACCEPTOR static void scan_StrCons(StrCons *p) {
    PROCESS_WEAK_EDGE(p->str);
    if (p->next != NULL)
      PROCESS_EDGE(p->next);
  }
  ACCEPTOR static void scan_Hashtable(HashTable *p) {
    if (p->transitions != NULL)
      PROCESS_EDGE(p->transitions);
    for (int i = 0; i < p->n_props; i++)
      PROCESS_EDGE(p->entry[i].key);
  }
  ACCEPTOR static void scan_TransitionTable(TransitionTable *p) {
    for (int i = 0; i < p->n_transitions; i++) {
      if (p->transition[i].key != JS_UNDEFINED) {
	PROCESS_EDGE(p->transition[i].key);
#ifdef HC_SKIP_INTERNAL
	PROCESS_WEAK_EDGE(p->transition[i].pm);
#else /* HC_SKIP_INTERNAL */
	PROCESS_EDGE(p->transition[i].pm);
#endif /* HC_SKIP_INTERNAL */
      }
    }
  }
  ACCEPTOR static void scan_PropertyMap(PropertyMap *p) {
    PROCESS_EDGE(p->map);
    if (p->u.ord.shapes != NULL)
      PROCESS_EDGE(p->u.ord.shapes);/* Shape
				     * (always keep the largest one) */
    PROCESS_EDGE(p->__proto__);
  }
  ACCEPTOR static void scan_Shape(Shape *p) {
    PROCESS_EDGE(p->pm);
    if (p->next != NULL) {
#ifdef WEAK_SHAPE_LIST
      PROCESS_WEAK_EDGE(p->next);
#else /* WEAK_SHAPE_LIST */
      PROCESS_EDGE(p->next);
#endif /* WEAK_SHAPE_LIST */
    }
  }
  ACCEPTOR static void scan_Unwind(UnwindProtect *p) {
    if (p->prev != NULL)
      PROCESS_EDGE(p->prev);
    if (p->lp != NULL)
      PROCESS_EDGE(p->lp);
  }
#if defined(HC_SKIP_INTERNAL) || defined(WEAK_SHAPE_LIST)
  ACCEPTOR static void scan_PropertyMapList(PropertyMapList *p) {
    PROCESS_WEAK_EDGE(p->pm);
    if (p->next != NULL)
      PROCESS_WEAK_EDGE(p->next);
  }
#endif /* HC_SKIP_INTERNAL || WEAK_SHAPE_LIST */
};  
  
ACCEPTOR STATIC_INLINE void process_node(uintptr_t ptr)
{
  process_node<Tracer>(space_get_cell_type(ptr), ptr);
}

ACCEPTOR STATIC_INLINE void process_node(cell_type_t type, uintptr_t ptr) {
  switch (type) {
  case CELLT_STRING:
    NodeScanner::scan_String<Tracer>((StringCell *) ptr);
    return;
  case CELLT_FLONUM:
    NodeScanner::scan_Flonum<Tracer>((FlonumCell *) ptr);
    return;
  case CELLT_SIMPLE_OBJECT:
    NodeScanner::scan_SimpleObject<Tracer>((JSObject *) ptr);
    return;
  case CELLT_ARRAY:
    NodeScanner::scan_Array<Tracer>((JSObject *) ptr);
    return;
  case CELLT_FUNCTION:
    NodeScanner::scan_Function<Tracer>((JSObject *) ptr);
    return;
  case CELLT_BUILTIN:
    NodeScanner::scan_Builtin<Tracer>((JSObject *) ptr);
    return;
  case CELLT_BOXED_NUMBER:
    NodeScanner::scan_BoxedNumber<Tracer>((JSObject *) ptr);
    return;
  case CELLT_BOXED_STRING:
    NodeScanner::scan_BoxedString<Tracer>((JSObject *) ptr);
    return;
  case CELLT_BOXED_BOOLEAN:
    NodeScanner::scan_BoxedBoolean<Tracer>((JSObject *) ptr);
    return;
#ifdef USE_REGEXP
  case CELLT_REGEXP:
    NodeScanner::scan_Regexp<Tracer>((JSObject *) ptr);
    return;
#endif /* USE_REGEXP */
  case CELLT_ITERATOR:
    NodeScanner::scan_Iterator<Tracer>((Iterator *) ptr);
    return;
  case CELLT_PROP:
    NodeScanner::scan_Prop<Tracer>((JSValue *) ptr);
    return;
  case CELLT_ARRAY_DATA:
    NodeScanner::scan_ArrayData<Tracer>((JSValue *) ptr);
    return;
  case CELLT_BYTE_ARRAY:
    NodeScanner::scan_ByteArray<Tracer>((char *) ptr);
    return;
  case CELLT_FUNCTION_FRAME:
    NodeScanner::scan_FunctionFrame<Tracer>((FunctionFrame *) ptr);
    return;
  case CELLT_STR_CONS:
    NodeScanner::scan_StrCons<Tracer>((StrCons *) ptr);
    return;
  case CELLT_TRANSITIONS:
    NodeScanner::scan_TransitionTable<Tracer>((TransitionTable *) ptr);
    return;
  case CELLT_HASHTABLE:
    NodeScanner::scan_Hashtable<Tracer>((HashTable *) ptr);
    return;
  case CELLT_PROPERTY_MAP:
    NodeScanner::scan_PropertyMap<Tracer>((PropertyMap *) ptr);
    return;
  case CELLT_SHAPE:
    NodeScanner::scan_Shape<Tracer>((Shape *) ptr);
    return;
  case CELLT_UNWIND:
    NodeScanner::scan_Unwind<Tracer>((UnwindProtect *) ptr);
    return;
#if defined(HC_SKIP_INTERNAL) || defined(WEAK_SHAPE_LIST)
  case CELLT_PROPERTY_MAP_LIST:
    NodeScanner::scan_PropertyMapList<Tracer>((PropertyMapList *) ptr);
    return;
#endif /* HC_SKIP_INTERNAL || WEAK_SHAPE_LIST */
  default:
    LOG_ASSERT_NOT_REACHED();
  }
}
  
ACCEPTOR STATIC void scan_Context(Context *context)
{
  PROCESS_EDGE(context->global);
  /* function table is a static data structure
   *   Note: spreg.cf points to internal address of the function table.
   */
  {
    FunctionTable *p;
    for (p = context->function_table; p->insns != NULL; ++p)
      scan_function_table_entry<Tracer>(p);
  }
  PROCESS_EDGE(context->spreg.lp);
  PROCESS_EDGE(context->spreg.a);
  PROCESS_EDGE(context->spreg.err);

  if (context->exhandler_stack_top != NULL)
    PROCESS_EDGE(context->exhandler_stack_top);
  PROCESS_EDGE(context->lcall_stack);

  /* process stack */
  scan_stack<Tracer>(context->stack, context->spreg.sp, context->spreg.fp);

#if defined(HC_SKIP_INTERNAL) || defined(WEAK_SHAPE_LIST)
  PROCESS_WEAK_EDGE(context->property_map_roots);
#endif /* HC_SKIP_INTERNAL || WEAK_SHAPE_LIST */
}

ACCEPTOR STATIC void scan_function_table_entry(FunctionTable *p)
{
  /* trace constant pool */
  {
    JSValue *constant_pool = p->constants;
    size_t n_constants = p->n_constants;
    size_t i;
    for (i = 0; i < n_constants; i++)
      PROCESS_EDGE(constant_pool[i]);
  }

#ifdef ALLOC_SITE_CACHE
  /* scan Allocation Sites and update */
  for (int i = 0; i < p->n_insns; i++) {
    AllocSite *as = &(INSN_CACHE(p->index, i).alloc_site);
    if (as->shape != NULL) {
      if (Tracer::is_hcg_mutator) {
	Shape *os = as->shape;
	while (((os->n_enter - os->n_leave) << 3) < os->n_enter) {
	  /* This map is tentative for objects allocated in this site.
	   * If destination for objects allocated in this site is a single,
	   * we can skip this map.
	   * Note: pm->n_transitions cannot be used.
	   */
	  PropertyMap *pm = os->pm;
	  HashTransitionIterator iter = createHashTransitionIterator(pm->map);
	  HashTransitionCell *cell;
	  Shape *next_os = NULL;
	  while (nextHashTransitionCell(pm->map, &iter, &cell) != FAIL) {
	    PropertyMap *next_pm = hash_transition_cell_pm(cell);
	    for (Shape *p = next_pm->u.ord.shapes; p != NULL; p = p->next) {
	      if (p->alloc_site == as) {
		if (next_os == NULL)
		  next_os = p;
		else
		  /* multiple outgoing edges */
		  goto BREAK_WHILE;
	      }
	    }
	  }
	  if (next_os == NULL)
	    break;
	  os = next_os;
	}
      BREAK_WHILE:
	if (as->shape != os) {
	  as->pm = os->pm;
#ifdef DUMP_HCG
	  as->shape->is_cached = 0;
#endif /* DUMP_HCG */
	  as->shape = NULL;
	  for (Shape *p = as->pm->u.ord.shapes; p != NULL; p = p->next) {
	    if (p->alloc_site == as &&
		p->n_embedded_slots == as->pm->n_props) {
	      as->shape = p;
#ifdef DUMP_HCG
	      as->shape->is_cached = 1;
#endif /* DUMP_HCG */
	      PROCESS_EDGE(as->shape);
	      break;
	    }
	  }
	} else
	  PROCESS_EDGE(as->shape);
      } else
	PROCESS_EDGE(as->shape);
    }
    if (as->pm != NULL)
      PROCESS_EDGE(as->pm);
  }
#elif defined(DUMP_HCG) || defined(LOAD_HCG)
  for (int i = 0; i < p->n_insns; i++) {
    AllocSite *as = &INSN_CACHE(p->index, i).alloc_site;
    if (as->shape != NULL)
      PROCESS_EDGE(as->shape);
    if (as->pm != NULL)
      PROCESS_EDGE(as->pm);
  }
#endif /* ALLOC_SITE_CACHE || DUMP_HCG || LOAD_HCG */


#ifdef INLINE_CACHE
  /* scan Inline Cache */
  {
    int i;
    for (i = 0; i < p->n_insns; i++) {
      InlineCache *ic = &(INSN_CACHE(p->index, i).inl_cache);
      if (ic->pm != NULL) {
        PROCESS_WEAK_EDGE(ic->pm);
	if (ic->prop_name != JS_EMPTY)
	  PROCESS_WEAK_EDGE(ic->prop_name);
#ifdef PROTO_IC
	if (ic->owner != JS_EMPTY)
	  PROCESS_WEAK_EDGE(ic->owner);
#endif /* PROTO_IC */
      }
    }
  }
#endif /* INLINE_CACHE */
}

ACCEPTOR STATIC void scan_stack(JSValue* stack, int sp, int fp)
{
  while (1) {
    while (sp >= fp) {
      PROCESS_EDGE(stack[sp]);
      sp--;
    }
    if (sp < 0)
      return;
    fp = stack[sp--]; /* FP */
    PROCESS_EDGE_FUNCTION_FRAME(stack[sp--]); /* LP */
    sp--; /* PC */
    sp--; /* CF (function table entries are scanned as a part of context) */
  }
}

ACCEPTOR STATIC void scan_string_table(StrTable *p)
{
  StrCons **vec = p->obvector;
  size_t length = p->size;
  size_t i;

  for (i = 0; i < length; i++)
    if (vec[i] != NULL)
      PROCESS_EDGE(vec[i]);
}

ACCEPTOR STATIC void scan_roots(Context *ctx)
{
  int i;

  /*
   * global variables
   */
  {
    struct global_constant_objects *gconstsp = &gconsts;
    JSValue *p;
    for (p = (JSValue *) gconstsp; p < (JSValue *) (gconstsp + 1); p++)
      PROCESS_EDGE(*p);
  }
  {
    struct global_property_maps *gpmsp = &gpms;
    PropertyMap **p;
    for (p = (PropertyMap **) gpmsp; p < (PropertyMap **) (gpmsp + 1); p++)
      PROCESS_EDGE(*p);
  }
  {
    struct global_object_shapes *gshapesp = &gshapes;
    Shape** p;
    for (p = (Shape **) gshapesp; p < (Shape **) (gshapesp + 1); p++)
      PROCESS_EDGE(*p);
  }

  /* function table: do not trace.
   *                 Used slots should be traced through Function objects
   */

  /* string table */
  scan_string_table<Tracer>(&string_table);

  /*
   * Context
   */
  scan_Context<Tracer>(ctx);

  /*
   * GC_PUSH'ed
   */
  for (i = 0; i < gc_root_stack_ptr; i++)
    PROCESS_EDGE(*(gc_root_stack[i]));

#ifdef HC_PROF
  /*
   * PropertyMap
   */
  {
    for (struct root_property_map *e = root_property_map;
	 e != NULL; e = e->next)
      PROCESS_EDGE(e->pm);
  }
#endif /* HC_PROF */
}

/*
 * Clear pointer field to StringCell whose mark bit is not set.
 * Unlink the StrCons from the string table.  These StrCons's
 * are collected in the next collection cycle.
 */
ACCEPTOR STATIC void weak_clear_StrTable(StrTable *table)
{
  size_t i;
  for (i = 0; i < table->size; i++) {
    StrCons ** p = table->obvector + i;
    while (*p != NULL) {
      StringCell *cell = jsv_to_normal_string((*p)->str);
      if (!Tracer::is_marked_cell(cell)) {
        (*p)->str = JS_UNDEFINED;
        *p = (*p)->next;
      } else {
        PROCESS_EDGE(*p);
        PROCESS_EDGE((*p)->str);
        Tracer::process_mark_stack();
        p = &(*p)->next;
      }
    }
  }
}

#ifdef WEAK_SHAPE_LIST
ACCEPTOR STATIC void weak_clear_shape_recursive(PropertyMap *pm)
{
#ifdef VERBOSE_GC_SHAPE
#defien PRINT(x...) printf(x)
#else /* VERBOSE_GC_SHAPE */
#define PRINT(x...)
#endif /* VERBOSE_GC_SHAPE */

  {
    Shape **p;
    for (p = &pm->u.ord.shapes; *p != NULL; ) {
      if (Tracer::is_marked_cell(*p)) {
	PROCESS_EDGE(*p);
	Tracer::process_mark_stack();
        p = &(*p)->next;
      } else {
        Shape *skip = *p;
        *p = skip->next;
#ifdef DEBUG
        PRINT("skip %p emb: %d ext: %d\n",
              skip, skip->n_embedded_slots, skip->n_extension_slots);
        skip->next = NULL;  /* avoid Black->While check failer */
#endif /* DEBUG */
      }
    }
  }

  HashTransitionIterator iter = createHashTransitionIterator(pm->map);
  HashTransitionCell *cell;
  while (nextHashTransitionCell(pm->map, &iter, &cell) != FAIL)
    weak_clear_shape_recursive<Tracer>(hash_transition_cell_pm(cell));

#undef PRINT /* VERBOSE_GC_SHAPE */
}

ACCEPTOR STATIC void weak_clear_shapes()
{
  PropertyMapList **pp;
  for (pp = &the_context->property_map_roots; *pp != NULL;) {
    PropertyMapList *e = *pp;
    if (Tracer::is_marked_cell(e->pm)) {
      PROCESS_EDGE(e);
      Tracer::process_mark_stack();
      *pp = e;
      weak_clear_shape_recursive<Tracer>(e->pm);
      pp = &e->next;
    } else
      *pp = (*pp)->next;
  }
}
#endif /* WEAK_SHAPE_LIST */

#if defined(HC_SKIP_INTERNAL) || defined(ALLOC_SITE_CACHE)
/*
 * Get the only transision from internal node.
 */
STATIC PropertyMap* get_transition_dest(PropertyMap *pm)
{
  HashTransitionIterator iter = createHashTransitionIterator(pm->map);
  HashTransitionCell *p;

  while(nextHashTransitionCell(pm->map, &iter, &p) != FAIL) {
    PropertyMap *ret = hash_transition_cell_pm(p);
    return ret;
  }
  LOG_ASSERT_NOT_REACHED();
  return NULL;
}
#endif /* HC_SKIP_INTERNAL || ALLOC_SITE_CACHE */

#ifdef HC_SKIP_INTERNAL

ACCEPTOR STATIC void weak_clear_property_map_recursive(PropertyMap *pm)
{
  int n_transitions = 0;

#ifdef VERBOSE_HC
#define PRINT_HC1(fmt, pm) do {			\
    char buf[1000];				\
    sprint_property_map(buf, pm);		\
    printf(fmt, buf);				\
  } while (0)
#define PRINT_HC2(fmt, pm1, pm2) do {		\
    char buf1[1000], buf2[1000];		\
    sprint_property_map(buf1, pm1);		\
    sprint_property_map(buf2, pm2);		\
    printf(fmt, buf1, buf2);			\
  } while (0)
#else /* VERBOSE_HC */
#define PRINT_HC1(fmt, pm)
#define PRINT_HC2(fmt, pm1, pm2)
#endif /* VERBOSE_HC */

  assert(Tracer::is_marked_cell(pm));

  HashTransitionIterator iter = createHashTransitionIterator(pm->map);
  HashTransitionCell *p;
  while(nextHashTransitionCell(pm->map, &iter, &p) != FAIL) {
    PropertyMap *next = hash_transition_cell_pm(p);
    /*
     * If the next node is
     *   0. not reused PM
     *   1. not strongly reachable and
     *   2. outgoing edge is exactly 1,
     * then, the node is an internal node to be eliminated.
     */
    while ((next->flags & PM_FLAG_REUSE) == 0 &&
	   !Tracer::is_marked_cell(next) && next->n_transitions == 1) {
      PRINT_HC2("skip PropertyMap %s from %s\n", next, pm);
      PropertyMap *next_next = get_transition_dest(next);
      next = next_next;
    }
    if ((next->flags & PM_FLAG_REUSE) == 0 &&
	!Tracer::is_marked_cell(next) && next->n_transitions == 0) {
      hash_transition_cell_delete(p);
      PRINT_HC1("delete tip of a branch %s\n", next);
      continue;
    }
    n_transitions++;
    PRINT_HC2("preserve PropertyMap %s from %s\n", next, pm);

#ifdef HC_SKIP_UNPOPULAR
    if ((next->flags & PM_FLAG_REUSE) == 0 &&
	next->n_transitions == 1 &&
	((next->n_enter - next->n_leave) << 3) < next->n_enter)
      pm_set_intermediate(next);
#endif /* HC_SKIP_UNPOPULAR */

    hash_transition_cell_pm(p) = next;
    /* Resurrect if it is branching node or terminal node */
    PROCESS_EDGE(hash_transition_cell_pm(p));
#if (!defined(THREADED)) && (!defined(LISP2))
    /* XXX: This code is maybe only for copy GC */
    next = hash_transition_cell_pm(p);
#endif /* (!defined(THREADED)) && (!defined(LISP2)) */
    Tracer::process_mark_stack();
    weak_clear_property_map_recursive<Tracer>(next);
  }
  pm->n_transitions = n_transitions;

#undef PRINT_HC1
#undef PRINT_HC2
}

ACCEPTOR STATIC void weak_clear_property_maps()
{
  PropertyMapList **pp;
  for (pp = &the_context->property_map_roots; *pp != NULL; ) {
    PropertyMap *pm = (*pp)->pm;
    while(!Tracer::is_marked_cell(pm) && pm->n_transitions == 1)
      pm = get_transition_dest(pm);
    if (!Tracer::is_marked_cell(pm) && pm->n_transitions == 0)
      *pp = (*pp)->next;
    else {
      PROCESS_EDGE(*pp);
      PROCESS_EDGE((*pp)->pm);
      Tracer::process_mark_stack();
      pm = (*pp)->pm;
      weak_clear_property_map_recursive<Tracer>(pm);
      pp = &(*pp)->next;
    }
  }
}
#endif /* HC_SKIP_INTERNAL */

#ifdef INLINE_CACHE
ACCEPTOR STATIC void weak_clear_inline_cache(Context *ctx)
{
  FunctionTable *p;
  int i = 0;
  for (p = ctx->function_table; p->insns != NULL; ++p, ++i) {
    for (int j = 0; j < p->n_insns; j++) {
      InlineCache *ic = &(INSN_CACHE(i, j).inl_cache);
      if (ic->pm != NULL && !Tracer::is_marked_cell(ic->pm)) {
	ic->pm = NULL;
	ic->prop_name = JS_EMPTY;
#ifdef PROTO_IC
	ic->owner = JS_EMPTY;
#endif /* PROTO_IC */
      }
    }
  }
}
#endif /* INLINE_CACHE */

ACCEPTOR STATIC void weak_clear(Context *ctx)
{
#ifdef HC_SKIP_INTERNAL
  /* !!! Do weak_clear_property_map first. This may resurrect some objects. */
  weak_clear_property_maps<Tracer>();
#endif /* HC_SKIP_INTERNAL */
#ifdef WEAK_SHAPE_LIST
  weak_clear_shapes<Tracer>();
#endif /* WEAK_SHAPE_LIST */
  weak_clear_StrTable<Tracer>(&string_table);
#ifdef INLINE_CACHE
  weak_clear_inline_cache<Tracer>(ctx);
#endif /* INLINE_CACHE */

  /* clear cache in the context */
  the_context->exhandler_pool = NULL;
}
