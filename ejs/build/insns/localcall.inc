#define d d0

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(localcall);Llocalcall0: __attribute__((unused));
TLlocalcall: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   localcall disp
 */
  lcall_stack_push(context, pc);
  set_pc_relative(d);
}
#undef d

