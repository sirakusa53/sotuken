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

extern char *load_hcg_file_name;

/*
 * initilaizes global constants
 */
void init_global_constants(void) {
  size_t i;
  for (i = 0; i < sizeof(gconsts)/sizeof(JSValue); i++)
    ((JSValue *)&gconsts)[i] = JS_UNDEFINED;

  /* string constants */
  gconsts.g_string___property_map__ = cstr_to_string(NULL, "__property_map__");
  gconsts.g_string_prototype = cstr_to_string(NULL, "prototype");
  gconsts.g_string___proto__ = cstr_to_string(NULL, "__proto__");
  gconsts.g_string_tostring  = cstr_to_string(NULL, "toString");
  gconsts.g_string_valueof   = cstr_to_string(NULL, "valueOf");
  gconsts.g_string_boolean   = cstr_to_string(NULL, "boolean");
  gconsts.g_string_number    = cstr_to_string(NULL, "number");
  gconsts.g_string_object    = cstr_to_string(NULL, "object");
  gconsts.g_string_string    = cstr_to_string(NULL, "string");
  gconsts.g_string_true      = cstr_to_string(NULL, "true");
  gconsts.g_string_false     = cstr_to_string(NULL, "false");
  gconsts.g_string_null      = cstr_to_string(NULL, "null");
  gconsts.g_string_undefined = cstr_to_string(NULL, "undefined");
  gconsts.g_string_length    = cstr_to_string(NULL, "length");
  gconsts.g_string_objtostr  = cstr_to_string(NULL, "[object Object]");
  gconsts.g_string_empty     = cstr_to_string(NULL, "");
  gconsts.g_string_comma     = cstr_to_string(NULL, ",");
  gconsts.g_string_blank     = cstr_to_string(NULL, " ");

  /* numbers */
  gconsts.g_flonum_infinity  = double_to_flonum(NULL, INFINITY);
  gconsts.g_flonum_negative_infinity = double_to_flonum(NULL, -INFINITY);
  gconsts.g_flonum_nan       = double_to_flonum(NULL, NAN);

  /* boolean */
  gconsts.g_boolean_true  = JS_TRUE;
  gconsts.g_boolean_false = JS_FALSE;

  /* special */
  gconsts.g_null      = JS_NULL;
  gconsts.g_undefined = JS_UNDEFINED;
}

static Shape *create_map_and_shape(Context *ctx,
                                   const char *name,
                                   uint32_t num_special,
                                   JSValue proto,
                                   ObjBuiltinProp builtin_props[],
                                   uint32_t num_builtin_props,
                                   ObjDoubleProp double_props[],
                                   uint32_t num_double_props,
                                   ObjGconstsProp gconsts_props[],
                                   uint32_t num_gconsts_props,
                                   char *user_props[],
                                   uint32_t num_user_props,
                                   int is_proto)
{
#ifdef LOAD_HCG
  if (load_hcg_file_name != NULL) {
    static int next_builtin_id = 1;
    int builtin_id = next_builtin_id++;
    PropertyMap *pm = find_loaded_property_map(builtin_id);
    Shape *os;
    /* PM may be shared with multiple shapes */
    if (pm->__proto__ == JS_EMPTY)
      property_map_install___proto__(pm, proto);
    if (is_proto)
      os = find_loaded_prototype_os(builtin_id);
    else {
      uint32_t num_normal_props =
        num_builtin_props + num_double_props + num_gconsts_props + num_user_props;
      uint32_t num_props = num_normal_props + num_special;
      uint32_t num_embedded = num_props + (num_normal_props == 0 ? 1 : 0);
      /* num_embedded is the initial number of properties.
       * Due to pretransitioning, pm may have more properties */
      if (pm->n_props > num_embedded)
        num_embedded = pm->n_props;
      os = property_map_find_shape(pm, num_embedded, 0, 0);
    }
    assert(os != NULL);
    return os;
  }
#endif /* LOAD_HCG */
  PropertyMap *m;
  Shape *s;
  uint32_t i;
  uint32_t num_normal_props =
    num_builtin_props + num_double_props + num_gconsts_props + num_user_props;
  uint32_t num_user_special_props;
  uint32_t num_props;
  uint32_t num_embedded;
  uint32_t index = num_special;

  /* remove special props */
  num_user_special_props = 0;
  for (i = 0; i < num_double_props; i++) {
    ObjDoubleProp *p = &double_props[i];
    if (p->index != -1)
      num_user_special_props++;
  }
  num_normal_props -= num_user_special_props;

  num_props = num_normal_props + num_special;
  num_embedded = num_props + (num_normal_props == 0 ? 1 : 0);

  m = new_property_map(ctx, name, num_special, num_props,
                       num_user_special_props, proto, PM_FLAG_ROOT);
#ifdef DUMP_HCG
  m->is_entry = 1;
#endif /* DUMP_HCG */
  for (i = 0; i < num_builtin_props; i++) {
    ObjBuiltinProp *p = &builtin_props[i];
    property_map_add_property_entry(ctx, m, cstr_to_string(ctx, p->name),
                                    index++, p->attr);
  }
  for (i = 0; i < num_double_props; i++) {
    ObjDoubleProp *p = &double_props[i];
    if (p->index != -1)
      property_map_add_property_entry(ctx, m, cstr_to_string(ctx, p->name),
                                      p->index, p->attr);
    else
      property_map_add_property_entry(ctx, m, cstr_to_string(ctx, p->name),
                                      index++, p->attr);
  }
  for (i = 0; i < num_gconsts_props; i++) {
    ObjGconstsProp *p = &gconsts_props[i];
    property_map_add_property_entry(ctx, m, cstr_to_string(ctx, p->name),
                                    index++, p->attr);
  }
  for (i = 0; i < num_user_props; i++) {
    char *p = user_props[i];
    property_map_add_property_entry(ctx, m, cstr_to_string(ctx, p),
                                    index++, ATTR_NONE);
  }
#if defined(DUMP_HCG)
  {
    static int next_builtin_id = 1;
    AllocSite *as = (AllocSite *) malloc(sizeof(AllocSite));
    init_alloc_site(as);
    as->builtin_id = next_builtin_id++;
    s = new_object_shape(ctx, name, m, num_embedded, 0, as, is_proto);
  }
#elif defined(ALLOC_SITE_CACHE)
  s = new_object_shape(ctx, name, m, num_embedded, 0, NULL, is_proto);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
  s = new_object_shape(ctx, name, m, num_embedded, 0, is_proto);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
  return s;
}

