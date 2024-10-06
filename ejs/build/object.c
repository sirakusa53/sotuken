/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN extern
#include "header.h"

#ifdef VERBOSE_HC
int sprint_property_map(char *start, PropertyMap *pm);
#endif /* VERBOSE_HC */

static
JSValue get_system_prop(JSValue obj, JSValue name) __attribute__((unused));

static PropertyMap *extend_property_map(Context *ctx, PropertyMap *prev,
                                        JSValue prop_name,  Attribute attr);
static void object_grow(Context *ctx, JSObject *p, size_t new_size);
static void object_grow_shape(Context *ctx, JSValue obj, Shape *os);
static JSValue object_get___proto__(JSValue obj);

#ifdef HC_PROF
static void hcprof_add_root_property_map(PropertyMap *pm);
#endif /* HC_PROF */

#ifdef INLINE_CACHE
static void inline_cache_install(InlineCache *ic, JSValue target, JSValue owner,
                                 JSValue name, int index);
#ifdef PROTO_IC
static void inline_cache_invalidate_all_prototype_cache();
int prototype_ic_epoch;
#endif /* PROTO_IC */
#endif /* INLINE_CACHE */

/* Profiling */
static inline void hcprof_enter_shape(Shape *os)
{
#if defined(HC_PROF) || defined(HC_SKIP_INTERNAL)
  {
    PropertyMap *pm = os->pm;
    pm->n_enter++;
  }
#endif /* HC_PROF || HC_SKIP_INTERNAL */
#if defined (HC_PROF) || defined(ALLOC_SITE_CACHE)
  os->n_enter++;
#endif /* HC_PROF || ALLOC_SITE_CACHE */
#ifdef AS_PROF
  if (os->alloc_site != NULL)
    os->alloc_site->transition++;
#endif /* AS_PROF */
}

static inline void hcprof_leave_shape(Shape *os)
{
#if defined(HC_PROF) || defined(HC_SKIP_INTERNAL)
  {
    PropertyMap *pm = os->pm;
    pm->n_leave++;
  }
#endif /* HC_PROF || HC_SKIP_INTERNAL */
#if defined(HC_PROF) || defined(ALLOC_SITE_CACHE)
  os->n_leave++;
#endif /* HC_PROF || ALLOC_SITE_CACHE */
}

#define HC_PROF_ENTER_SHAPE(os) hcprof_enter_shape(os)
#define HC_PROF_LEAVE_SHAPE(os) hcprof_leave_shape(os)

#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG) || defined(LOAD_HCG)
static inline void alloc_site_loc(Context *ctx,
                                  AllocSite *as, int *fun_no, int *insn_no)
{
  int i;
  if (as == NULL) {
    *fun_no = -1;
    *insn_no = -1;
    return;
  }
#ifdef DUMP_HCG
  if (as->builtin_id != 0) {
    *fun_no = -1;
    *insn_no = as->builtin_id;
    return;
  }
#endif /* DUMP_HCG */
  for (i = 0; i < ctx->nfuncs; i++) {
    FunctionTable *p = ctx->function_table + i;
    int j;
    for (j = 0; j < p->n_insns; j++) {
      if (as == &(INSN_CACHE(i, j).alloc_site)) {
        *fun_no = i;
        *insn_no = j;
        return;
      }
    }
  }
}
#endif /* ALLOC_SITE_CACHE || DUMP_HCG || LOAD_HCG */

/* PROPERTY OPERATION **************************************************/

/**
 * obtains the index of a property of a JSObject
 * If the specified property does not exist, returns -1.
 *
 * Note that if hash_get_with_attribute returns HASH_GET_SUCCESS,
 * the property map of the object contains either the index
 * of JSValue array (as a fixnum) or the pointer to the next property map.
 * These two cases can be distinguished by investigating the ``transition
 * bit'' of the obtained attribute.  For the latter case, the pointer to
 * the next property map is returned through ``next_map'' parameter if
 * it is not NULL.
 */
static int prop_index(JSObject *p, JSValue name, Attribute *attrp,
                      PropertyMap **next_map)
{
  HashData retv;
  int result;
  Attribute attr;

  result = hash_get_with_attribute(p->shape->pm->map, name, &retv, &attr);
  if (result == HASH_GET_FAILED) {
    if (next_map != NULL)
      *next_map = NULL;
    return -1;
  }
  if (is_transition(attr)) {
    if (next_map != NULL)
      *next_map = retv.u.pm;
    return -1;
  } else {
    *attrp = attr;
    return retv.u.index;
  }
}

/**
 * Initialise a pre-defined property
 * NOTE: Pre-defined properties should be registered in the map and
 *       object should be large enough for them to be embedded.
 *       Thus, no memory allocation takes place.
 */
static void init_prop(JSObject *p, JSValue name, JSValue value)
{
  Attribute attr;
  int index = prop_index(p, name, &attr, NULL);

  assert(index != -1);
  assert(index < p->shape->n_embedded_slots);

  p->eprop[index] = value;
}


#ifdef VERBOSE_SET_PROP
#define PRINT(x...) printf(x)
#else /* VERBOSE_SET_PROP */
#define PRINT(x...)
#endif /* VERBOSE_SET_PROP */

static PropertyMap *
object_add_prop_get_next_pm(Context *ctx, PropertyMap *current_pm,
                            JSValue name, PropertyMap *next_pm,
                            Attribute att, int is_builtin)
{
  if (next_pm == NULL) {
    next_pm = extend_property_map(ctx, current_pm, name, att);
#ifdef DUMP_HCG
    next_pm->is_builtin = is_builtin;
#endif /* DUMP_HCG */
    PRINT("  new property (new PM %p is created)\n", next_pm);
  } else
#if defined(HC_SKIP_INTERNAL) && defined(HC_SKIP_UNPOPULAR)
    /* If the next property map is transient, take the next */
    while (is_pm_intermediate(next_pm)) {
      HashTransitionIterator iter =
        createHashTransitionIterator(next_pm->map);
      HashTransitionCell *cell;
      int ret __attribute__((unused));
      assert(next_pm->n_transitions == 1);
      ret = nextHashTransitionCell(next_pm->map, &iter, &cell);
      assert(ret != FAIL);
      next_pm = hash_transition_cell_pm(cell);
    }
#endif /* HC_SKIP_INTERNAL && HC_SKIP_UNPOPULAR */
  PRINT("  new property (cached PM %p is used)\n", next_pm);
  return next_pm;
}

static Shape *
object_add_prop_get_next_os(Context *ctx, Shape *current_os,
                            PropertyMap *next_pm)
{
  /* 2. Find the shape that is compatible to the current shape. */
  size_t n_embedded = current_os->n_embedded_slots;
  size_t n_extension = current_os->n_extension_slots;
  Shape *next_os = NULL;
#ifdef PROTO_IC
  int is_proto = current_os->is_proto;
#else /* PROTO_IC */
  int is_proto = 0;
#endif /* PROTO_IC */

  /* 2.1 compute new size of extension array */
  size_t need_slots = next_pm->n_props;
  if (n_embedded + n_extension - (n_extension == 0 ? 0 : 1) < need_slots)
    n_extension = need_slots - (n_embedded - 1);
  PRINT("  finding shape for PM %p (n_props = %d) EM/EX %zu %zu\n",
        next_pm, next_pm->n_props, n_embedded, n_extension);

  /* 2.2 Find from the shape list of the next PM. */
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
  next_os = property_map_find_shape(next_pm, n_embedded, n_extension,
                                    current_os->alloc_site, is_proto);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
  next_os = property_map_find_shape(next_pm, n_embedded, n_extension, is_proto);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */

  /* 2.3 If there is not compatible shape, create it. */
  if (next_os == NULL) {
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
    next_os = new_object_shape(ctx, DEBUG_NAME("(extend)"), next_pm,
                               n_embedded, n_extension,
                               current_os->alloc_site, is_proto);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
    next_os = new_object_shape(ctx, DEBUG_NAME("(extend)"), next_pm,
                               n_embedded, n_extension, is_proto);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
    PRINT("  create new shape %p EM/EX %zu %zu\n",
          next_os, n_embedded, n_extension);
  }

  return next_os;
}

