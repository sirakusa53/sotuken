#define d d0

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(jump);Ljump0: __attribute__((unused));
TLjump: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   jump disp
   pc = pc + $disp
 */

  set_pc_relative(d);
}
#undef d

