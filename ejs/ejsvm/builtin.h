/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#define BUILTIN_FUNCTION(x) void x(Context *context, cint fp, cint na)
#define BUILTIN_FUNCTION_STATIC(x) static BUILTIN_FUNCTION(x)

#define get_args()  ((JSValue *)(&(get_stack(context, fp))))

#define builtin_prologue() JSValue *args __attribute__((unused)) = get_args()

#define not_implemented(s)                                              \
  LOG_EXIT("%s is not implemented yet\n", (s)); set_a(context, JS_UNDEFINED)

/*
 * #define builtin_prologue() \
 * int fp; JSValue *args; fp = get_fp(context); args = get_args()
 */

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct obj_builtin_prop {
  const char *name;
  builtin_function_t fn;
  int na;
  Attribute attr;
} ObjBuiltinProp;

typedef struct obj_double_prop {
  const char *name;
  double value;
  Attribute attr;
  int index;
} ObjDoubleProp;

typedef struct obj_gconsts_prop {
  const char *name;
  JSValue *addr;
  Attribute attr;
} ObjGconstsProp;

#define DEFINE_PROPERTY_TABLE_SIZES_PCI(T)                              \
int T ## Prototype_num_builtin_props =                                  \
  sizeof(T ## Prototype_builtin_props) / sizeof(ObjBuiltinProp);        \
int T ## Prototype_num_double_props =                                   \
  sizeof(T ## Prototype_double_props) / sizeof(ObjDoubleProp);          \
int T ## Prototype_num_gconsts_props =                                  \
  sizeof(T ## Prototype_gconsts_props) / sizeof(ObjGconstsProp);        \
DEFINE_PROPERTY_TABLE_SIZES_CI(T)

#define DEFINE_PROPERTY_TABLE_SIZES_CI(T)                               \
int T ## Constructor_num_builtin_props =                                \
  sizeof(T ## Constructor_builtin_props) / sizeof(ObjBuiltinProp);      \
int T ## Constructor_num_double_props =                                 \
  sizeof(T ## Constructor_double_props) / sizeof(ObjDoubleProp);        \
int T ## Constructor_num_gconsts_props =                                \
  sizeof(T ## Constructor_gconsts_props) / sizeof(ObjGconstsProp);      \
DEFINE_PROPERTY_TABLE_SIZES_I(T)

#define DEFINE_PROPERTY_TABLE_SIZES_I(T)                \
int T ## _num_builtin_props =                           \
  sizeof(T ## _builtin_props) / sizeof(ObjBuiltinProp); \
int T ## _num_double_props =                            \
  sizeof(T ## _double_props) / sizeof(ObjDoubleProp);   \
int T ## _num_gconsts_props =                           \
  sizeof(T ## _gconsts_props) / sizeof(ObjGconstsProp)

#define EXTERN_PROPERTY_TABLES_PCI(T)                          \
extern ObjBuiltinProp T ## Prototype_builtin_props[];          \
extern ObjDoubleProp  T ## Prototype_double_props[];           \
extern ObjGconstsProp T ## Prototype_gconsts_props[];          \
extern int            T ## Prototype_num_builtin_props;        \
extern int            T ## Prototype_num_double_props;         \
extern int            T ## Prototype_num_gconsts_props;        \
EXTERN_PROPERTY_TABLES_CI(T)

#define EXTERN_PROPERTY_TABLES_CI(T)                           \
extern ObjBuiltinProp T ## Constructor_builtin_props[];        \
extern ObjDoubleProp  T ## Constructor_double_props[];         \
extern ObjGconstsProp T ## Constructor_gconsts_props[];        \
extern int            T ## Constructor_num_builtin_props;      \
extern int            T ## Constructor_num_double_props;       \
extern int            T ## Constructor_num_gconsts_props;      \
EXTERN_PROPERTY_TABLES_I(T)

#define EXTERN_PROPERTY_TABLES_I(T)                            \
extern ObjBuiltinProp T ## _builtin_props[];                   \
extern ObjDoubleProp  T ## _double_props[];                    \
extern ObjGconstsProp T ## _gconsts_props[];                   \
extern int            T ## _num_builtin_props;                 \
extern int            T ## _num_double_props;                  \
extern int            T ## _num_gconsts_props

#ifdef PROFILE

#define jstypename_na_cmp(v,i,na) (i <= na ? to_jsv_typename(v) : "none")

#define BUILTIN_COUNT0(iname, na) \
  ((void) (profile_flag == TRUE && fprintf(bprof_stream, "OPERAND: %s\n", #iname)) )
#define BUILTIN_COUNT1(iname, na, v0) \
  ((void) (profile_flag == TRUE && fprintf(bprof_stream, "OPERAND: %s %s\n", #iname, \
    jstypename_na_cmp(v0, 0, na))) )
#define BUILTIN_COUNT2(iname, na, v0, v1) \
  ((void) (profile_flag == TRUE && fprintf(bprof_stream, "OPERAND: %s %s %s\n", #iname, \
    jstypename_na_cmp(v0, 0, na), jstypename_na_cmp(v1, 1, na))) )
#define BUILTIN_COUNT3(iname, na, v0, v1, v2) \
  ((void) (profile_flag == TRUE && fprintf(bprof_stream, "OPERAND: %s %s %s %s\n", #iname, \
    jstypename_na_cmp(v0, 0, na), jstypename_na_cmp(v1, 1, na), jstypename_na_cmp(v2, 2, na))) )

#else /* PROFILE */

#define BUILTIN_COUNT0(insn, na)
#define BUILTIN_COUNT1(insn, na, v0)
#define BUILTIN_COUNT2(insn, na, v0, v1)
#define BUILTIN_COUNT3(insn, na, v0, v1, v2)

#endif /* PROFILE */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
