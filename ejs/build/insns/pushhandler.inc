#define disp d0

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(pushhandler);Lpushhandler0: __attribute__((unused));
TLpushhandler: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

  UnwindProtect *p;

  if (context->exhandler_pool != NULL) {
    p = context->exhandler_pool;
    context->exhandler_pool = p->prev;
  } else {
    save_context();
    p = (UnwindProtect *) gc_malloc(context, sizeof(UnwindProtect),
                                    CELLT_UNWIND);
    update_context();
  }
  p->fp = fp;
  p->pc = pc + disp;
  p->lp = get_lp(context);
  p->lcall_stack_ptr = context->lcall_stack_ptr;
  p->_jmp_buf = &jmp_buf;
  p->prev = context->exhandler_stack_top;
  context->exhandler_stack_top = p;
}
#undef disp

