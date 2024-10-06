#define dst regbase[r0]
#define link i1
#define index_ s2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(getlocal);Lgetlocal0: __attribute__((unused));
TLgetlocal: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   getlocal dst link index_
   $dst = value of the index-th local variable in the link-th function frame
 */

  FunctionFrame *fr;
  int i;
  fr = get_lp(context);
  for (i = 0; i < link; i++) fr = fframe_prev(fr);
  dst = fframe_locals_idx(fr, index_);
}
#undef dst
#undef link
#undef index_

