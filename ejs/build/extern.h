/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef EXTERN_H_
#define EXTERN_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int ftable_flag;
extern int trace_flag;
extern int lastprint_flag;
extern int cputime_flag;
extern int repl_flag;
extern int regstack_limit;

extern eJSUtilTimer *eJSTimer_Mutator;
extern eJSUtilTimer *eJSTimer_GC;

#if defined(USE_OBC) && defined(USE_SBC)
extern int obcsbc;
#endif

extern int run_phase;
extern int generation;

extern FILE *log_stream;

#ifdef PROFILE
extern int profile_flag;
extern int coverage_flag;
extern int icount_flag;
extern int forcelog_flag;
extern int countuniq_flag;
extern FILE *prof_stream;
extern FILE *bprof_stream;

extern int logflag_stack[];
extern int logflag_sp;
#define logflag()   (logflag_sp >= 0 ? logflag_stack[logflag_sp] : 0)
#define TYPE_SIZE 13
#define TABLE_INDEX(v0,v1,v2) ((v0)*TYPE_SIZE*TYPE_SIZE+(v1)*TYPE_SIZE+(v2))

extern int *allocate_call_table(int size);
#endif /* PROFILE */

#ifdef IC_PROF
extern int ic_prof_count;
extern int ic_prof_hit;
#endif /* IC_PROF */

extern InsnInfo insn_info_table[];
extern int numinsts;

#ifdef NEED_INSTRUCTION_CACHE
extern struct instruction_cache **insn_cache;
#endif /* NEED_INSTRUCTION_CACHE */


extern int n_hc;
extern int n_enter_hc;
extern int n_exit_hc;

#ifdef USE_MBED
extern uintptr_t __jsheap_start;
extern uintptr_t __jsheap_end;
#endif /* USE_MBED */

#ifdef USE_EMBEDDED_INSTRUCTION
extern uintptr_t __ejs_function_table_address;

extern FunctionTable *function_table;
#endif /* USE_EMBEDDED_INSTRUCTION */

/*
 * allocate.c
 */
extern FlonumCell *allocate_flonum(Context *, double);
extern StringCell *allocate_string(Context *, uint32_t);
extern void reallocate_array_data(Context *, JSValue, int);
extern Iterator *allocate_iterator(Context *);
extern void allocate_iterator_data(Context *, JSValue, int);
extern ByteArray allocate_byte_array(Context *ctx, size_t size);

/*
 * builtin.c
 */
extern BUILTIN_FUNCTION(builtin_const_true);
extern BUILTIN_FUNCTION(builtin_const_false);
extern BUILTIN_FUNCTION(builtin_const_undefined);
extern BUILTIN_FUNCTION(builtin_const_null);
extern BUILTIN_FUNCTION(builtin_identity);
extern BUILTIN_FUNCTION(builtin_fixnu_to_string);
extern BUILTIN_FUNCTION(builtin_flonum_to_string);
/* extern BUILTIN_FUNCTION(builtin_string_to_index); */

/*
 * builtin-array.c
 */
