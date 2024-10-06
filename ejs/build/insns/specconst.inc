#define dst regbase[r0]
#define imm i1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(specconst);Lspecconst0: __attribute__((unused));
TLspecconst: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   specconst dst imm
    dst : destination register
    imm : immediate value of the special constant
   $dst = imm
 */

  dst = imm;
}
#undef dst
#undef imm

