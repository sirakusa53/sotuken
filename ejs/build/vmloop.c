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

#ifdef USE_VMDL
#include "vmdl-extern.h"
#endif /* USE_VMDL */

static void exhandler_throw(Context *context);
static void lcall_stack_push(Context* context, int pc);
static int lcall_stack_pop(Context* context, int *pc);
#ifdef USE_VMDL
struct LCallStackPop_rettype{int r0;/* status value */ int r1; /* newpc */};
static inline struct LCallStackPop_rettype LCallStackPop(Context *context){
  struct LCallStackPop_rettype ret;
  ret.r0 = lcall_stack_pop(context, &ret.r1);
  return ret;
}
#endif /* USE_VMDL */

#ifdef USE_EMBEDDED_INSTRUCTION
FunctionTable *function_table = (FunctionTable *) &__ejs_function_table_address;
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef DEBUG
extern void print_bytecode(FunctionTable *, Instruction *, int);
#endif /* DEBUG */

#ifdef IC_PROF
int ic_prof_count;
int ic_prof_hit;
#endif /* IC_PROF */

#define NOT_IMPLEMENTED()                                               \
  LOG_EXIT("Sorry, instruction %s has not been implemented yet\n",      \
           insn_nemonic(get_opcode(insn)))
#define type_error(s)  LOG_EXIT("Type error: " s "\n")

#ifdef PROFILE

int *allocate_call_table(int size){
  int *table = (int*)malloc(sizeof(int) * size);
  int i;
  for(i=0; i<size; i++)
    table[i] = 0;
  return table;
}

#define INSN_COUNTN(tsize,tindex,p) \
  do {\
    struct instruction_cache *insn = &(INSN_CACHE(curfn->index, pc)); \
    if(profile_flag != TRUE || insn->logflag != TRUE) break; \
    if(countuniq_flag == TRUE){ \
      if(insn->call_flag_table == NULL) \
        insn->call_flag_table = allocate_call_table((tsize)); \
      if(insn->call_flag_table[(tindex)] == TRUE) \
        break; \
      insn->call_flag_table[(tindex)] = TRUE; \
    } \
    p; \
  } while(0)