static int object_add_prop(Context *ctx, JSValue obj, JSValue name,
                           Attribute att, int is_builtin, PropertyMap *next_pm)
{
  /* Current map does not have the property named `name'.
   * Remark: Hidden class related objects must be GC_PUSHed because
   *         pointers between them are regarded weak.
   * Note: Only properties added during initialisation has special
   *       attributes. Thus, now there is no risk of failure due to
   *       conflict of attribute. */
  Shape *current_os = object_get_shape(obj);
  int index = current_os->pm->n_props;
  Shape *next_os;

  GC_PUSH2(obj, current_os);
  /* 1. Find the next PM */
  next_pm = object_add_prop_get_next_pm(ctx, current_os->pm,
                                        name, next_pm, att, is_builtin);
  /* 2. Find a suitable Shape */
  next_os = object_add_prop_get_next_os(ctx, current_os, next_pm);
  /* 3. Change the shape of object if necessary and installs the new shape.
   *    This may cause reallocation of the extension array. */
  object_grow_shape(ctx, obj, next_os);
  GC_POP2(current_os, obj);
#ifdef PROTO_IC
  if (next_os->is_proto)
    inline_cache_invalidate_all_prototype_cache();
#endif /* PROTO_IC */
  /* 4. Return `index'.  It should be equal to the number of properties
   *    registered to the previous property map.
   *    Note: The current property map may have extra properties to skip
   *          intermediate property map in the transition graph. */
  return index;
}

/**
 * Set an object's property value with its attribute.
 * If the property is not defined in the object, it registers
 * the property to the property map.
 * set_prop fails if the object has a property of the same name
 * with a conflicting attribute.
 */
#ifdef INLINE_CACHE
void set_prop_(Context *ctx, JSValue obj, JSValue name, JSValue v,
               Attribute att, int is_builtin, InlineCache *ic)
#else /* INLINE_CACHE */
void set_prop_(Context *ctx, JSValue obj, JSValue name, JSValue v,
               Attribute att, int is_builtin)
#endif /* INLINE_CACHE */
{
  PropertyMap *next_pm;
  int index;
  Attribute attr_unused;

  assert(is_jsobject(obj));
  assert(is_string(name));

  PRINT("set_prop shape %p PM %p prop %s (%" PRIJSValue ") %s\n",
        object_get_shape(obj), object_get_shape(obj)->pm,
        string_to_cstr(name), name, is_builtin ? "(builtin)" : "");

  if (!is_builtin) {
    /* __proto__ is stored in the dedicated field of property map */
    if (name == gconsts.g_string___proto__) {
      JSValue default___proto__ = object_get_shape(obj)->pm->__proto__;
      if (default___proto__ == v)
        return;

      if (is_undefined(v))
        v = JS_NULL;
      else if (!is_jsobject(v))
        return;
#ifdef PROTO_IC
      GC_PUSH3(v, name, obj);
      object_promote_to_prototype(ctx, v);
      inline_cache_invalidate_all_prototype_cache();
      GC_POP3(obj, name, v);
#endif /* PROTO_IC */
    } else if (name == gconsts.g_string_prototype) {
      if (is_undefined(v))
        v = JS_NULL;
      else if (!is_jsobject(v))
        return;
    }
  }

  index = prop_index(jsv_to_jsobject(obj), name, &attr_unused, &next_pm);
  if (index == -1) {
    GC_PUSH3(obj, name, v);
    index = object_add_prop(ctx, obj, name, att, is_builtin, next_pm);
    GC_POP3(v, name, obj);
  }

  if (name == gconsts.g_string___proto__)
    object_get_shape(obj)->pm->__proto__ = JS_EMPTY;
  
#ifdef INLINE_CACHE
  inline_cache_install(ic, obj, obj, name, index);
#endif /* INLINE_CACHE */
  object_set_prop(obj, index, v);

#undef PRINT  /* VERBOSE_SET_PROP */
}

/**
 * Get property of the object. This does not follow the property chain.
 * If the object does not have the property, it returns JS_EMPTY.
 */
#ifdef INLINE_CACHE
JSValue get_prop_with_ic(JSValue obj, JSValue target, JSValue name, InlineCache *ic)
#else /* INLINE_CACHE */
JSValue get_prop(JSValue obj, JSValue name)
#endif /* INLINE_CACHE */
{
  int index;
  Attribute attr;

  assert(is_jsobject(obj));

  if (name == gconsts.g_string___proto__)
    return object_get___proto__(obj);

  index = prop_index(jsv_to_jsobject(obj), name, &attr, NULL);
  if (index == -1 || is_system_prop(attr))
    return JS_EMPTY;

#ifdef INLINE_CACHE
  inline_cache_install(ic, target, obj, name, index);
#endif /* INLINE_CACHE */
  return object_get_prop(obj, index);
}

static JSValue get_system_prop(JSValue obj, JSValue name)
{
  int index;
  Attribute attr;

  assert(is_jsobject(obj));

  index = prop_index(jsv_to_jsobject(obj), name, &attr, NULL);
  if (index == -1)
    return JS_EMPTY;
  assert(is_system_prop(attr));  /* or system property is overwritten */
  return object_get_prop(obj, index);
}

static JSValue get_array_element_no_proto(JSValue array, cint index)
{
  assert(is_array(array));
  if (0 <= index &&
      index < number_to_double(get_jsarray_length(array)) &&
      ((uintjsv_t) index) < get_jsarray_size(array))
    return get_jsarray_body(array)[index];
  return JS_EMPTY;
}

/**
 * Search for the property by following the prototype chain if necessary.
 * If the property is not defined in any object on the chain, it returns
 * JS_UNDEFINED.
 */
#ifdef INLINE_CACHE
JSValue get_prop_prototype_chain_with_ic(JSValue obj, JSValue name,
                                         InlineCache *ic)
#else /* INLINE_CACHE */
JSValue get_prop_prototype_chain(JSValue obj, JSValue name)
#endif /* INLINE_CACHE */
{
  const JSValue target_obj = obj;

  while (is_jsobject(obj)) {
#if defined(INLINE_CACHE) && defined(PROTO_IC)
    JSValue ret = get_prop_with_ic(obj, target_obj, name, ic);
#else /* INLINE_CACHE && PROTO_IC */
    JSValue ret = get_prop(obj, name);
#endif /* INLINE_CACHE && PROTO_IC */
    if (ret != JS_EMPTY)
      return ret;
    if (is_array(obj)) {
      JSValue num = string_to_number(NULL, name);
      if (is_fixnum(num))
        ret = get_array_element_no_proto(obj, fixnum_to_cint(num));
      if (ret != JS_EMPTY)
        return ret;
    }
#ifdef IC_PROF
    if (ic != NULL && obj == target_obj)
      ic->proto++;
#endif /* IC_PROF */
    obj = object_get___proto__(obj);
  }
  return JS_UNDEFINED;
}

static JSValue object_get___proto__(JSValue obj)
{
  JSObject *p;
  JSValue __proto__;
  int index;
  Attribute attr;
  assert(is_jsobject(obj));

  p = jsv_to_jsobject(obj);
  __proto__ = p->shape->pm->__proto__;
  if (__proto__ != JS_EMPTY)
    return __proto__;

  index = prop_index(p, gconsts.g_string___proto__, &attr, NULL);
  assert(index != -1);
  
  return object_get_prop(obj, index);
}

/* OBJECT CONSTRUCTOR **************************************************/

/**
 * Allocate memory for JSObject.
 * Initialise common and property fields of JSObject.
 */
static JSObject *allocate_jsobject(Context *ctx, const char *name, Shape *os,
                                   HTag htag)
{
  size_t n_embedded = os->n_embedded_slots;
  size_t size = sizeof(JSObject) + sizeof(JSValue) * n_embedded;
  JSObject *p;
  size_t i;

  GC_PUSH(os);
  p = (JSObject *) gc_malloc(ctx, size, htag.v);
  p->shape = os;
  for (i = 0; i < n_embedded; i++)
    p->eprop[i] = JS_EMPTY;

#ifdef DEBUG
  p->name = name;
#endif /* DEBUG */

  HC_PROF_ENTER_SHAPE(os);
  GC_POP(os);

  return p;
}

JSValue new_simple_object(Context *ctx, const char *name, Shape *os)
{
  JSObject *p;

  assert(os->pm->n_special_props == OBJECT_SPECIAL_PROPS);

  p = allocate_jsobject(ctx, name, os, HTAG_SIMPLE_OBJECT);

  assert(Object_num_builtin_props +
         Object_num_double_props + Object_num_gconsts_props == 0);

  return ptr_to_normal_simple_object(p);
}

JSValue new_array_object(Context *ctx, const char *name, Shape *os, size_t size)
{
  JSObject *p;
  JSValue *array_data;
  size_t i;

  assert(os->pm->n_special_props == ARRAY_SPECIAL_PROPS);

  p = allocate_jsobject(ctx, name, os, HTAG_ARRAY);
  set_array_ptr_body(p, NULL);  /* tell GC not to follow this pointer */

  GC_PUSH(p);
  array_data =
    (JSValue *) gc_malloc(ctx, size * sizeof(JSValue), CELLT_ARRAY_DATA);
  for (i = 0; i < size; i++)
    array_data[i] = JS_UNDEFINED;

  set_array_ptr_body(p, array_data);
  set_array_ptr_size(p, size);
  set_array_ptr_length(p, cint_to_number(ctx, (cint) size));
  GC_POP(p);

  assert(Array_num_builtin_props +
         Array_num_double_props + Array_num_gconsts_props == 1);

  return ptr_to_normal_array(p);
}


