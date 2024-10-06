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

static Context *allocate_context(size_t);

/*
 * creates a new function frame
 */
FunctionFrame *new_frame(Context *ctx, FunctionTable *ft,
                         FunctionFrame *env, int nl) {
  FunctionFrame *frame;
  JSValue *locals;
  int i;

#ifdef DEBUG
  nl++;
#endif /* DEBUG */
  GC_PUSH(env);
  frame = (FunctionFrame *)
    gc_malloc(ctx, sizeof(FunctionFrame) + BYTES_IN_JSVALUE * nl,
              CELLT_FUNCTION_FRAME);
  GC_POP(env);
  frame->prev_frame = env;
  frame->arguments = JS_UNDEFINED;
  frame->nlocals = nl;
  locals = frame->locals;
  for (i = 0; i < nl; i++)
    locals[i] = JS_UNDEFINED;
  return frame;
}

/*
 * initializes special registers in a context
 */
void init_special_registers(SpecialRegisters *spreg){
  spreg->fp = 0;
  spreg->cf = NULL;
  spreg->lp = NULL;
  spreg->sp = -1;
  spreg->pc = 0;
  spreg->a = JS_UNDEFINED;
  spreg->err = JS_UNDEFINED;
  spreg->iserr = false;
}

void reset_context(Context *ctx, FunctionTable *ftab, int func_index) {
  init_special_registers(&(ctx->spreg));
  ctx->function_table = ftab;
  set_cf(ctx, &(ftab[func_index]));
  set_lp(ctx, new_frame(NULL, ftab, NULL, 0));

  ctx->global = gconsts.g_global;
  ctx->exhandler_stack_top = NULL;
  ctx->exhandler_pool = NULL;
  ctx->lcall_stack = new_array_object(NULL, DEBUG_NAME("allocate_context"),
                                      gshapes.g_shape_Array, 0);
  ctx->lcall_stack_ptr = 0;
}

/*
 * Create context with minimum initialisation to create objects.
 * Note that global objects are not created because their creation needs
 * context.  Bottom half of initialisation is done in reset_context.
 */
void init_context(size_t stack_limit, Context **context)
{
  Context *c;

  c = allocate_context(stack_limit);
  c->nfuncs = 0;
  *context = c;
#if defined(HC_SKIP_INTERNAL) || defined(WEAK_SHAPE_LIST)
  c->property_map_roots = NULL;
#endif /* HC_SKIP_INTERNAL || WEAK_SHAPE_LIST */
}

static Context *allocate_context(size_t stack_size)
{
  Context *ctx = (Context *) malloc(sizeof(Context));
  ctx->stack = (JSValue *) malloc(sizeof(JSValue) * stack_size);
  return ctx;
}

static void print_single_frame(Context *ctx, int index)
{
  fprintf(log_stream,
          "  #%d %p LP:%p, PC: %d, SP:%d, FP:%d (#i = %d, #c = %d)\n",
          index,
          ctx->spreg.cf,
          ctx->spreg.lp,
          ctx->spreg.pc,
          ctx->spreg.sp,
          ctx->spreg.fp,
          ctx->spreg.cf->n_insns,
          ctx->spreg.cf->n_constants);
}

void print_backtrace(Context *ctx)
{
  JSValue *stack = &get_stack(ctx, 0);
  int i = 0;
  fprintf(log_stream, "backtrace:\n");
  print_single_frame(ctx, i++);
  while (ctx->spreg.fp != 0) {
    ctx->spreg.sp = ctx->spreg.fp - 5;
    restore_special_registers(ctx, stack, ctx->spreg.fp - 4);
    print_single_frame(ctx, i++);
  };
}



/*
 * Need to generate automatically because this validator
 * depends on type representation.
 */
int is_valid_JSValue(JSValue x)
{
  return 1;
}