#define INSN_COUNT0(iname) \
  INSN_COUNTN(1, \
    TABLE_INDEX(0,0,0), \
    fprintf(prof_stream, "OPERAND: %s\n", #iname))
#define INSN_COUNT1(iname, v0) \
    INSN_COUNTN(TYPE_SIZE, \
      TABLE_INDEX(0,0,to_jsv_typeindex(v0)), \
      fprintf(prof_stream, "OPERAND: %s %s\n", #iname, to_jsv_typename(v0)))
#define INSN_COUNT2(iname, v0, v1) \
    INSN_COUNTN(TYPE_SIZE*TYPE_SIZE, \
      TABLE_INDEX(0,to_jsv_typeindex(v0),to_jsv_typeindex(v1)), \
      fprintf(prof_stream, "OPERAND: %s %s %s\n", #iname, to_jsv_typename(v0), to_jsv_typename(v1)))
#define INSN_COUNT3(iname, v0, v1, v2) \
  INSN_COUNTN(TYPE_SIZE*TYPE_SIZE*TYPE_SIZE, \
    TABLE_INDEX(to_jsv_typeindex(v0),to_jsv_typeindex(v1),to_jsv_typeindex(v2)), \
    fprintf(prof_stream, "OPERAND: %s %s %s %s\n", #iname, to_jsv_typename(v0), to_jsv_typename(v1), to_jsv_typename(v2)))

#else /* PROFILE */

#define INSN_COUNT0(insn)
#define INSN_COUNT1(insn, v0)
#define INSN_COUNT2(insn, v0, v1)
#define INSN_COUNT3(insn, v0, v1, v2)

#endif /* PROFILE */

#ifndef USE_EMBEDDED_INSTRUCTION
inline void make_ilabel(FunctionTable *curfn, void *const *jt) {
  int i, n_insns;
  Instruction *insns;
  n_insns = curfn->n_insns;
  insns = curfn->insns;
  for (i = 0; i < n_insns; i++)
    insns[i].ilabel = jt[get_opcode(insns[i].code)];
  curfn->ilabel_created = true;
}
#endif /* USE_EMBEDDED_INSTRUCTION */

#define INCPC()      do { pc++; insns++; } while (0)
#define PRINTPC()    fprintf(stderr, "pc:%d\n", pc)

#ifdef DEBUG
static int instruction_count = 0;
static void instruction_hook(int pc, int fp,
                             FunctionTable *curfn, Instruction *insns) {
  if (trace_flag == TRUE) {
    printf("%8d pc = %3d, fp = %3d: ", instruction_count, pc, fp);
#ifdef USE_SBC
    if (insns->line == -1)
      printf("         ");
    else
      printf("%4d:%2d: ", insns->line, insns->column);
#endif /* USE_SBC */
    print_bytecode(curfn, insns, 0);
    fflush(stdout);
  }
  instruction_count++;
}
#define INSNLOAD()                                      \
  do {                                                  \
    insn = insns->code;                                 \
    instruction_hook(pc, fp, curfn, insns);             \
  } while (0)
#else /* DEBUG */
#define INSNLOAD() (insn = insns->code)
#endif /* DEBUG */

#ifdef PROFILE
#define ENTER_INSN(x)                                                   \
  do {                                                                  \
    if (INSN_CACHE(curfn->index, pc).logflag == TRUE)                   \
      (INSN_CACHE(curfn->index, pc).count)++;                           \
    asm volatile("#enter insn, loc = " #x "\n\t");                      \
  } while (0)
#else
#define ENTER_INSN(x)                           \
      asm volatile("#enter insn, loc = " #x "\n\t")
#endif

#define NEXT_INSN()                             \
  goto *(insns->ilabel)

#define NEXT_INSN_INCPC()   do {                                \
    INCPC();                                                    \
    INSNLOAD();                                                 \
    NEXT_INSN();                                                \
  } while(0)
#define NEXT_INSN_NOINCPC() do {                \
    INSNLOAD();                                 \
    NEXT_INSN();                                \
  } while(0)

#define save_context() do                            \
    {                                                \
      set_cf(context, curfn);                        \
      set_pc(context, pc);                           \
      set_fp(context,fp);                            \
    } while(0)

#ifdef USE_EMBEDDED_INSTRUCTION
#define MAKE_ILABEL() do { } while(0)
#else /* USE_EMBEDDED_INSTRUCTION */
#define MAKE_ILABEL() do {            \
    if (!curfn->ilabel_created)       \
      make_ilabel(curfn, jump_table); \
  } while (0)
#endif /* USE_EMBEDDED_INSTRUCTION */

#define update_context() do {                           \
    curfn = get_cf(context);                            \
    pc = get_pc(context);                               \
    fp = get_fp(context);                               \
    insns = curfn->insns + pc;                          \
    regbase = (JSValue *)&get_stack(context, fp) - 1;   \
    MAKE_ILABEL();                                      \
  } while (0)

#define load_regs(insn, dst, r1, r2, v1, v2)    \
  dst = get_first_operand_reg(insn),            \
    r1 = get_second_operand_reg(insn),          \
    r2 = get_third_operand_reg(insn),           \
    v1 = regbase[r1],                           \
    v2 = regbase[r2]

#define set_pc_relative(d) (pc += (d), insns += (d))

/*
 * executes the main loop of the vm as a threaded code
 */
int vmrun_threaded(Context* context, int border) {
  FunctionTable *curfn;
  int pc;
  int fp;
  Instruction *insns;
  JSValue *regbase;
  Bytecode insn;
  /* JSValue *locals = NULL; */
#ifdef USE_EMBEDDED_INSTRUCTION
#include "embedded_instructions.inc"
#else /* USE_EMBEDDED_INSTRUCTION */
  static InsnLabel jump_table[] = {
#include "instructions-label.h"
  };
#endif /* USE_EMBEDDED_INSTRUCTION */
  jmp_buf jmp_buf;
  int gc_root_sp;

  gc_root_sp = gc_save_root_stack();
  if (!setjmp(jmp_buf))
    gc_restore_root_stack(gc_root_sp);
  update_context();

  /* load the first instruction (or the current instruction, if
   * an unwind protect is being executed), and jump to its code */
  ENTER_INSN(__LINE__);
  INSNLOAD();
  NEXT_INSN();

#include "vmloop-cases.inc"
}

static void exhandler_throw(Context *context)
{
  UnwindProtect *p = context->exhandler_stack_top;
  JSValue *stack = &get_stack(context, 0);
  int fp;

  if (p == NULL)
    LOG_EXIT("uncaught exception");

  /* 1. unwind function frame, restore FP, and CF */
  context->exhandler_stack_top = p->prev;
  for (fp = get_fp(context); fp != p->fp; fp = get_fp(context)) {
    restore_special_registers(context, stack, fp - 4);
    set_sp(context, fp - 5);
  }

  /* 2. restore LP and local call stack*/
  set_lp(context, p->lp);
  context->lcall_stack_ptr = p->lcall_stack_ptr;

  /* 3. set PC to the handler address */
  set_pc(context, p->pc);

  /* 4. unwind C stack, and go to the entry of vmloop */
  longjmp(*p->_jmp_buf, 1);
}

static void lcall_stack_push(Context* context, int pc)
{
  set_array_element(context, context->lcall_stack,
                    context->lcall_stack_ptr++,
                    cint_to_number(context, (cint) pc));
}

/* 
 * NOTE:
 * The condition is "context->lcall_stack < 1".
 * It should be "context->lcall_stack_ptr < 1" here, shouldn't it?
 */
static int lcall_stack_pop(Context* context, int *pc)
{
  JSValue v;
  if (context->lcall_stack_ptr < 1)
    return -1;
  context->lcall_stack_ptr--;
  v = get_array_prop(context, context->lcall_stack,
                     cint_to_number(context, (cint) context->lcall_stack_ptr));
  *pc = number_to_cint(v);
  return 0;
}

#ifdef IC_PROF
void print_ic_prof(Context *ctx)
{
  int i;
  for (i = 0; i < ctx->nfuncs; i++) {
    FunctionTable *ft = ctx->function_table + i;
    int j;
    for (j = 0; j < ft->n_insns; j++) {
      Instruction *insn = ft->insns + j;
      InlineCache *ic = &(INSN_CACHE(i, j).inl_cache);
      if (ic->count >= 10) {
        printf("IC %03d:%03d ", i, j);
#ifdef WITH_SOURCE_LOCATION
        printf("%03d:%03d ", insn->line, insn->column);
#endif /* WITH_SOURCE_LOCATION */
        printf("%s ",
               get_opcode(insn->code) == GETPROP ? "get " :
               get_opcode(insn->code) == SETPROP ? "set " :
               get_opcode(insn->code) == GETGLOBAL ? "gget" :
               get_opcode(insn->code) == SETGLOBAL ? "gset" : "????");
        printf("count %7d hit %7d miss %7d (radio %f) proto-search %5d\n",
               ic->count,
               ic->hit,
               ic->count - ic->hit,
               ((float) ic->hit) / ic->count,
               ic->proto);
      }
    }
  }
  printf("total count %8d hit %8d (ratio %f)\n",
         ic_prof_count, ic_prof_hit, ((float) ic_prof_hit) / ic_prof_count);
}
#endif /* IC_PROF */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