JSValue new_function_object(Context *ctx, const char *name, Shape *os, int ft_index)
{
  JSObject *p;
  JSValue prototype;

  assert(os->pm->n_special_props == FUNCTION_SPECIAL_PROPS);

  GC_PUSH(os);
  prototype = new_simple_object(ctx, DEBUG_NAME("(prototype)"),
                                gshapes.g_shape_Object);
  GC_PUSH(prototype);
  p = allocate_jsobject(ctx, name, os, HTAG_FUNCTION);
  GC_POP2(prototype, os);

  set_function_ptr_table_entry(p, &(ctx->function_table[ft_index]));
  set_function_ptr_environment(p, get_lp(ctx));

  assert(Function_num_builtin_props +
         Function_num_double_props + Function_num_gconsts_props == 1);
  init_prop(p, gconsts.g_string_prototype, prototype);

  return ptr_to_normal_function(p);
}

JSValue new_builtin_object(Context *ctx, const char *name, Shape *os,
                           builtin_function_t cfun, builtin_function_t cctor,
                           int na)
{
  JSObject *p;

  assert(os->pm->n_special_props == BUILTIN_SPECIAL_PROPS);

  p = allocate_jsobject(ctx, name, os, HTAG_BUILTIN);

  set_builtin_ptr_body(p, cfun);
  set_builtin_ptr_constructor(p, cctor);
  set_builtin_ptr_nargs(p, na);

  assert(Builtin_num_builtin_props +
         Builtin_num_double_props + Builtin_num_gconsts_props == 0);

  return ptr_to_normal_builtin(p);
}

JSValue new_number_object(Context *ctx, const char *name, Shape *os, JSValue v)
{
  JSObject *p;

  assert(os->pm->n_special_props == NUMBER_SPECIAL_PROPS);
  assert(is_fixnum(v) || is_flonum(v));

  GC_PUSH(v);
  p = allocate_jsobject(ctx, name, os, HTAG_BOXED_NUMBER);
  GC_POP(v);

  set_number_object_ptr_value(p, v);

  assert(Number_num_builtin_props +
         Number_num_double_props + Number_num_gconsts_props == 0);

  return ptr_to_normal_number_object(p);
}

JSValue new_string_object(Context *ctx, const char *name, Shape *os, JSValue v)
{
  JSObject *p;

  assert(os->pm->n_special_props == STRING_SPECIAL_PROPS);
  assert(is_string(v));

  GC_PUSH(v);
  p = allocate_jsobject(ctx, name, os, HTAG_BOXED_STRING);
  GC_POP(v);

  set_string_object_ptr_value(p, v);

  assert(String_num_builtin_props +
         String_num_double_props + String_num_gconsts_props == 1);
  init_prop(p, gconsts.g_string_length,
            uint32_to_number(ctx, string_length(v)));

  return ptr_to_normal_string_object(p);
}


JSValue new_boolean_object(Context *ctx, const char *name, Shape *os, JSValue v)
{
  JSObject *p;

  assert(os->pm->n_special_props == STRING_SPECIAL_PROPS);
  assert(is_boolean(v));

  GC_PUSH(v);
  p = allocate_jsobject(ctx, name, os, HTAG_BOXED_BOOLEAN);
  GC_POP(v);

  set_boolean_object_ptr_value(p, v);

  return ptr_to_normal_boolean_object(p);
}

#ifdef USE_REGEXP
static int set_regexp_members(Context *ctx, JSValue re, char *pat, int flag);

JSValue new_regexp_object(Context *ctx, const char *name, Shape *os, char *pat, int flag)
{
  JSObject *p;
  JSValue ret;

  assert(os->pm->n_special_props == REX_SPECIAL_PROPS);

  p = allocate_jsobject(ctx, name, os, HTAG_REGEXP);

  /* pattern field is set in set_regexp_members */
  set_regexp_ptr_pattern(p, NULL);
  set_regexp_ptr_reg(p, 0);
  set_regexp_ptr_global(p, ((flag & F_REGEXP_GLOBAL) != 0));
  set_regexp_ptr_ignorecase(p, ((flag & F_REGEXP_IGNORE) != 0));
  set_regexp_ptr_multiline(p, ((flag & F_REGEXP_MULTILINE) != 0));
  set_regexp_ptr_lastindex(p, 0);

  assert(RegExp_num_builtin_props +
         RegExp_num_double_props + RegExp_num_gconsts_props == 0);

  ret = ptr_to_normal_regexp(p);

  if (set_regexp_members(ctx, ret, pat, flag) != SUCCESS)
    ret = JS_UNDEFINED;

  return ret;
}
#endif /* USE_REGEXP */

/* HIDDEN CLASS *******************************************************/

PropertyMap *new_property_map(Context *ctx, const char *name,
                              int n_special_props, int n_props,
                              int n_user_special_props,
                              JSValue __proto__, uint8_t flags)
{
  HashTable   *hash;
  PropertyMap *m;

  assert(ctx != NULL);

  GC_PUSH(__proto__);
  hash = hash_create(ctx, n_props);
  GC_PUSH(hash);
  m = (PropertyMap *) gc_malloc(ctx, sizeof(PropertyMap), CELLT_PROPERTY_MAP);
  GC_POP2(hash, __proto__);

  m->map          = hash;
  m->__proto__    = __proto__;
  m->n_props      = n_props;
  m->n_special_props = n_special_props;
  m->flags        = flags;
#ifdef HC_SKIP_INTERNAL
  m->n_transitions = 0;
#endif /* HC_SKIP_INTERNAL */

  GC_PUSH(m);
  /* setup hidden class graph */
  m->u.ord.shapes = NULL;

#if defined(HC_SKIP_INTERNAL) || defined(WEAK_SHAPE_LIST)
  /* register as a root of hidden class graph */
  if ((flags & PM_FLAG_ROOT)) {
    PropertyMapList *p =
      (PropertyMapList*) gc_malloc(ctx, sizeof(PropertyMapList),
                                   CELLT_PROPERTY_MAP_LIST);
    p->pm = m;
    p->next = ctx->property_map_roots;
    ctx->property_map_roots = p;
  }
#endif /* HC_SKIP_INTERNAL || WEAK_SHAPE_LIST */
  GC_POP(m);
  
#ifdef DEBUG
  m->name = name;
  m->n_user_special_props = n_user_special_props;
#endif /* DEBUG */
#if defined(HC_PROF) || defined(HC_SKIP_INTERNAL)
  m->n_enter = 0;
  m->n_leave = 0;
#endif /* HC_PROF || HC_SKIP_INTERNAL */
#ifdef HC_PROF
  /* Retain all HC for HCG_DUMP.
   * This can be inconvenient when dumping an optimized HCG as this
   * makes strong references to all root hidden classes, which may
   * prevent them from being removed.
   */
  if ((flags & PM_FLAG_ROOT))
    hcprof_add_root_property_map(m);
#ifdef DUMP_HCG
  if (ctx == NULL) {
    m->function_no = -1;
    m->insn_no = -1;
  } else {
    m->function_no = (int) (ctx->spreg.cf - ctx->function_table);
    m->insn_no = ctx->spreg.pc;
  }
  m->is_entry = 0;
  m->is_builtin = 0;
#endif /* DUMP_HCG */
  {
    static int last_id;
    m->id = ++last_id;
  }
#endif /* HC_PROF */
  
  return m;
}

/**
 * Create a new property map by extending an exispting property map
 * with a new property name. The index for the new property is the
 * next number to the largest used one.
 * Then, set up edges of the transition graph.
 */
static PropertyMap *extend_property_map(Context *ctx, PropertyMap *prev,
                                        JSValue prop_name,  Attribute attr)
{
  PropertyMap *m;
  int index = prev->n_props;
  JSValue __proto__;

  GC_PUSH2(prev, prop_name);

  /* 1. Create property map */
  if (prop_name == gconsts.g_string___proto__)
    __proto__ = JS_EMPTY;
  else
    __proto__ = prev->__proto__;
  m = new_property_map(ctx, DEBUG_NAME("(extended)"),
                       prev->n_special_props, prev->n_props + 1,
#ifdef DEBUG
                       prev->n_user_special_props,
#else /* DEBUG */
                       0,
#endif /* DEBUG */
                       __proto__, 0);
  GC_PUSH(m);

  /* 2. Copy existing entries */
#ifdef DEBUG
  {
    int n = hash_copy(ctx, prev->map, m->map);
    assert(n == prev->n_props - prev->n_special_props +
           prev->n_user_special_props);
  }
#else /* DEBUG */
  hash_copy(ctx, prev->map, m->map);
#endif /* DEBUG */

  /* 3. Add property */
  property_map_add_property_entry(ctx, m, prop_name, index, attr);
 
  /* 4. Create an edge from prev to new property map. */
  property_map_add_transition(ctx, prev, prop_name, m);

  GC_POP3(m, prop_name, prev);

#ifdef VERBOSE_HC
  {
    char buf[1000];
    sprint_property_map(buf, m);
    printf("HC-create extend %s\n", buf);
  }
#endif /* VERBOSE_HC */

  return m;
}

