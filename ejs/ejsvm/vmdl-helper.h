/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
#define concat(context,s1,s2)            ejs_string_concat((context), (s1), (s2))

#ifdef INLINE_CACHE
#define getObjectProp(context,v1,v2)     get_object_prop((context), (v1), (v2), NULL)
#else /* INLINE_CACHE */
#define getObjectProp(context,v1,v2)     get_object_prop((context), (v1), (v2))
#endif /* INLINE_CACHE */
#ifdef INLINE_CACHE
static inline void set_object_prop_inl(Context *ctx, JSValue obj, JSValue prop, JSValue val, InlineCache *ic)
{
#ifdef IC_PROF
  ic->count++;
  ic_prof_count++;
  if (ic->pm == NULL)
    ic->unavailable++;
#endif /* IC_PROF */
  if (ic->pm == object_get_shape(obj)->pm && ic->prop_name == prop) {
    assert(ic->index <
           object_get_shape(obj)->n_embedded_slots +
           object_get_shape(obj)->n_extension_slots -
           (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
    object_set_prop(obj, ic->index, val);
#ifdef IC_PROF
    ic->hit++;
    ic_prof_hit++;
#endif /* IC_PROF */
  } else {
    if (++ic->miss > INLINE_CACHE_RESET_THRESHOLD)
      ic->pm = NULL;
    set_prop_with_ic(ctx, obj, prop, val, ATTR_NONE, ic);
  }
}
#define SetObjectPropInl(context,v1,v2,v3)  set_object_prop_inl((context), (v1), (v2), (v3), &(INSN_CACHE(curfn->index, pc).inl_cache))
#endif /* INLINE_CACHE */

#define cint_to_double(x) ((double)(x))
#define double_to_cint(x) ((cint)(x))
#define cint_to_uintjsv_t(x) ((uintjsv_t)(x))
#define uintjsv_t_to_cint(x) ((cint)(x))
#define to_unsigned_long(x) ((unsigned long)(x))

#define FIXNUM_EQ(v1,v2) ((int64_t) (v1) == (int64_t) (v2))
#define FIXNUM_LESSTHAN(v1,v2)   ((int64_t) (v1) < (int64_t) (v2))
#define FIXNUM_LESSTHANEQ(v1,v2) ((int64_t) (v1) <= (int64_t) (v2))
#define FIXNUM_AND(v1,v2)        ((int64_t) (v1) & (int64_t) (v2))
#define FIXNUM_OR(v1,v2)        ((int64_t) (v1) | (int64_t) (v2))


#define Object_to_primitive_hint_number(context,v) object_to_primitive((context), (v) ,HINT_NUMBER)

#define IsFlonumInfinity(v)    ((v) == gconsts.g_flonum_infinity)
#define IsFlonumNegInfinity(v) ((v) == gconsts.g_flonum_negative_infinity)
#define IsFlonumNan(v)         ((v) == gconsts.g_flonum_nan)
#define IsFixnumZero(v)        ((v) == small_cint_to_fixnum((cint)0))

#define isNullPointer(v)     ((v) == NULL)

#define LogicalRightShift(v1, v2)   ((uint32_t)(v1) >> (uint32_t)(v2))

#define Get_opcode()    get_opcode(insn)
#define IsSend(op)      (((op) != CALL)? TRUE : FALSE)
#define IsTailSend(op)  (((op) == TAILSEND)? TRUE : FALSE)
/* NOTE: 'Set_sp' is an old wrap function. Use 'set_sp' instead. */
#define Set_sp(n)       set_sp(context, fp - n)
#define Tailcall_builtin(context,fn, n, sendp)			\
  tailcall_builtin(context, (fn), (n), (sendp), FALSE)
#define Create_simple_object_with_constructor(context, con)                      \
  create_simple_object_with_constructor(context, con)
#ifdef INLINE_CACHE
/* Implementation of the branch of GETPROP instruction where obj is
 * a JSObject and INLINE_CACHE is enabled.
 */
static inline JSValue get_prop_object_inl_helper(Context* context, InlineCache* ic,
                                   JSValue obj, JSValue prop)
{
  JSValue ret;

#ifdef IC_PROF
  ic->count++;
  ic_prof_count++;
  if (ic->pm == NULL)
    ic->unavailable++;
#endif /* IC_PROF */
  if (ic->pm == object_get_shape(obj)->pm && ic->prop_name == prop) {
    assert(ic->index <
           object_get_shape(obj)->n_embedded_slots +
           object_get_shape(obj)->n_extension_slots -
           (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
    ret = object_get_prop(obj, ic->index);
    if (ret == JS_EMPTY)
      ret = get_object_prop(context, obj, prop, ic);
#ifdef IC_PROF
    else {
      ic->hit++;
      ic_prof_hit++;
    }
#endif /* IC_PROF */
  } else {
    if (++ic->miss > INLINE_CACHE_RESET_THRESHOLD)
      ic->pm = NULL;
    ret = get_object_prop(context, obj, prop, ic);
  }

  return ret;
}
#define Get_prop_object_inl(context, obj, prop)                           \
  get_prop_object_inl_helper(context, &(INSN_CACHE(curfn->index, pc).inl_cache), obj, prop)
#endif /* INLINE_CACHE */
#define Lcall_stack_push()          lcall_stack_push(context, pc)

#ifdef INLINE_CACHE
static inline JSValue get_global_inl(Context *context, JSValue obj, JSValue prop, InlineCache *ic)
{
  JSValue val;

#ifdef IC_PROF
  ic->count++;
  ic_prof_count++;
  if (ic->prop_name == JS_EMPTY)
    ic->unavailable++;
#endif /* IC_PROF */
  if (ic->prop_name == prop) {
    assert(ic->index <
      object_get_shape(obj)->n_embedded_slots +
      object_get_shape(obj)->n_extension_slots -
      (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
    val = object_get_prop(obj, ic->index);
    assert(val != JS_EMPTY);  /* global variable removed? */
#ifdef IC_PROF
    ic->hit++;
    ic_prof_hit++;
#endif /* IC_PROF */
  } else {
    assert(ic->prop_name == JS_EMPTY);
    ic->miss++;
    val = get_object_prop(context, obj, prop, ic);
  }

  return val;
}
#define GetGlobalInl(context,obj,prop)  get_global_inl((context), (obj), (prop), &(INSN_CACHE(curfn->index, pc).inl_cache))
#endif /* INLINE_CACHE */

#define GOTO(l)                     goto l
#define Ret_minus_one()             return -1
#define Ret_one()                   return 0
#define LOG_EXIT_2_ARGS(m, v1)      LOG_EXIT(m, v1)

#define Nop()                       asm volatile("#NOP Instruction\n")
#define Not(obj)                    true_false(obj == JS_FALSE || obj == FIXNUM_ZERO || obj == gconsts.g_flonum_nan || obj == gconsts.g_string_empty)
#define GetLiteral(ftable, d1)      (ftable->constants[d1])

#define set_dst(val)               (regbase[r0] = val)

#define Seta(v0)                   set_a(context, v0)
#define Setarray(dst, index, src)  (array_body_index(v0, s1) = v2)

#define IsEmptyCstring(str)        ((str)[0] == '\0')
#define CstrToString(cstr)         cstr_to_string(NULL, (cstr))
#define PutLnChar()                putchar('\n')

#define AllocateJSArray(context, size)  ((JSValue *)gc_malloc((context), sizeof(JSValue) * (size), HTAG_ARRAY_DATA))
#define AllocateCintArray(size)         ((cint *)malloc(sizeof(cint) * (size))
#define AllocateCdoubleArray(size)      ((double *)malloc(sizeof(double) * (size))
#define AllocateCstring(size)           ((char *)malloc(sizeof(char) * (size)))
#define AllocateUnwindProtect(context)  ((UnwindProtect *)gc_malloc(context, sizeof(UnwindProtect), CELLT_UNWIND))

#define int32_to_cint(v)                  ((cint)(v))
#define cint_to_int32(v)                  ((int32_t)(v))
#define cint_to_uint32(v)                 ((uint32_t)(v))
#define fixnum_to_intjsv_t(v)             ((intjsv_t)(v))
#define instructionDisplacementToCint(v)  ((cint)(v))
#define cintToInstructionDisplacement(v)  ((InstructionDisplacement)(v))
#define subscriptToCint(v)                ((cint)(v))
#define uintjsv_tToCint(v)                ((cint)(v))

#define getStack(context, pos)                    (&get_stack((context), (pos)))
#define setFFrameArgument(fr, arr)                (fframe_arguments(fr) = arr)
#define setFFrameLocalsIndex(fr, i, arr)          (fframe_locals_idx(fr, i) = arr)

#define get_jmp_buf_addr() (&jmp_buf)

#define printfDebugArray(str, size, length, to)  (printf((str), (long long)(size), (long long)(length), (long long)(to)))
#define printf_int(str, v)                       (printf((str), (v)))
#define cstringPutCharAt(str, index, c)      ((str)[(index)] = (c))
#define vmdlStringConcat(context, str, append) do{ str = ejs_string_concat(context, str, append); }while(0)

typedef double (* DDFunc)(double);
typedef double (* DDDFunc)(double, double);

#define callFunc1(fn, v1) ((*(fn))(v1))
#define callFunc2(fn, v1, v2) ((*(fn))((v1), (v2)))
#define callDDFunc(fn, v1) callFunc1(fn, v1)
#define callDDDFunc(fn, v1, v2) callFunc2((fn), (v1), (v2))

static inline JSValue iteratorGetNextPropName(JSValue itr) {
  JSValue res = JS_UNDEFINED;
  iterator_get_next_propname(itr, &res);
  return res;
}
static inline JSValue instanceof_helper(JSValue __proto__, JSValue ctor_prototype){
  JSValue ret = JS_FALSE;
  while ((__proto__ = get_prop(__proto__, gconsts.g_string___proto__)) != JS_EMPTY){
    if (__proto__ == ctor_prototype){
      ret = JS_TRUE;
      break;
    }
  }
  return ret;
}
static inline JSValue getCharString(Context *context, cint c){
  char s[2] = {(char)c, '\0'};
  return cstr_to_string(context, s);
}

/*
 * For Pair-Assignment operations
 */

struct Strtol_rettype{cint r0;/* return value of strtol */ char* r1; /* endptr of strtol */};
struct Strtod_rettype{double r0;/* return value of strtod */ char* r1; /* endptr of strtod */};

static inline struct Strtol_rettype Strtol(char *s, int base){
  struct Strtol_rettype ret;
  ret.r0 = strtol(s, &ret.r1, base);
  return ret;
}
static inline struct Strtod_rettype Strtod(char *s){
  struct Strtod_rettype ret;
  ret.r0 = strtod(s, &ret.r1);
  return ret;
}

/*
 * Wrapped instructions
 */

#define Poplocal()				            \
  do {                                \
    int newpc;					              \
    lcall_stack_pop(context, &newpc); \
  } while(0)

#define Makeclosure(context, ss) \
  new_function_object((context), DEBUG_NAME("insn:makeclosure"), gshapes.g_shape_Function, (ss))

#ifdef INLINE_CACHE
static inline void set_global_inl(Context* context, JSValue obj, JSValue prop, JSValue src, InlineCache *ic) {
#ifdef IC_PROF
  ic->count++;
  ic_prof_count++;
  if (ic->prop_name == JS_EMPTY)
    ic->unavailable++;
#endif /* IC_PROF */
  if (ic->prop_name == prop) {
    assert(ic->index <
      object_get_shape(obj)->n_embedded_slots +
      object_get_shape(obj)->n_extension_slots -
      (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
    object_set_prop(obj, ic->index, src);
#ifdef IC_PROF
    ic->hit++;
    ic_prof_hit++;
#endif /* IC_PROF */
  } else {
    assert(ic->prop_name == JS_EMPTY);
    ic->miss++;
    set_prop_with_ic(context, obj, prop, src, ATTR_NONE, ic);
  }
}

#define SetglobalInl(context, prop, src) \
  set_global_inl((context), (context)->global, (prop), (src), &(INSN_CACHE(curfn->index, pc).inl_cache))
#endif /* INLINE_CACHE */
#define Setglobal(context, str, src) \
  set_prop((context), (context)->global, (str), (src), ATTR_NONE)
#define UNUSE(x) ((void)(&x))

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