/* TODO: generate automatically */
#ifdef USE_VMDL
void array_constr(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(array_constr);
#endif /* USE_VMDL */
EXTERN_PROPERTY_TABLES_PCI(Array);

/*
 * builtin-boolean.c
 */
/* TODO: generate automatically */
#ifdef USE_VMDL
void boolean_constr(Context*, cint, cint);
void boolean_constr_nonew(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(boolean_constr);
extern BUILTIN_FUNCTION(boolean_constr_nonew);
#endif /* USE_VMDL */
EXTERN_PROPERTY_TABLES_PCI(Boolean);

/*
 * builtin-global.c
 */
extern BUILTIN_FUNCTION(builtin_not_a_constructor);
EXTERN_PROPERTY_TABLES_I(Global);

/*
 * builtin-math.c
 */
EXTERN_PROPERTY_TABLES_I(Math);

/*
 * builtin-number.c
 */
/* TODO: generate automatically */
#ifdef USE_VMDL
void number_constr(Context*, cint, cint);
void number_constr_nonew(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(number_constr);
extern BUILTIN_FUNCTION(number_constr_nonew);
#endif /* USE_VMDL */
EXTERN_PROPERTY_TABLES_PCI(Number);

/*
 * builtin-string.c
 */
/* TODO: generate automatically */
#ifdef USE_VMDL
void string_constr_nonew(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(string_constr_nonew);
#endif /* USE_VMDL */
extern BUILTIN_FUNCTION(string_constr);
EXTERN_PROPERTY_TABLES_PCI(String);

/*
 * builtin-object.c
 */
extern BUILTIN_FUNCTION(object_constr);
extern BUILTIN_FUNCTION(object_toString);
EXTERN_PROPERTY_TABLES_PCI(Object);

/*
 * builtin-function.c
 */
extern BUILTIN_FUNCTION(function_constr);
extern BUILTIN_FUNCTION(function_prototype_fun);
/* TODO: generate automatically */
#ifdef USE_VMDL
void function_apply(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(function_apply);
#endif /* USE_VMDL */
EXTERN_PROPERTY_TABLES_PCI(Function);
EXTERN_PROPERTY_TABLES_I(Builtin);

/*
 * builtin-regexp.c
 */
/* TODO: generate automatically */
#ifdef USE_REGEXP
#ifdef USE_VMDL
#error "Not implemented yet"
void regexp_constr(Context*, cint, cint);
void regexp_constr_nonew(Context*, cint, cint);
#else /* USE_VMDL */
extern BUILTIN_FUNCTION(regexp_constr);
extern BUILTIN_FUNCTION(regexp_constr_nonew);
#endif /* USE_VMDL */
EXTERN_PROPERTY_TABLES_PCI(RegExp);
#endif /* USE_REGEXP */

/*
 * builtin-performance.c
 */
EXTERN_PROPERTY_TABLES_I(Performance);

/*
 * call.c
 */
extern void call_function(Context *, JSValue, int, int);
extern void call_builtin(Context *, JSValue, int, int, int);
extern void tailcall_function(Context *, JSValue, int, int);
extern void tailcall_builtin(Context *, JSValue, int, int, int);
extern JSValue invoke_function(Context *, JSValue, JSValue, int, JSValue, int);
extern JSValue invoke_builtin(Context *, JSValue, JSValue, int, JSValue, int);
extern JSValue send_function3(Context *, JSValue, JSValue, JSValue, JSValue, JSValue);
extern JSValue send_builtin3(Context *, JSValue, JSValue, JSValue, JSValue, JSValue);
extern JSValue send_function4(Context *, JSValue, JSValue, JSValue, JSValue, JSValue, JSValue);
extern JSValue send_builtin4(Context *, JSValue, JSValue, JSValue, JSValue, JSValue, JSValue);

/*
 * codeloader.c
 */
extern const char *insn_nemonic(int);
extern void init_code_loader(FILE *);
extern void end_code_loader(void);
extern int code_loader(Context *, FunctionTable *, int);
extern JSValue specstr_to_jsvalue(const char *);

/*
 * hcgloader.c
 */
extern void load_hcg(Context *ctx, char *filename);
extern void install_pretransition_hidden_class(void);
extern PropertyMap *find_loaded_property_map(int builtin_id);
extern Shape *find_loaded_prototype_os(int builtin_id);

  
/*
 * context.c
 */
extern void reset_context(Context *, FunctionTable *, int);
extern FunctionFrame *new_frame(Context *, FunctionTable *, FunctionFrame *, int);
extern void pop_special_registers(Context *, int, JSValue *);
extern void init_context(size_t, Context **);
extern void print_backtrace(Context *);
extern const char *insn_nemonic(int);
extern InsnOperandType si_optype(Opcode, int);

#ifdef DEBUG
extern int print_function_table(FunctionTable *, int);
extern void print_constant(FunctionTable *, ConstantDisplacement);
extern void print_bytecode(FunctionTable *, Instruction *, int);
#endif /* DEBUG */


/*
 * conversion.c
 */

#ifdef USE_VMDL

extern double primitive_to_double(JSValue);
extern JSValue primitive_to_string(JSValue);
extern JSValue array_to_string(Context *, JSValue, JSValue);
extern cint toInteger(Context *context, JSValue a);
extern const char *type_name(JSValue);
extern JSValue cint_to_string(cint);
extern JSValue double_to_string(double);

#include "vmdl-generated.h"

#else /* USE_VMDL */

extern JSValue special_to_string(JSValue);
extern JSValue special_to_number(JSValue);
extern JSValue special_to_boolean(JSValue);
/* JSValue special_to_object(JSValue v); */
extern JSValue string_to_number(Context *, JSValue);
/* JSValue string_to_boolean(JSValue v); */
/* JSValue string_to_object(JSValue v); */
extern JSValue fixnum_to_string(JSValue);
extern JSValue flonum_to_string(JSValue);
extern JSValue number_to_string(JSValue);
/* JSValue fixnum_to_boolean(JSValue v); */
/* JSValue flonum_to_boolean(JSValue v); */
/* JSValue fixnum_to_object(JSValue v); */
/* JSValue flonum_to_object(JSValue v); */
extern double primitive_to_double(JSValue);
extern JSValue primitive_to_string(JSValue);
extern JSValue object_to_string(Context *, JSValue);
extern JSValue object_to_number(Context *, JSValue);
extern JSValue object_to_primitive(Context *, JSValue, int);
extern JSValue array_to_string(Context *, JSValue, JSValue);
extern JSValue to_object(Context *, JSValue);
extern JSValue to_string(Context *, JSValue);
extern JSValue to_boolean(JSValue v);
extern JSValue to_number(Context *, JSValue);
extern double to_double(Context *, JSValue);
extern cint number_to_cint(JSValue n);
extern cint toInteger(Context *context, JSValue a);
extern const char *type_name(JSValue);
extern JSValue cint_to_string(cint);

#endif /* USE_VMDL */

extern JSValue specstr_to_jsvalue(const char *);
extern const char *jsvalue_to_specstr(JSValue);

/*
 * hash.c
 */
extern HashTable *hash_create(Context *, unsigned int);
extern int hash_get_with_attribute(HashTable *, HashKey, HashData *, Attribute *attr);
extern int hash_put_property(Context *ctx, HashTable *table,
                             HashKey key, uint32_t index, Attribute attr);
extern void hash_put_transition(Context *ctx, HashTable *table,
                                HashKey key, PropertyMap *pm);

extern int hash_copy(Context *, HashTable *, HashTable *);
extern int hash_delete(HashTable *table, HashKey key);
extern void print_hash_table(HashTable *);

extern HashPropertyIterator createHashPropertyIterator(HashTable *);
extern HashTransitionIterator createHashTransitionIterator(HashTable *);
extern int nextHashTransitionCell(HashTable *table,
                                  HashTransitionIterator *iter,
                                  HashTransitionCell** p);
extern int nextHashPropertyCell(HashTable *table,
                                HashPropertyIterator *iter,
                                JSValue *key,
                                uint32_t *index,
                                Attribute *attr);

/*
 * string.c
 */
extern void init_string_table(unsigned int);
extern JSValue cstr_to_string_ool(Context *context, const char *s);
extern JSValue string_concat_ool(Context *context, JSValue v1, JSValue v2);
extern JSValue string_to_upper_lower_case(Context *ctx, JSValue str, int upper);
extern JSValue string_make_substring(Context *ctx,
				     JSValue str, cint from, cint len);
extern cint string_char_code_at(JSValue str, cint pos);
extern JSValue ejs_string_trim(Context *context, JSValue str);

#ifdef USE_EMBEDDED_INSTRUCTION
extern void load_string_from_function_table(Context *, FunctionTable *);
#endif /* USE_EMBEDDED_INSTRUCTION */


/*
 * init.c
 */
extern void init_global_constants(void);
extern void init_meta_objects(Context *);
extern void init_global_objects(Context *);
extern void init_builtin(Context *);
#ifdef NEED_INSTRUCTION_CACHE
extern void init_instruction_cache_list(size_t size);
extern void init_instruction_cache(int index, size_t size);
#endif /* NEED_INSTRUCTION_CACHE */
#ifndef USE_EMBEDDED_INSTRUCTION
extern void init_function_table_list(FunctionTable [], size_t);
#endif /* USE_EMBEDDED_INSTRUCTION */

/*
 * main.c
 */

/*
 * object.c
 */
#ifdef INLINE_CACHE
extern void set_prop_(Context *ctx, JSValue obj, JSValue name,
                      JSValue v, Attribute att, int skip_setter,
                      InlineCache *ic);
#define set_prop(c,o,n,v,a) set_prop_(c,o,n,v,a,0,NULL)
#define set_prop_with_ic(c,o,n,v,a,ic) set_prop_(c,o,n,v,a,0,ic)
#define set_prop_direct(c,o,n,v,a) set_prop_(c,o,n,v,a,1,NULL)
#else /* INLINE_CACHE */
extern void set_prop_(Context *ctx, JSValue obj, JSValue name,
                      JSValue v, Attribute att, int skip_setter);
#define set_prop(c,o,n,v,a) set_prop_(c,o,n,v,a,0)
#define set_prop_direct(c,o,n,v,a) set_prop_(c,o,n,v,a,1)
#endif /* INLINE_CACHE */
#ifdef INLINE_CACHE
extern JSValue get_prop_with_ic(JSValue obj, JSValue target, JSValue name,
                                InlineCache *ic);
#define get_prop(obj, name)                     \
  get_prop_with_ic(obj, obj, name, NULL)
extern JSValue get_prop_prototype_chain_with_ic(JSValue obj, JSValue name,
                                                InlineCache *ic);
#define get_prop_prototype_chain(obj, name)             \
  get_prop_prototype_chain_with_ic(obj, name, NULL)
#else /* INLINE_CACHE */
extern JSValue get_prop(JSValue obj, JSValue name);
extern JSValue get_prop_prototype_chain(JSValue obj, JSValue name);
#endif /* INLINE_CACHE */

extern JSValue new_simple_object(Context *ctx, const char *name, Shape *os);
extern JSValue new_array_object(Context *ctx, const char *name, Shape *os,
                                size_t size);
extern JSValue new_function_object(Context *ctx, const char *name, Shape *os,
                                   int ft_index);
extern JSValue new_builtin_object(Context *ctx, const char *name, Shape *os,
                                  builtin_function_t cfun,
                                  builtin_function_t cctor, int na);
extern JSValue new_number_object(Context *ctx, const char *name, Shape *os,
                                 JSValue v);
extern JSValue new_string_object(Context *ctx, const char *name, Shape *os,
                                 JSValue v);
extern JSValue new_boolean_object(Context *ctx, const char *name, Shape *os,
                                  JSValue v);
#ifdef USE_REGEXP
extern JSValue new_regexp_object(Context *ctx, const char *name, Shape *os,
                                 char *pat, int flag);
#endif /* USE_REGEXP */

extern PropertyMap *new_property_map(Context *ctx, const char *name,
                                     int n_special_props, int n_props,
                                     int n_user_special_props,
                                     JSValue __proto__, uint8_t flags);
extern void property_map_add_property_entry(Context *ctx, PropertyMap *pm,
                                            JSValue name, uint32_t index,
                                            Attribute attr);
extern void property_map_add_transition(Context *ctx, PropertyMap *pm,
                                        JSValue name, PropertyMap *dest);
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
extern Shape *property_map_find_shape(PropertyMap *pm, size_t n_embedded,
                                      size_t n_extension, AllocSite *as,
                                      int is_proto);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
extern Shape *property_map_find_shape(PropertyMap *pm, size_t n_embedded,
                                      size_t n_extension, int is_proto);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */
#ifdef LOAD_HCG
void property_map_install___proto__(PropertyMap *pm, JSValue __proto__);
#endif /* LOAD_HCG */
  
#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG)
extern Shape *new_object_shape(Context *ctx, const char *name, PropertyMap *pm,
                               int num_embedded, int num_extension,
                               AllocSite *as, int is_proto);
extern JSValue create_array_object(Context *ctx, const char *name, size_t size);
#else /* ALLOC_SITE_CACHE || DUMP_HCG */
extern Shape *new_object_shape(Context *ctx, const char *name, PropertyMap *pm,
                               int num_embedded, int num_extension,
                               int is_proto);
#endif /* ALLOC_SITE_CACHE || DUMP_HCG */

#ifdef PROTO_IC
extern void object_promote_to_prototype(Context *ctx, JSValue obj);
extern int prototype_ic_epoch;
#else /* PROTO_IC */
#define object_promote_to_prototype(ctx, obj)
#endif /* PROTO_IC */

extern JSValue create_simple_object_with_constructor(Context *ctx,
                                                     JSValue ctor);
extern JSValue create_simple_object_with_prototype(Context *ctx,
                                                   JSValue prototype);

#if defined(ALLOC_SITE_CACHE) || defined(DUMP_HCG) || defined(LOAD_HCG)
extern void init_alloc_site(AllocSite *alloc_site);
#endif /* ALLOC_SITE_CACEH || DUMP_HCG || LOAD_HCG */

#ifdef INLINE_CACHE
extern void init_inline_cache(InlineCache *ic);
#endif /* INLINE_CACHE */

#ifdef HC_PROF
extern void hcprof_print_all_hidden_class(void);
#endif /* HC_PROF */

#ifdef VERBOSE_HC
extern int sprint_property_map(char*, PropertyMap*);
#endif /* VERBOSE_HC */

/*
 * object-compat.c
 */
#ifdef INLINE_CACHE
extern JSValue get_object_prop(Context *ctx, JSValue obj, JSValue name,
                               InlineCache *ic);
#else /* INLINE_CACHE */
extern JSValue get_object_prop(Context *ctx, JSValue obj, JSValue name);
#endif /* INLINE_CACHE */
extern JSValue get_array_element(Context * ctx, JSValue obj, cint index);
extern JSValue get_array_prop(Context *ctx, JSValue obj, JSValue name);
extern int has_array_element(JSValue a, cint n);
extern int set_object_prop(Context *ctx, JSValue o, JSValue p, JSValue v);
extern void set_array_element(Context *ctx, JSValue array, cint index,
                              JSValue v);
extern int set_array_prop(Context *ctx, JSValue a, JSValue p, JSValue v);
extern int delete_object_prop(JSValue obj, HashKey key);
extern int delete_array_element(JSValue a, cint n);
extern int iterator_get_next_propname(JSValue iter, JSValue *name);
extern JSValue new_iterator(Context *ctx, JSValue obj);

extern char *space_chomp(char *str);
extern double cstr_to_double(char* cstr);

/*
 * operations.c
 */
extern JSValue slow_add(Context *, JSValue, JSValue);
extern JSValue slow_sub(Context *, JSValue, JSValue);
extern JSValue slow_mul(Context *, JSValue, JSValue);
extern JSValue slow_div(Context *, JSValue, JSValue);
extern JSValue slow_mod(Context *, JSValue, JSValue);
extern JSValue slow_bitand(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_bitor(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_leftshift(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_rightshift(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_unsignedrightshift(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_lessthan(Context *context, JSValue v1, JSValue v2);
extern JSValue slow_lessthanequal(Context *context, JSValue v1, JSValue v2);

/*
 * vmloop.c
 */
extern int vmrun_threaded(Context *, int);

extern void init_builtin_global(Context *);
extern void init_builtin_object(Context *);
extern void init_builtin_array(Context *);
extern void init_builtin_function(Context *);
extern void init_builtin_number(Context *);
extern void init_builtin_string(Context *);
extern void init_builtin_boolean(Context *);
extern void init_builtin_math(Context *);
#ifdef USE_REGEXP
extern void init_builtin_regexp(Context *);
#endif /* USE_REGEXP */

/*
 * cstring.c
 */
extern size_t cstr_length(const char *p);
extern char *cstr_skip_space(char *str);
extern const char *ccstr_skip_space(const char *str);
extern JSValue cstr_parse_int(Context *ctx, const char *p, int radix);
#define PARSE_INT_RADIX_AUTO 0
extern JSValue cstr_parse_float(Context *ctx, const char *p);

/*
 * gc.c
 */
#ifdef GC_PROF
extern uint64_t total_alloc_bytes;
extern uint64_t total_alloc_count;
extern uint64_t pertype_alloc_max[];
extern uint64_t pertype_alloc_bytes[];
extern uint64_t pertype_alloc_count[];
extern uint64_t pertype_live_bytes[];
extern uint64_t pertype_live_count[];
extern uint64_t pertype_collect_bytes[];
extern uint64_t pertype_collect_count[];
#endif /* GC_PROF */

/*
 * log.c
 */
#ifdef USE_MBED
extern void print_end_signal();
#endif /* USE_MBED */

/*
 * iccprof.c
 */
#ifdef ICC_PROF
extern void icc_inc_record1(const char *name, JSValue v1);
extern void icc_inc_record2(const char *name, JSValue v1, JSValue v2);
extern void icc_inc_record3(const char *name, JSValue v1, JSValue v2, JSValue v3);
extern void write_icc_profile(FILE *fp);
#endif /* ICC_PROF */

/*
 * util.c
 */
extern void print_value_simple(Context *, JSValue);
extern void print_value_verbose(Context *, JSValue);
extern void print_value(Context *, JSValue, int);
extern void simple_print(JSValue);
extern void debug_print(Context *, int);

extern const char *to_jsv_typename(JSValue v);
extern int to_jsv_typeindex(JSValue v);

extern int icc_value2index(JSValue value);
extern const char *icc_index2type_name(int index);

extern void calc_rusage_duration(time_t *, suseconds_t *, struct rusage *, struct rusage *);
size_t get_function_table_length(FunctionTable *);

/*
 * mbed_util.c
 */
#ifdef USE_MBED
extern int check_last_execution_status();
#endif /* USE_MBED */

#ifdef __cplusplus
}
#endif

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */

#endif /* EXTERN_H_ */