#ifdef LOAD_HCG
void property_map_install___proto__(PropertyMap *pm, JSValue __proto__)
{
  assert(pm->__proto__ == JS_EMPTY);
  assert((pm->flags & PM_FLAG_REUSE) == PM_FLAG_REUSE);
  pm->__proto__ = __proto__;
  HashTransitionIterator iter = createHashTransitionIterator(pm->map);
  HashTransitionCell *p;
  while (nextHashTransitionCell(pm->map, &iter, &p) != FAIL)
    property_map_install___proto__(hash_transition_cell_pm(p), __proto__);
}
#endif /* LOAD_HCG */

void property_map_add_property_entry(Context *ctx, PropertyMap *pm,
                                     JSValue name, uint32_t index,
                                     Attribute attr)
{
  hash_put_property(ctx, pm->map, name, index, attr);
}

void property_map_add_transition(Context *ctx, PropertyMap *pm,
                                 JSValue name, PropertyMap *dest)
{
#ifdef HC_SKIP_INTERNAL
  {
    uint16_t current_n_trans = pm->n_transitions;
    pm->n_transitions = PM_N_TRANS_UNSURE;  /* protect from GC */
    GC_PUSH(pm);
    hash_put_transition(ctx, pm->map, name, dest);
    GC_POP(pm);
    pm->n_transitions = current_n_trans + 1;
  }
#else /* HC_SKIP_INTERNAL */
  hash_put_transition(ctx, pm->map, name, dest);
#endif /* HC_SKIP_INTERNAL */
}

#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
Shape *property_map_find_shape(PropertyMap *pm, size_t n_embedded,
                               size_t n_extension, AllocSite *as, int is_proto)
{
  Shape *os;
  for (os = pm->u.ord.shapes; os != NULL; os = os->next) {
    if (os->n_embedded_slots == n_embedded &&
        os->n_extension_slots == n_extension &&
        os->alloc_site == as
#ifdef PROTO_IC
        && os->is_proto == is_proto
#endif /* PROTO_IC */
        )
      return os;
  }
  return NULL;
}
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
Shape *property_map_find_shape(PropertyMap *pm, size_t n_embedded,
                               size_t n_extension, int is_proto)
{
  Shape *os;
  for (os = pm->u.ord.shapes; os != NULL; os = os->next) {
    if (os->n_embedded_slots == n_embedded &&
        os->n_extension_slots == n_extension
#ifdef PROTO_IC
        && os->is_proto == is_proto
#endif /* PROTO_IC */
        )
      return os;
  }
  return NULL;
}
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */

#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
Shape *new_object_shape(Context *ctx, const char *name, PropertyMap *pm,
                        int num_embedded, int num_extension,
                        AllocSite *as, int is_proto)
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
Shape *new_object_shape(Context *ctx, const char *name, PropertyMap *pm,
                        int num_embedded, int num_extension, int is_proto)
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
{
  Shape *s;
  Shape **pp;

  assert(num_embedded > 0);

  GC_PUSH(pm);
  s = (Shape *) gc_malloc(ctx, sizeof(Shape), CELLT_SHAPE);
  GC_POP(pm);
  s->pm = pm;
  s->n_embedded_slots  = num_embedded;
  s->n_extension_slots = num_extension;
#ifdef PROTO_IC
  s->is_proto = is_proto;
#endif /* PROTO_IC */
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
  s->alloc_site = as;
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */

#if defined(PROTO_IC) && !defined(DUMP_HCG)
  if (!is_proto)
#endif /* PROTO_IC && !DUMP_HCG */
    {
      /* Insert `s' into the `shapes' list of the property map.
       * The list is sorted from more `n_embedded_slots' to less.
       */
      for (pp = &pm->u.ord.shapes; ; pp = &(*pp)->next) {
        Shape *p = *pp;
        if (p == NULL || p->n_embedded_slots < num_embedded) {
          s->next = *pp;
          *pp = s;
          break;
        }
      }
    }
#if defined(PROTO_IC) && !defined(DUMP_HCG)
  else
    s->next = NULL;
#endif /* PROTO_IC && !DUMP_HCG */

#if defined(HC_PROF) || defined(ALLOC_SITE_CACHE)
  s->n_enter = 0;
  s->n_leave = 0;
#endif /* HC_PROF || ALLOC_SITE_CACHE */
#ifdef AS_PROF
  s->n_alloc = 0;
#endif /* AS_PROF */
#ifdef DUMP_HCG
  s->is_cached = 0;
  s->population = NULL;
#endif /* DUMP_HCG */
#ifdef DEBUG
  s->name = name;
#endif /* DEBUG */

  return s;
}

static void object_grow(Context *ctx, JSObject *p, size_t new_size)
{
  Shape *os = p->shape;
  size_t current_size = os->n_extension_slots;
  int extension_index = os->n_embedded_slots - 1;
  
  if (current_size < new_size) {
    JSValue *extension;
    size_t i;
    GC_PUSH(p);
    extension = (JSValue *) gc_malloc(ctx, sizeof(JSValue) * new_size,
                                      CELLT_PROP);
    GC_POP(p);
    if (current_size == 0) {
      extension[0] = p->eprop[extension_index];
      i = 1;
    } else {
      JSValue *current_extension =
        jsv_to_extension_prop(p->eprop[extension_index]);
      for (i = 0; i < current_size; i++)
        extension[i] = current_extension[i];
    }
    for (; i < new_size; i++)
      extension[i] = JS_EMPTY;
    p->eprop[extension_index] = (JSValue) (uintjsv_t) (uintptr_t) extension;
#ifdef AS_PROF
    if (p->shape->alloc_site != NULL)
      p->shape->alloc_site->copy_words += current_size;
#endif /* AS_PROF */
  }
}

/**
 * Reallocate extension array if necessary.
 * Assign new shape to the object.
 */
static void object_grow_shape(Context *ctx, JSValue obj, Shape *os)
{
  size_t new_size;
  JSObject *p;

  p = jsv_to_jsobject(obj);

  GC_PUSH2(p, os);
  HC_PROF_LEAVE_SHAPE(p->shape);

  /* 1. Reallocate extension array if necessary. */
  new_size = os->n_extension_slots;
  object_grow(ctx, p, new_size);

  /* 2. Assign new shape */
  p->shape = os;

  HC_PROF_ENTER_SHAPE(os);
  GC_POP2(os, p);
}

#ifdef PROTO_IC
void object_promote_to_prototype(Context *ctx, JSValue obj)
{
  JSObject *p = jsv_to_jsobject(obj);
  Shape *os = p->shape;
  PropertyMap *pm = os->pm;
  Shape *proto_os;

  if (os->is_proto)
    return;

  HC_PROF_LEAVE_SHAPE(os);
  GC_PUSH(p);
#if defined(DUMP_HCG)
  proto_os = new_object_shape(ctx, DEBUG_NAME("(proto)"), pm,
                              os->n_embedded_slots, os->n_extension_slots,
                              os->alloc_site, 1);
#elif defined(ALLOC_SITE_CACHE)
  proto_os = new_object_shape(ctx, DEBUG_NAME("(proto)"), pm,
                              os->n_embedded_slots, os->n_extension_slots,
                              NULL, 1);
#else /* ALLOC_SITE_CACHE  */
  proto_os = new_object_shape(ctx, DEBUG_NAME("(proto)"), pm,
                              os->n_embedded_slots, os->n_extension_slots, 1);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
  p->shape = proto_os;
  HC_PROF_ENTER_SHAPE(proto_os);
  GC_POP(p);
}
#endif /* PROTO_IC */

