#define dst regbase[r0]
#define disp d1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(bigprim);Lbigprim0: __attribute__((unused));
TLbigprim: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   number dst disp
   string dst disp
   regexp dst disp
     dst : destination register
     disp : displacement of the constant position from the pc
   $dst = ((JSValur *)insns)[disp]
 */

  // dst = insns[disp].code;
  dst = curfn->constants[disp];
}
#undef dst
#undef disp

