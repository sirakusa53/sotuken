#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(geta);Lgeta0: __attribute__((unused));
TLgeta: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   geta dst
     dst : destination register
   $dst = a
 */
  dst = get_a(context);
}
#undef dst