#if defined(ALLOC_SITE_CACHE) || defined(LOAD_HCG)
static Shape *get_cached_shape(Context *ctx, AllocSite *as,
                               JSValue __proto__, int n_special)
{
  PropertyMap *pm;
#ifdef AS_PROF
  as->n_alloc++;
#endif /* AS_PROF */

  /* 1. Check availability */

  if (as == NULL || as->pm == NULL)
    return NULL;

  pm = as->pm;
  if (pm->__proto__ == __proto__)
    /* OK */;
  else if (pm->__proto__ == JS_EMPTY) {
#ifdef LOAD_HCG
    if ((pm->flags & PM_FLAG_REUSE) == PM_FLAG_REUSE) {
      /* First use of reused property map. Install prototype. */
      property_map_install___proto__(pm, __proto__);
    }
#endif /* LOAD_HCG */
    /* OK */;
  } else
    return NULL;

  assert(pm->n_special_props == n_special);

#ifdef ALLOC_SITE_CACHE
  /* 2. Create shape */
  if (as->shape == NULL) {
    size_t n_embedded = pm->n_props == 0 ? 1 : pm->n_props;
    as->shape = new_object_shape(ctx, DEBUG_NAME("(pre-transition)"),
                                 pm, n_embedded, 0, as, 0 /*not a prototype*/);
#ifdef DUMP_HCG
    as->shape->is_cached = 1;
#endif /* DUMP_HCG */
  }
#endif /* ALLOC_SITE_CACHE */
  
#ifdef AS_PROF
  if (as->shape != NULL)
    as->shape->n_alloc++;
#endif /* AS_PROF */

  return as->shape;
}
#endif /* ALLOC_SITE_CACHE || LOAD_HCG */

/* OBJECT CONSTRUCTOR  *********************************************/

/**
 * The most normal way to create an object.
 * Called from ``new'' instruction.
 */
JSValue create_simple_object_with_constructor(Context *ctx, JSValue ctor)
{
  JSValue prototype;
  assert(is_function(ctor));

  prototype = get_prop(ctor, gconsts.g_string_prototype);
  if (!is_jsobject(prototype))
    prototype = gconsts.g_prototype_Object;

  return create_simple_object_with_prototype(ctx, prototype);
}

JSValue create_simple_object_with_prototype(Context *ctx, JSValue prototype)
{
  JSValue obj;
  Shape *os;
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG) || defined(LOAD_HCG)
  AllocSite *as = &(INSN_CACHE(ctx->spreg.cf->index, ctx->spreg.pc).alloc_site);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG || LOAD_HCG */

#ifdef VERBOSE_NEW_OBJECT
#define PRINT(x...) printf(x)
#else /* VERBOSE_NEW_OBJECT */
#define PRINT(x...)
#endif /* VERBOSE_NEW_OBJECT */

  assert(is_jsobject(prototype));

  GC_PUSH(prototype);
#if defined(ALLOC_SITE_CACHE) || defined(LOAD_HCG)
  os = get_cached_shape(ctx, as, prototype, OBJECT_SPECIAL_PROPS);
  if (os == NULL)
#endif /* ALLOC_SITE_CACHE || LOAD_HCG */
    {
      JSValue retv;
      PropertyMap *pm;

#ifdef ALLOC_SITE_CACHE
  PRINT("new_obj @ %03td:%03d cache miss proto %" PRIJSValue " AS %p\n",
        ctx->spreg.cf - ctx->function_table, ctx->spreg.pc, prototype, as);
#else /* ALLOC_SITE_CACHE */
  PRINT("new_obj @ %03td:%03d cache miss proto %" PRIJSValue "\n",
        ctx->spreg.cf - ctx->function_table, ctx->spreg.pc, prototype);
#endif /* ALLOC_SITE_CACHE */
#ifdef DEBUG
  PRINT("  proto name = %s\n", jsv_to_jsobject(prototype)->name);
#endif /* DEBUG */

      /* 1. If `prototype' is valid, find the property map */
      retv = get_system_prop(prototype, gconsts.g_string___property_map__);
      if (retv != JS_EMPTY) {
        pm = jsv_to_property_map(retv);
        PRINT("PM found in proto %p OS[0] %p AS %p\n",
              pm, pm->shapes, pm->shapes->alloc_site);
      } else {
        /* 2. If there is not, create it. */
        int n_props = 0;
        int n_embedded = OBJECT_SPECIAL_PROPS + 1;/* at least 1 normal slot */
#ifdef PROTO_IC
        object_promote_to_prototype(ctx, prototype);
#endif /* PROTO_IC */
        pm = new_property_map(ctx, DEBUG_NAME("(new)"),
                              OBJECT_SPECIAL_PROPS, n_props,
                              OBJECT_USPECIAL_PROPS, prototype,
                              PM_FLAG_ROOT);
#ifdef DUMP_HCG
        pm->is_entry = 1;
#endif /* DUMP_HCG */
        GC_PUSH(pm);
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
        new_object_shape(ctx, DEBUG_NAME("(new)"), pm, n_embedded, 0, as, 0);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
        new_object_shape(ctx, DEBUG_NAME("(new)"), pm, n_embedded, 0, 0);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
        assert(Object_num_builtin_props +
               Object_num_double_props + Object_num_gconsts_props == 0);
        PRINT("create PM/OS PM %p OS %p AS %p\n",
              pm, pm->shapes, pm->shapes->alloc_site);

        /* 3. Create a link from the prototype object to the PM so that
         *    this function can find it in the following calls. */
        set_prop(ctx, prototype, gconsts.g_string___property_map__,
                 (JSValue) (uintjsv_t) (uintptr_t) pm, ATTR_SYSTEM);
        GC_POP(pm);
      }

      assert((pm->flags & PM_FLAG_ROOT) == PM_FLAG_ROOT);
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
      /* 4. serch for the shape whose allocation site is here */
      os = property_map_find_shape(pm, OBJECT_SPECIAL_PROPS + 1, 0, as, 0);
      /* 5. If there is not such a shape, create it */
      if (os == NULL)
        os = new_object_shape(ctx, DEBUG_NAME("(alloc site variant)"),
                              pm, OBJECT_SPECIAL_PROPS + 1, 0, as, 0);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
      /* 4. Obtain the shape of the PM. There should be a single shape,
       * if any, because the PM is an entrypoint. */
      os = pm->u.ord.shapes;
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */

#ifdef ALLOC_SITE_CACHE
      if (as != NULL && as->pm == NULL) {
        as->pm = pm;
#ifdef DUMP_HCG
        if (as->shape != NULL)
          as->shape->is_cached = 0;
#endif /* DUMP_HGC */
        as->shape = os;
#ifdef DUMP_HCG
        as->shape->is_cached = 1;
#endif /* DUMP_HCG */
      }
#endif /* ALLOC_SITE_CACHE */
    }

#ifdef ALLOC_SITE_CACHE
  GC_PUSH(os);
  obj = new_simple_object(ctx, DEBUG_NAME("inst:new"), os);
  GC_PUSH(obj);
  if (os->pm->__proto__ == JS_EMPTY)
    set_prop(ctx, obj, gconsts.g_string___proto__, prototype, ATTR_NONE);
  GC_POP2(obj, os);
#else /* ALLOC_SITE_CACHE */
  obj = new_simple_object(ctx, DEBUG_NAME("inst:new"), os);
#endif /* ALLOC_SITE_CACHE */
  GC_POP(prototype);
  return obj;

#undef PRINT
}

#ifdef ALLOC_SITE_CACHE
JSValue create_array_object(Context *ctx, const char *name, size_t size)
{
  JSValue obj;
  AllocSite *as = &(INSN_CACHE(ctx->spreg.cf->index, ctx->spreg.pc).alloc_site);
  Shape *os = get_cached_shape(ctx, as, gconsts.g_prototype_Array,
                               ARRAY_SPECIAL_PROPS);
  assert(os == NULL || (os->pm->flags & PM_FLAG_REUSE) == 0);
  if (os == NULL) {
    PropertyMap *pm = gshapes.g_shape_Array->pm;
    os = new_object_shape(ctx, DEBUG_NAME("(array)"),
                          pm, ARRAY_SPECIAL_PROPS + 1, 0, as, 0);
#ifdef DUMP_HCG
    pm->is_entry = 1;
#endif /* DUMP_HCG */
    if (as->pm == NULL) {
      as->pm = pm;
      as->shape = os;
    }
  }
  obj = new_array_object(ctx, name, os, size);
  return obj;
}
#endif /* ALLOC_SITE_CACHE */

#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG) || defined(LOAD_HCG)
void init_alloc_site(AllocSite *alloc_site)
{
  alloc_site->shape = NULL;
  alloc_site->pm = NULL;
#ifdef AS_PROF
  alloc_site->copy_words = 0;
  alloc_site->transition = 0;
  alloc_site->n_alloc = 0;
#endif /* AS_PROF */
#ifdef DUMP_HCG
  alloc_site->builtin_id = 0;
#endif /* DUMP_HCG */
}
#endif /* ALLOC_SITE_CACHE || DUMP_HCG || LOAD_HCG */

