#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(geterr);Lgeterr0: __attribute__((unused));
TLgeterr: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   geterr dst
     dst : destination register
   $dst = err
   I don't know in which situation this instruction is necessary.
 */ 

 dst = get_err(context);
}
#undef dst