void check_stack_invariant(Context *ctx)
{
  int sp = get_sp(ctx);
  int fp = get_fp(ctx);
  int pc __attribute__((unused)) = get_pc(ctx);
  FunctionTable *cf __attribute__((unused)) = get_cf(ctx);
  FunctionFrame *lp __attribute__((unused)) = get_lp(ctx);
  int i;

  assert(is_valid_JSValue(get_global(ctx)));
  assert(is_valid_JSValue(get_a(ctx)));
  assert(!is_err(ctx) || is_valid_JSValue(ctx->spreg.err));
  while (1) {
    for (i = sp; i >= fp; i--)
      assert(is_valid_JSValue(get_stack(ctx,i)));
    if (fp == 0)
      break;
    sp = fp - 1;
    fp = (int) (intjsv_t) get_stack(ctx, sp); sp--;
    lp = jsv_to_function_frame(get_stack(ctx, sp)); sp--;
    pc = (int) (intjsv_t) get_stack(ctx, sp); sp--;
    cf = (FunctionTable *) jsv_to_noheap_ptr(get_stack(ctx, sp)); sp--;
  }
}


/*
 * information of instructions
 */
InsnInfo insn_info_table[] = {
#include "instructions-table.h"
};

/*
 * number of instructions
 */
int numinsts = sizeof(insn_info_table) / sizeof(InsnInfo);

const char *insn_nemonic(int opcode) {
  return insn_info_table[opcode].insn_name;
}

InsnOperandType si_optype(Opcode oc, int i) {
  switch (i) {
  case 0:
    return insn_info_table[oc].op0;
  case 1:
    return insn_info_table[oc].op1;
  case 2:
    return insn_info_table[oc].op2;
  default:
    return OPTYPE_ERROR;
  }
}

#ifdef DEBUG
int print_function_table(FunctionTable *ftable, int nfuncs) {
  int i, j;
  JSValue *lit;

  printf("number of functions = %d\n", nfuncs);
  for (i = 0; i < nfuncs; i++) {
    printf("function #%d\n", i);
    printf("call_entry: %d\n", ftable[i].call_entry);
    printf("send_entry: %d\n", ftable[i].send_entry);
    printf("n_locals: %d\n" ,ftable[i].n_locals);
    printf("n_insns: %d\n", ftable[i].n_insns);
    printf("n_constants: %d\n", ftable[i].n_constants);
    for (j = 0; j < ftable[i].n_insns; j++) {
      printf("%03d: %" PRIByteCode " --- ", j, ftable[i].insns[j].code);
      print_bytecode(&(ftable[i]), ftable[i].insns, j);
    }
    lit = ftable[i].constants;
    for (j = 0; j < ftable[i].n_constants; j++) {
      JSValue o;
      o = lit[j];
      printf("%03d: %" PRIJSValue " --- ", j, o);
      if (is_flonum(o))
        printf("FLONUM %lf\n", flonum_value(o));
      else if (is_fixnum(o))
        printf("FIXNUM %" PRIcint " (%p)\n", fixnum_to_cint(o), lit);
      else if (is_string(o))
        printf("STRING \"%s\"\n", string_value(o));
#ifdef USE_REGEXP
      else if (is_regexp(o))
        printf("REGEXP \"%s\"\n", get_jsregexp_pattern(o));
#endif /* USE_REGEXP */
      else
        printf("Unexpected JSValue\n");
    }
  }
  return 0;
}

/*
 * prints a bytecode instruction
 */
void print_constant(FunctionTable *ftable, ConstantDisplacement disp) {
  JSValue o;
  o = ftable->constants[disp];
  if (is_flonum(o))
    printf(" %f", flonum_value(o));
  else if (is_fixnum(o))
    printf(" %" PRIcint " (%d, 0x%" PRIJSValue ", %p)", fixnum_to_cint(o), disp, o, ftable->constants);
  else if (is_string(o))
    printf(" \"%s\"", string_value(o));
#ifdef USE_REGEXP
  else if (is_regexp(o)) {
    printf(" \"%s\"", get_jsregexp_pattern(o));
    if (get_jsregexp_global(o)) printf("g");
    if (get_jsregexp_ignorecase(o)) printf("i");
    if (get_jsregexp_multiline(o)) printf("m");
  }
#endif /* USE_REGEXP */
  else
    printf(" ???");
}