/* INLINE CACHE **************************************************/

#ifdef INLINE_CACHE
void init_inline_cache(InlineCache *ic)
{
  ic->pm = NULL;
  ic->prop_name = JS_EMPTY;
  ic->index = 0;
  ic->miss = 0;
#ifdef PROTO_IC
  ic->owner = JS_EMPTY;
#endif /* PROTO_IC */
#ifdef IC_PROF
  ic->count = 0;
  ic->hit = 0;
  ic->unavailable = 0;
  ic->install = 0;
  ic->proto = 0;
#endif /* IC_PROF */
}
#endif /* INLINE_CACHE */

#ifdef INLINE_CACHE
static void inline_cache_install(InlineCache *ic, JSValue target, JSValue owner,
                                 JSValue name, int index)
{
  assert(is_jsobject(target));
  assert(is_jsobject(owner));
  assert(is_string(name));

  if (ic == NULL || ic->pm != NULL)
    return;

  ic->pm = object_get_shape(target)->pm;
  ic->prop_name = name;
  ic->index = index;
  ic->miss = 0;
#ifdef PROTO_IC
  if (owner == target)
    ic->owner = JS_EMPTY;
  else
    ic->owner = owner;
  ic->epoch = prototype_ic_epoch;
#endif /* PROTO_IC */
#ifdef IC_PROF
  ic->install++;
#endif /* IC_PROF */
}
#endif /* INLINE_CACHE */

#ifdef PROTO_IC
static void inline_cache_invalidate_all_prototype_cache() {
  prototype_ic_epoch++;
}
#endif /* PROTO_IC */

/* ELEMENT ACCESS **************************************************/

/**
 * Obtain property of the object. It converts type of ``name'' if necessary.
 *   obj:  any type
 *   name: any type
 */
#ifdef INLINE_CACHE
JSValue get_object_prop(Context *ctx, JSValue obj, JSValue name,
			InlineCache *ic)
#else /* INLINE_CACHE */
  JSValue get_object_prop(Context *ctx, JSValue obj, JSValue name)
#endif /* INLINE_CACHE */
{
  if (!is_string(name)) {
    GC_PUSH(obj);
    name = to_string(ctx, name);
    GC_POP(obj);
  }
#ifdef INLINE_CACHE
  return get_prop_prototype_chain_with_ic(obj, name, ic);
#else /* INLINE_CACHE */
  return get_prop_prototype_chain(obj, name);
#endif /* INLINE_CACHE */
}

/*
 * obtain array element. `index' is an integer.
 * returns JS_EMPTY if `index` is out of range.
 */
JSValue get_array_element(Context *ctx, JSValue array, cint index)
{
  JSValue prop, ret;
  assert(is_array(array));

  if ((ret = get_array_element_no_proto(array, index)) != JS_EMPTY) {
    return ret;
  }

  GC_PUSH(array);
  prop = cint_to_number(ctx, index);
  GC_POP(array);
  prop = number_to_string(prop);
  return get_prop_prototype_chain(array, prop);
}

/*
 *  obtains array's property
 *    a: array
 *    p: property (number / string / other type)
 *  It is not necessary to check the type of `a'.
 */
JSValue get_array_prop(Context *ctx, JSValue a, JSValue p)
{
  if (is_fixnum(p))
    return get_array_element(ctx, a, fixnum_to_cint(p));

  if (!is_string(p)) {
    GC_PUSH(a);
    p = to_string(ctx, p);
    GC_POP(a);
  }
  assert(is_string(p));
  {
    JSValue num;
    GC_PUSH2(a, p);
    num = string_to_number(ctx, p);
    GC_POP2(p, a);
    if (is_fixnum(num))
      return get_array_element(ctx, a, fixnum_to_cint(num));
    else
      return get_prop_prototype_chain(a, p);
  }
}

/*
 * determines whether a[n] exists or not
 * if a[n] is not an element of body (a C array) of a, search properties of a
 *  a: array
 *  n: subscript
 */
int has_array_element(JSValue a, cint n)
{
  if (!is_array(a))
    return FALSE;
  if (n < 0 || number_to_cint(get_jsarray_length(a)) <= n)
    return FALSE;
  /* in body of 'a' */
  if (((uintjsv_t) n) < get_jsarray_size(a))
    return TRUE;
  /* in property of 'a' */
  return get_prop_prototype_chain(a, cint_to_string(n)) != JS_EMPTY;
}

/*
 * sets object's property
 *   o: object (but not an array)
 *   p: property (number / string / other type)
 *   v: value to be set
 * It is not necessary to check the type of `o'.
 */
int set_object_prop(Context *ctx, JSValue o, JSValue p, JSValue v)
{
  if (!is_string(p)) {
    GC_PUSH2(o, v);
    p = to_string(ctx, p);
    GC_POP2(v, o);
  }
  set_prop(ctx, o, p, v, ATTR_NONE);
  return SUCCESS;
}


/*
 * An array element is stored
 *  1. in array storage, or
 *  2. as a property
 * If 0 <= index < array.size, then the element is stored in the array storage.
 * Otherwise, it is stored as a property.
 *
 * Before judging where an element should be stored to, array storage may
 * be expanded.  If array.size <= index < ASIZE_LIMIT, the array storage
 * is expanded to the length of index.
 */

/*
 * Try to set a value into an continuous array of Array.
 * If the index is out of range of limit of continuous container,
 * handle it as a normal property.
 */
void set_array_element(Context *ctx, JSValue array, cint index, JSValue v)
{
  assert(is_array(array));

  /* 1. If array.size <= index < array.size * ASIZE_FACTOR + 1,
   *    expand the storage */
  {
    int32_t size = get_jsarray_size(array);
    if (size <= index && index < size + (size >> LOG_ASIZE_EXPAND_FACTOR) + 1) {
      GC_PUSH2(array, v);
      reallocate_array_data(ctx, array, size + (size >> LOG_ASIZE_EXPAND_FACTOR) + 1);
      GC_POP2(v, array);
    }
  }

  /* 2. If 0 <= index < array.size, store the value to the storage */
  if (0 <= index && ((uintjsv_t) index) < get_jsarray_size(array)) {
    JSValue *storage = get_jsarray_body(array);
    storage[index] = v;
  } else {
    /* 3. otherwise, store it as a property */
    JSValue prop;
    GC_PUSH2(array, v);
    prop = cint_to_number(ctx, index);
    prop = number_to_string(prop);
    set_prop(ctx, array, prop, v, ATTR_NONE);
    GC_POP2(v, array);
  }

  /* 4. Adjust `length' property. */
  {
    JSValue length_value;
    cint length;
    length_value = get_jsarray_length(array);
    assert(is_fixnum(length_value));
    length = fixnum_to_cint(length_value);
    if (length <= index) {
      GC_PUSH(array);
      JSValue num = cint_to_number(ctx, index + 1);
      GC_POP(array);
      set_jsarray_length(array, num);
    }
  }
}

static void
remove_and_convert_numerical_properties(Context *ctx, JSValue array,
                                        int32_t length)
{
  Shape *os = object_get_shape(array);
  PropertyMap *pm = os->pm;
  HashPropertyIterator iter = createHashPropertyIterator(pm->map);
  JSValue key;
  uint32_t index;
  Attribute attr;
  GC_PUSH2(pm, array);
  while (nextHashPropertyCell(pm->map, &iter, &key, &index, &attr) != FAIL) {
    JSValue number_key;
    double double_key;
    int32_t int32_key;
    assert(is_string(key));
    GC_PUSH(key);
    number_key = string_to_number(ctx, key);
    double_key = number_to_double(number_key);
    int32_key = (int32_t) double_key;
    if (int32_key >= 0 && double_key == (double) int32_key) {
      if (int32_key < length) {
        JSValue v = object_get_prop(array, index);
        JSValue *storage = get_jsarray_body(array);
        storage[index] = v;
      }
      set_prop(ctx, array, key, JS_EMPTY, ATTR_NONE);
    }
    GC_POP(key);
  }
  GC_POP2(array, pm);
}

