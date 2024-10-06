
DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(pophandler);Lpophandler0: __attribute__((unused));
TLpophandler: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

  UnwindProtect *p;
  p = context->exhandler_stack_top;
  if (p != NULL) {
    context->exhandler_stack_top = p->prev;
    p->prev = context->exhandler_pool;
    context->exhandler_pool = p;
  }
}