void print_bytecode(FunctionTable* ftable, Instruction *insns, int pc) {
  Bytecode code;
  Opcode oc;
  OperandType t;

  code = insns[pc].code;
  oc = get_opcode(code);
  t = insn_info_table[oc].otype;
  printf("%" PRIByteCode " ", code);
#ifdef PROFILE
  printf("%s%s", insn_info_table[oc].insn_name,
         INSN_CACHE(ftable->index, pc).logflag == TRUE? "_log": "");
#else
  printf("%s", insn_info_table[oc].insn_name);
#endif
  switch (t) {
  case SMALLPRIMITIVE:
    {
      SmallPrimitive imm;
      printf(" %d", get_first_operand_reg(code));
      switch (oc) {
      case FIXNUM:
        imm = get_small_immediate(code);
        printf(" %d", imm);
        break;
      case SPECCONST:
        imm = get_small_immediate(code);
        printf(" %s", jsvalue_to_specstr(imm));
        break;
      default:
        printf(" ???");
        break;
      }
    }
    break;
  case BIGPRIMITIVE:
    {
      printf(" %d", get_first_operand_reg(code));
      print_constant(ftable, get_big_constant_disp(code));
    }
    break;
  case THREEOP:
    {
      InsnOperandType type;
      int i;
      for (i = 0; i < 3; i++) {
        type = si_optype(oc, i);
        if (type == STR || type == NUM) {
          ConstantDisplacement disp =
            ((i == 0)? get_first_operand_constant_disp(code):
             (i == 1)? get_second_operand_constant_disp(code):
             get_third_operand_constant_disp(code));
          print_constant(ftable, disp);
        } else if (type == LIT) {
          int k = ((i == 0)? get_first_operand_int(code):
                   (i == 1)? get_second_operand_int(code):
                   get_third_operand_int(code));
          printf(" %d (LIT)", k);
        } else if (type == SPEC) {
          int k = ((i == 0)? get_first_operand_int(code):
                   (i == 1)? get_second_operand_int(code):
                   get_third_operand_int(code));
          SmallPrimitive imm = get_small_immediate(k);
          printf(" %s", jsvalue_to_specstr(imm));
        } else {   /* REG NONE */
          Register r;
          r = ((i == 0)? get_first_operand_reg(code):
               (i == 1)? get_second_operand_reg(code):
               get_third_operand_reg(code));
          printf(" %d (REG)", r);
        }
      }
    }
    break;
  case TWOOP:
    {
      Register dst, r1;
      dst = get_first_operand_reg(code);
      r1 = get_second_operand_reg(code);
      printf(" %d %d", dst, r1);
    }
    break;
  case ONEOP:
    {
      Register dst;
      dst = get_first_operand_reg(code);
      printf(" %d", dst);
    }
    break;
  case ZEROOP:
    break;
  case UNCONDJUMP:
  case TRYOP:
    {
      InstructionDisplacement disp = get_operand_instruction_disp(code);
      printf(" %d", pc + disp);
    }
    break;
  case CONDJUMP:
    {
      Register r = get_first_operand_reg(code);
      InstructionDisplacement disp = get_operand_instruction_disp(code);
      printf(" %d %d", r, pc + disp);
    }
    break;
  case GETVAR:
    {
      Register dst;
      Subscript link, ss;
      link = get_first_operand_subscr(code);
      ss = get_second_operand_subscr(code);
      dst = get_third_operand_reg(code);
      printf(" %d %d %d", link, ss, dst);
    }
    break;
  case SETVAR:
    {
      Register src;
      Subscript link, ss;
      link = get_first_operand_subscr(code);
      ss = get_second_operand_subscr(code);
      src = get_third_operand_reg(code);
      printf(" %d %d %d", link, ss, src);
    }
    break;
  case MAKECLOSUREOP:
    {
      Register dst;
      Subscript ss;
      dst = get_first_operand_reg(code);
      ss = get_second_operand_subscr(code);
      printf(" %d %d", dst, ss);
    }
    break;
  case CALLOP:
    {
      Register f;
      int na;
      f = get_first_operand_reg(code);
      na = get_second_operand_int(code);
      printf(" %d %d", f, na);
    }
    break;
  case UNKNOWNOP:
    break;
  }
  putchar('\n');
}
#endif /* DEBUG */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