int set_array_prop(Context *ctx, JSValue array, JSValue prop, JSValue v)
{
  JSValue index_prop;

  /* 1. If prop is fixnum, do element access. */
  if (is_fixnum(prop)) {
    cint index = fixnum_to_cint(prop);
    set_array_element(ctx, array, index, v);
    return SUCCESS;
  }

  /* 2. Convert prop to a string. */
  GC_PUSH2(v, array);
  if (!is_string(prop))
    prop = to_string(ctx, prop);

  /* 3. If prop is fixnum-like, do element access. */
  GC_PUSH(prop);
  index_prop = string_to_number(ctx, prop);
  GC_POP3(prop, array, v);
  if (is_fixnum(index_prop)) {
    cint index = fixnum_to_cint(index_prop);
    set_array_element(ctx, array, index, v);
    return SUCCESS;
  }

  /* 4. If prop is `length', adjust container size. */
  if (prop == gconsts.g_string_length) {
    double double_length;
    int32_t length;
    GC_PUSH2(v, array);
    if (!is_number(v))
      v = to_number(ctx, v);
    double_length = number_to_double(v);
    length = (int32_t) double_length;
    if (double_length != (double) length || length < 0)
      LOG_EXIT("invalid array length");
    {
      int32_t old_size = get_jsarray_size(array);
      JSValue old_len_jsv = get_jsarray_length(array);
      int32_t old_length = (int32_t) number_to_double(old_len_jsv);
      /* 4.1. Adjust container size. */
      reallocate_array_data(ctx, array, length);
      if (old_size < old_length) {
        /* 4.2 Remove and convert numerical properties.
         *       [old_size, length)   -- convert to array element.
         *       [length, old_length) -- remove
         */
        remove_and_convert_numerical_properties(ctx, array, length);
      }
    }
    /* 4.3 Set length property. */
    set_jsarray_length(array, v);
    GC_POP2(array,v);
    return SUCCESS;
  }

  /* 5. Set normal property */
  set_prop(ctx, array, prop, v, ATTR_NONE);
  return SUCCESS;
}

/*
 * delete the hash cell with key and the property of the object
 * NOTE:
 *   The function does not reallocate (shorten) the prop array of the object.
 *   It must be improved.
 * NOTE:
 *   When using hidden class, this function does not delete a property
 *   of an object but merely sets the corresponding property as JS_UNDEFINED,
 */
int delete_object_prop(JSValue obj, HashKey key)
{
  int index;
  Attribute attr;

  if (!is_object(obj))
    return FAIL;

  /* Set corresponding property as JS_UNDEFINED */
  index = prop_index(jsv_to_jsobject(obj), key, &attr, NULL);
  if (index == - 1)
    return FAIL;
  object_set_prop(obj, index, JS_UNDEFINED);

  /* Delete map */
  LOG_EXIT("delete is not implemented");
  return SUCCESS;
}

/*
 * delete a[n]
 * Note that this function does not change a.length
 */
int delete_array_element(JSValue a, cint n)
{
  assert(n >= 0);
  if (((uintjsv_t) n) < get_jsarray_size(a)) {
    JSValue *body = get_jsarray_body(a);
    body[n] = JS_UNDEFINED;
    return SUCCESS;
  }
  return delete_object_prop(a, cint_to_string(n));
}

/*
 * obtains the next property name in an iterator
 * iter:Iterator
 */
int iterator_get_next_propname(JSValue iter, JSValue *name)
{
  int size = get_jsnormal_iterator_size(iter);
  int index = get_jsnormal_iterator_index(iter);
  if(index < size) {
    JSValue *body = get_jsnormal_iterator_body(iter);
    *name = body[index++];
    set_jsnormal_iterator_index(iter, index);
    return SUCCESS;
  }else{
    *name = JS_UNDEFINED;
    return FAIL;
  }
}

#ifdef USE_REGEXP
/*
 * sets a regexp's members and makes an Oniguruma's regexp object
 */
int set_regexp_members(Context *ctx, JSValue re, char *pat, int flag)
{
  OnigOptionType opt;
  OnigErrorInfo err;
  char *e;
  JSObject *p;

  p = jsv_to_jsobject(re);

  set_jsregexp_pattern(re, strdup(pat));

  opt = ONIG_OPTION_NONE;

  if (flag & F_REGEXP_GLOBAL) {
    set_jsregexp_global(re, true);
    set_obj_cstr_prop(ctx, re, "global", JS_TRUE, ATTR_ALL);
  } else {
    set_jsregexp_global(re, false);
    set_obj_cstr_prop(ctx, re, "global", JS_FALSE, ATTR_ALL);
  }

  if (flag & F_REGEXP_IGNORE) {
    opt |= ONIG_OPTION_IGNORECASE;
    set_jsregexp_ignorecase(re, true);
    set_obj_cstr_prop(ctx, re, "ignoreCase", JS_TRUE, ATTR_ALL);
  } else {
    set_jsregexp_ignorecase(re, false);
    set_obj_cstr_prop(ctx, re, "ignoreCase", JS_FALSE, ATTR_ALL);
  }

  if (flag & F_REGEXP_MULTILINE) {
    opt |= ONIG_OPTION_MULTILINE;
    set_jsregexp_multiline(re, true);
    set_obj_cstr_prop(ctx, re, "multiline", JS_TRUE, ATTR_ALL);
  } else {
    set_jsregexp_multiline(re, false);
    set_obj_cstr_prop(ctx, re, "multiline", JS_FALSE, ATTR_ALL);
  }

  e = pat + strlen(pat);
  if (onig_new((OnigRegex *)&(p->eprop[1])/* TODO: This code means &(get_jsregexp_reg(re)) */,
               (OnigUChar *)pat, (OnigUChar *)e, opt,
               ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &err) == ONIG_NORMAL)
    return SUCCESS;
  else
    return FAIL;
}

/*
 * returns a flag value from a ragexp objext
 */
int regexp_flag(JSValue re)
{
  int flag;

  flag = 0;
  if (get_jsregexp_global(re)) flag |= F_REGEXP_GLOBAL;
  if (get_jsregexp_ignorecase(re)) flag |= F_REGEXP_IGNORE;
  if (get_jsregexp_multiline(re)) flag |= F_REGEXP_MULTILINE;
  return flag;
}
#endif

/*
 * makes a simple iterator object
 */
JSValue new_iterator(Context *ctx, JSValue obj) {
  JSValue iter;
  int index = 0;
  int size = 0;
  JSValue tmpobj;

  GC_PUSH(obj);
  iter = ptr_to_normal_iterator(allocate_iterator(ctx));

  /* allocate an itearator */
  tmpobj = obj;
  do {
    PropertyMap *pm = object_get_shape(tmpobj)->pm;
    size += pm->n_props - pm->n_special_props;
    tmpobj = object_get___proto__(tmpobj);
  } while (tmpobj != JS_NULL);
  GC_PUSH(iter);
  allocate_iterator_data(ctx, iter, size);

  /* fill the iterator with object properties */
  do {
    HashTable *ht;
    HashPropertyIterator hi;
    JSValue key;
    uint32_t prop_index;
    Attribute attr;
    JSValue *body;

    ht = object_get_shape(obj)->pm->map;
    hi = createHashPropertyIterator(ht);

    body = get_jsnormal_iterator_body(iter);
    while (nextHashPropertyCell(ht, &hi, &key, &prop_index, &attr) == SUCCESS) {
      if (attr & ATTR_DE)
        continue;
      body[index++] = key;
    }
    obj = object_get___proto__(obj);
  } while (obj != JS_NULL);
  GC_POP2(iter, obj);
  return iter;
}

/*  data conversion functions */
char *space_chomp(char *str)
{
  while (isspace(*str)) str++;
  return str;
}

double cstr_to_double(char* cstr)
{
  char* endPtr;
  double ret;
  ret = strtod(cstr, &endPtr);
  while (isspace(*endPtr)) endPtr++;
  if (*endPtr == '\0') return ret;
  else return NAN;
}

#ifdef HC_PROF
/* exprot to GC */
struct root_property_map *root_property_map;

static void hcprof_add_root_property_map(PropertyMap *pm)
{
  struct root_property_map *e =
    (struct root_property_map *) malloc(sizeof(struct root_property_map));
  e->pm = pm;
  e->next = root_property_map;
  root_property_map = e;
}

static void print_shape_line(Shape *os)
{
  printf("SHAPE: %p %p %d %d %s\n",
         os,
         os->next,
         os->n_embedded_slots,
         os->n_extension_slots,
#ifdef DEBUG
         os->name
#else /* DEBUG */
         ""
#endif /* DEBUG */
         );
}

static void print_property_map(const char *key, PropertyMap *pm)
{
  if (key == NULL)
    key = "(root)";
  printf("======== %s start ========\n", key);
  printf("HC: %p %p %d %d %d %s %s\n",
         pm,
         pm->u.ord.shapes,
         pm->n_props,
         pm->n_enter,
         pm->n_leave,
         key,
#ifdef DEBUG
         pm->name
#else /* DEBUG */
         ""
#endif /* DEBUG */
         );
  {
    Shape *os;
    for (os = pm->u.ord.shapes; os != NULL; os = os->next)
      print_shape_line(os);
  }
  print_hash_table(pm->map);
  printf("======== %s end ========\n", key);
}

