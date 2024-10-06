#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(getglobalobj);Lgetglobalobj0: __attribute__((unused));
TLgetglobalobj: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   getglobalobj dst
   $dst = global object
 */ 

 dst = context->global;
}
#undef dst

