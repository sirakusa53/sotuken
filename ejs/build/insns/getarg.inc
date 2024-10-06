#define dst regbase[r0]
#define link i1
#define index_ s2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(getarg);Lgetarg0: __attribute__((unused));
TLgetarg: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

/*
   getarg dst link index_
   $dst = value of the index-th argument in the link-th function frame
 */

  FunctionFrame *fr;
  JSValue arguments;
  int i;
  fr = get_lp(context);
  for (i = 0; i < link; i++) {
    fr = fframe_prev(fr);
  }
  arguments = fframe_arguments(fr);
  dst = get_array_element(context, arguments, index_);
}
#undef dst
#undef link
#undef index_