static void print_property_map_recursive(const char *key, PropertyMap *pm)
{
  HashTransitionIterator iter;
  HashTransitionCell *p;

  print_property_map(key, pm);
  iter = createHashTransitionIterator(pm->map);
  while(nextHashTransitionCell(pm->map, &iter, &p) != FAIL)
    print_property_map_recursive(string_to_cstr(hash_transition_cell_key(p)),
                                 hash_transition_cell_pm(p));
}

void hcprof_print_all_hidden_class(void)
{
  struct root_property_map *e;
  for (e = root_property_map; e != NULL; e = e->next)
    print_property_map_recursive(NULL, e->pm);
}

#ifdef DUMP_HCG
static inline int is_jsobject_type(cell_type_t type)
{
  switch(type) {
  case CELLT_SIMPLE_OBJECT:
  case CELLT_FUNCTION:
  case CELLT_BUILTIN:
  case CELLT_ARRAY:
  case CELLT_BOXED_STRING:
  case CELLT_BOXED_NUMBER:
  case CELLT_BOXED_BOOLEAN:
#ifdef USE_REGEXP
  case CELLT_REGEXP:
#endif /* USE_REGEXP */
    return 1;
  default:
    return 0;
  }
}

struct population_cell {
  int generation;
  int count;
  struct population_cell* next;
};

void count_hc_instance_hook(void *xp)
{
  cell_type_t type = gc_obj_header_type(xp);
  JSObject *p;
  struct population_cell *cellp;
  
  if (!is_jsobject_type(type))
    return;
  p = (JSObject*) xp;
  
  cellp = (struct population_cell *) p->shape->population;
  if (cellp == NULL || cellp->generation != generation) {
    cellp = (struct population_cell *)malloc(sizeof(struct population_cell));
    cellp->generation = generation;
    cellp->count = 0;
    cellp->next = (struct population_cell *) p->shape->population;
    p->shape->population = cellp;
  }
  cellp->count++;
}

static int shape_peak_population(Shape *os)
{
  int max = 0;
  struct population_cell *cellp;
  for (cellp = (struct population_cell *)os->population;
       cellp != NULL; cellp = cellp->next)
    if (cellp->count > max)
      max = cellp->count;
  return max;
}

static void dump_property_map_recursive(FILE *fp, Context *ctx,
                                        char *prop_name, PropertyMap *pm)
{
  Shape *os;
  
  fprintf(fp, "HC"); /* 0 */
  fprintf(fp, " %p", pm); /* 1 */
  fprintf(fp, " %c", (pm->flags & PM_FLAG_ROOT) ? 'R' : '_'); /* 2 */
  fprintf(fp, " %c", pm->is_entry ? 'E' : '_'); /* 3 */
  fprintf(fp, " %c", pm->is_builtin ? 'B' : '_'); /* 4 */
  fprintf(fp, " %d", pm->function_no); /* 5 */
  fprintf(fp, " %d", pm->insn_no); /* 6 */
  fprintf(fp, " %s", prop_name == NULL ? "(null)" : prop_name); /* 7 */
  fprintf(fp, " J"); /* 8 */
  fprintf(fp, " %d", pm->n_enter); /* 9 */
  fprintf(fp, " %d", pm->n_leave); /* 10 */
#ifdef DEBUG
  fprintf(fp, " %s", pm->name); /* 11 */
#else /* DEBUG */
  fprintf(fp, " noname");
#endif /* DEBUG */
  fprintf(fp, " %d", pm->n_props); /* 12 */
  fprintf(fp, " %d", pm->id); /* 13 */
  fprintf(fp, " %d", pm->n_special_props); /* 14 */
  fprintf(fp, "\n");
  {
    HashPropertyIterator iter = createHashPropertyIterator(pm->map);
    JSValue key;
    uint32_t index;
    Attribute attr;
    while(nextHashPropertyCell(pm->map, &iter, &key, &index, &attr) != FAIL)
      fprintf(fp, "PROP %p %d %s %d\n", pm, index, string_to_cstr(key), attr);
  }
  for (os = pm->u.ord.shapes; os != NULL; os = os->next) {
    int fun_no, insn_no;
    alloc_site_loc(ctx, os->alloc_site, &fun_no, &insn_no);
    fprintf(fp, "SHAPE %p %d %d %d %c %d %d %d %d\n",
            pm, /* 1 */
            os->n_embedded_slots, /* 2 */
            fun_no, /* 3 */
            insn_no, /* 4 */
            os->is_cached ? 'C' : '_', /* 5 */
            shape_peak_population(os), /* 6 */
            os->n_enter, /* 7 */
            os->n_leave, /* 8 */
#ifdef PROTO_IC
            os->is_proto /* 9 */
#else  /* PROTO_IC */
            0 /* 9 */
#endif /* PROTO_IC */
            );
  }
  {
    HashTransitionIterator iter = createHashTransitionIterator(pm->map);
    HashTransitionCell *p;
    while(nextHashTransitionCell(pm->map, &iter, &p) != FAIL)
      fprintf(fp, "TRANSITION %p %s %p\n",
              pm,  /* 1 */
              string_to_cstr(hash_transition_cell_key(p)), /* 2 */
              hash_transition_cell_pm(p)); /* 3 */
  }

  {
    HashTransitionIterator iter = createHashTransitionIterator(pm->map);
    HashTransitionCell *p;
    while(nextHashTransitionCell(pm->map, &iter, &p) != FAIL)
      dump_property_map_recursive(fp, ctx,
                                  string_to_cstr(hash_transition_cell_key(p)),
                                  hash_transition_cell_pm(p));
  }
}

void dump_hidden_classes(char *outfile, Context *ctx)
{
  struct root_property_map *e;
  FILE *fp;
  fp = fopen(outfile, "w");
  if (fp == NULL)
    LOG_EXIT("cannot open HC dump file");
  for (e = root_property_map; e != NULL; e = e->next)
    dump_property_map_recursive(fp, ctx, NULL, e->pm);
  fclose(fp);
}
#endif /* DUMP_HCG */
#endif /* HC_PROF */

#ifdef AS_PROF
void print_as_prof(Context *ctx)
{
  int i;
  char buf[2000] = {};

  for (i = 0; i < ctx->nfuncs; i++) {
    FunctionTable *p = ctx->function_table + i;
    int j;
    for (j = 0; j < p->n_insns; j++) {
      AllocSite *as = &(INSN_CACHE(i, j).alloc_site);
      if (as->pm != NULL) {
        int nshare = 0;
        PropertyMap *pm = as->pm;
        Shape *os;
        for (os = pm->u.ord.shapes; os != NULL; os = os->next)
          nshare++;
#ifdef VERBOSE_HC
        buf[0] = ' ';
        sprint_property_map(buf + 1, pm);
#endif /* VERBOSE_HC */
        printf("AS %03d:%03d ", i, j);
        printf("alloc %6d hit %6d ", as->n_alloc,
               as->shape == NULL ? 0 : as->shape->n_alloc);
        printf("trans %6d copy %6d ", as->transition, as->copy_words);
        printf("size %d/%d ",
               as->shape == NULL ? pm->n_props : as->shape->n_embedded_slots,
               as->shape == NULL ? 0 : as->shape->n_extension_slots);
        printf("share %d%s\n", nshare, buf);
      }
    }
  }
}
#endif /* AS_PROF */

#ifdef VERBOSE_HC
#ifndef HC_PROF
#error VERBOSE_HC require HC_PROF
#endif /* HC_PROF */
int sprint_property_map(char *start, PropertyMap *pm)
{
  char *buf = start;
  int i;

  buf += sprintf(buf, "%p(%3d)", pm, pm->id);
#ifdef PROTO_IC
  if (pm->u.ord.prev == NULL)
    buf += sprintf(buf, " prev (NIL)");
  else
    buf += sprintf(buf, " prev (%3d)", pm->u.ord.prev->id);
  }
#endif /* PROTO_IC */
  buf += sprintf(buf, " %7d/%7d props %d",
                 pm->n_enter, pm->n_leave, pm->n_props);
#ifdef HC_SKIP_INTERNAL
  buf += sprintf(buf, "trans %d", pm->n_transitions);
#endif /* HC_SKIP_INTERNAL */
  buf += sprintf(buf, " [");
  for (i = 0; i < pm->n_props; i++) {
    HashPropertyIterator iter = createHashPropertyIterator(pm->map);
    JSValue key;
    uint32_t index;
    Attribute attr;
    while (nextHashPropertyCell(pm->map, &iter, &key, &index, &attr) != FAIL) {
      if (index == i) {
        buf += sprintf(buf, "%s ", string_to_cstr(key));
        break;
      }
    }
  }
  buf += sprintf(buf, "]");

  return buf - start;
}
#endif /* VERBOSE_HC */


/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