#define CREATE_MAP_AND_SHAPE(ctx, name, num_special, proto, KEY, is_proto) \
  create_map_and_shape(ctx, name, num_special, proto,                   \
                       KEY ## _builtin_props,                           \
                       KEY ## _num_builtin_props,                       \
                       KEY ## _double_props,                            \
                       KEY ## _num_double_props,                        \
                       KEY ## _gconsts_props,                           \
                       KEY ## _num_gconsts_props,                       \
                       NULL,                                            \
                       0,                                               \
                       is_proto)

static void fill_builtin_properties(Context *ctx,
                                    JSValue object,
                                    ObjBuiltinProp builtin_props[],
                                    uint32_t num_builtin_props,
                                    ObjDoubleProp double_props[],
                                    uint32_t num_double_props,
                                    ObjGconstsProp gconsts_props[],
                                    uint32_t num_gconsts_props)
{
  uint32_t i;
  for (i = 0; i < num_builtin_props; i++) {
    ObjBuiltinProp *p = &builtin_props[i];
    JSValue value =
      new_builtin_object(ctx, p->name, gshapes.g_shape_Builtin,
                         p->fn, builtin_not_a_constructor, p->na);
    set_prop_direct(ctx, object, cstr_to_string(ctx, p->name),
                    value, p->attr);
  }
  for (i = 0; i < num_double_props; i++) {
    ObjDoubleProp *p = &double_props[i];
    set_prop_direct(ctx, object, cstr_to_string(ctx, p->name),
                    double_to_number(ctx, p->value), p->attr);
  }
  for (i = 0; i < num_gconsts_props; i++) {
    ObjGconstsProp *p = &gconsts_props[i];
    set_prop_direct(ctx, object, cstr_to_string(ctx, p->name),
                    *(p->addr), p->attr);
  }
}
#define FILL_BUILTIN_PROPERTIES(ctx, object, KEY)      \
  fill_builtin_properties(ctx, object,                 \
                          KEY ## _builtin_props,       \
                          KEY ## _num_builtin_props,   \
                          KEY ## _double_props,        \
                          KEY ## _num_double_props,    \
                          KEY ## _gconsts_props,       \
                          KEY ## _num_gconsts_props)

/*
 * initialisation of prototypes objects, constructor objects, and their
 * property maps and shapes.
 */
void init_meta_objects(Context *ctx)
{
  /*
   * Step 1
   *  - Create property maps and object shapes for prototype objects.
   *  - Create prototype objects.
   *  - Create property maps and object shapes for instances.
   */

  /* STEP1
   *   T        Type name.
   *   pproto   __proto__ of prototype object.
   *   psp      # of special fields of prototype object.
   *   isp      # of special fields of instances
   *   ctor     C-constructor function to create prototype object.
   *   ctorargs [VA] Custom arguments to be passed to the constructor.
   */
#define STEP1(T, pproto, psp, isp, ctor, ctorargs...)                   \
  do {                                                                  \
    Shape *os =                                                        \
      CREATE_MAP_AND_SHAPE(ctx, DEBUG_NAME(#T "Prototype"), psp, pproto, \
                           T ## Prototype, 1);                          \
    JSValue iproto = ctor(ctx, DEBUG_NAME(#T "Prototype"), os, ##ctorargs); \
    gshapes.g_shape_ ## T =                                             \
      CREATE_MAP_AND_SHAPE(ctx, DEBUG_NAME(#T "0"), isp, iproto, T, 0); \
    gconsts.g_prototype_ ## T = iproto;                                 \
  } while(0)

#define OBJPROTO gconsts.g_prototype_Object

  STEP1(Object,   JS_NULL,  OBJECT_SPECIAL_PROPS,  OBJECT_SPECIAL_PROPS,
        new_simple_object);
  STEP1(Function, OBJPROTO, BUILTIN_SPECIAL_PROPS, FUNCTION_SPECIAL_PROPS,
        new_builtin_object, function_prototype_fun,
        builtin_not_a_constructor, 0);
  STEP1(Array,    OBJPROTO, ARRAY_SPECIAL_PROPS,   ARRAY_SPECIAL_PROPS,
        new_array_object, 0);
  STEP1(String,   OBJPROTO, STRING_SPECIAL_PROPS,  STRING_SPECIAL_PROPS,
        new_string_object, gconsts.g_string_empty);
  STEP1(Boolean,  OBJPROTO, BOOLEAN_SPECIAL_PROPS, BOOLEAN_SPECIAL_PROPS,
        new_boolean_object, JS_FALSE);
  STEP1(Number,   OBJPROTO, NUMBER_SPECIAL_PROPS,  NUMBER_SPECIAL_PROPS,
        new_number_object, FIXNUM_ZERO);
#ifdef USE_REGEXP
  STEP1(RegExp,   OBJPROTO, REX_SPECIAL_PROPS,     REX_SPECIAL_PROPS,
        new_regexp_object, "", 0);
#endif /* USE_REGEXP */

  gpms.g_property_map_Object = gshapes.g_shape_Object->pm;

#undef OBJPROTO
#undef STEP1
  
  /*
   * Step 2
   *   - Fill built-in properties of prototype objects.
   *   - Create constructors.
   *   - Fill built-in properties of constructors.
   *   TODO: create dedicated object shapes for the constructors.
   */

  gshapes.g_shape_Builtin =
    CREATE_MAP_AND_SHAPE(ctx, DEBUG_NAME("Builtin0"), BUILTIN_SPECIAL_PROPS,
                         gconsts.g_prototype_Function, Builtin, 0);

#define STEP2(T, cfun, cctor, na)                               \
  do {                                                          \
    JSValue ctor;                                               \
    FILL_BUILTIN_PROPERTIES(ctx, gconsts.g_prototype_ ## T,     \
                            T ## Prototype);                    \
    ctor = new_builtin_object(ctx, DEBUG_NAME(#T),              \
                              gshapes.g_shape_Builtin,          \
                              cfun, cctor, na);                 \
    FILL_BUILTIN_PROPERTIES(ctx, ctor, T ## Constructor);       \
    gconsts.g_ctor_ ## T = ctor;                                \
  } while (0)

  STEP2(Object,   object_constr,        object_constr,   0);
  STEP2(Function, function_constr,      function_constr, 0);
  STEP2(Array,    array_constr,         array_constr,    0);
  STEP2(String,   string_constr_nonew,  string_constr,   1);
  STEP2(Number,   number_constr_nonew,  number_constr,   1);
  STEP2(Boolean,  boolean_constr_nonew, boolean_constr,  1);
#ifdef USE_REGEXP
  STEP2(RegExp,   regexp_constr_nonew,  regexp_constr,   2);
#endif /* USE_REGEXP */
#undef STEP2

  /*
   * Step 3
   *   - Create builtin constructors whose prototypes are normal objects.
   *   TODO: create dedicated object shapes for the constructors.
   */
#define STEP3(T, cfun, cctor, na, nprops)                               \
  do {                                                                  \
    /* TODO: Complete definition */                                     \
    JSValue prototype, ctor;                                            \
    prototype = new_simple_object(ctx, DEBUG_NAME(#T "Prototype"),      \
                                  gshapes.g_shape_Object);              \
    ctor = new_builtin_object(ctx, DEBUG_NAME(#T),                      \
                              gshapes.g_shape_Builtin,                  \
                              cfun, cctor, na);                         \
    FILL_BUILTIN_PROPERTIES(ctx, ctor, T ## Constructor);               \
    gconsts.g_ctor_ ## T = ctor;                                        \
    gshapes.g_shape_ ## T = CREATE_MAP_AND_SHAPE(                       \
      ctx, DEBUG_NAME(#T "Shape"), nprops,                              \
      gconsts.g_prototype_Object, T, 0);                                \
  } while (0)

#if 0
#ifdef USE_REGEXP
  STEP3(RegExp, regexp_constr_nonew, regexp_constr, 2, REX_SPECIAL_PROPS);
#endif /* USE_REGEXP */
#endif /* 0 */

#undef STEP3
}

#define CREATE_GLOBAL_OBJECT(ctx, name, KEY, key, uprops, num_uprops)   \
do {                                                                    \
  Shape *os;                                                            \
  JSValue obj;                                                          \
  JSValue proto = new_simple_object(ctx, DEBUG_NAME(name ".__proto__"), \
                                    gshapes.g_shape_Object);            \
  object_promote_to_prototype(ctx, proto);                              \
  os = create_map_and_shape(ctx, DEBUG_NAME(name), 0, proto,            \
                            KEY ## _builtin_props,                      \
                            KEY ## _num_builtin_props,                  \
                            KEY ## _double_props,                       \
                            KEY ## _num_double_props,                   \
                            KEY ## _gconsts_props,                      \
                            KEY ## _num_gconsts_props,                  \
                            uprops, num_uprops, 0);                     \
  obj = new_simple_object(ctx, DEBUG_NAME(name), os);                   \
  gconsts.key = obj;                                                    \
} while(0)

/*
 * initializes global objects
 */
void init_global_objects(Context *ctx)
{
  /* Step 1
   *   - create shape
   *   - create object with empty slots
   */
  CREATE_GLOBAL_OBJECT(ctx, "global", Global, g_global, NULL, 0);
  CREATE_GLOBAL_OBJECT(ctx, "math", Math, g_math, NULL, 0);
  CREATE_GLOBAL_OBJECT(ctx, "performance", Performance, g_performance, NULL, 0);

  /* Step 2
   *   - fill propertyes
   */
  FILL_BUILTIN_PROPERTIES(ctx, gconsts.g_global, Global);
  FILL_BUILTIN_PROPERTIES(ctx, gconsts.g_math, Math);
  FILL_BUILTIN_PROPERTIES(ctx, gconsts.g_performance, Performance);
}

#ifdef NEED_INSTRUCTION_CACHE
struct instruction_cache **insn_cache;

void init_instruction_cache_list(size_t size)
{
  size_t i;

  struct instruction_cache **p
    = (struct instruction_cache **)malloc(sizeof(struct instruction_cache*) * size);

  if (p == NULL)
    LOG_EXIT("Out of memory; instruction cache list cannot be allocateed.\n");

  insn_cache = p;

  for (i = 0; i < size; ++i)
    p[i] = NULL;
}

void init_instruction_cache(int index, size_t size)
{
#ifdef FUNCTION_TABLE_LIMIT
  if (index >= FUNCTION_TABLE_LIMIT)
    LOG_EXIT("Function index is out of range.\n");
#endif /* FUNCTION_TABLE_LIMIT */

  struct instruction_cache *p
    = (struct instruction_cache *)malloc(sizeof(struct instruction_cache) * size);

  if (p == NULL)
    LOG_EXIT("Out of memory; instruction cache cannot be allocateed.\n");

  size_t i;
  for (i = 0; i < size; ++i) {
    struct instruction_cache *elem = &(p[i]);
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG) || defined(LOAD_HCG)
    init_alloc_site(&(elem->alloc_site));
#endif /* ALLOC_SITE_CACHE || DUMP_HCG || LOAD_HCG */
#ifdef INLINE_CACHE
    init_inline_cache(&(elem->inl_cache));
#endif /* INLINE_CACHE */
#ifdef PROFILE
    elem->count = 0;
    elem->logflag = 0;
    elem->call_flag_table = NULL;
#endif /* PROFILE */
  }

  insn_cache[index] = p;
}
#endif /* NEED_INSTRUCTION_CACHE */

#ifndef USE_EMBEDDED_INSTRUCTION
void init_function_table_list(FunctionTable ftable[], size_t size)
{
  size_t i;
  for (i = 0; i <= size; ++i) {
    ftable[i].insns = NULL;
    ftable[i].constants = NULL;
  }
}
#endif /* USE_EMBEDDED_INSTRUCTION */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
