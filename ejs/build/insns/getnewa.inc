#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT0(getnewa);Lgetnewa0: __attribute__((unused));
TLgetnewa: __attribute__((unused));
{ // vmgen.newsynth.DecisionDiagram$Leaf@550

  /*
   getnewa dst
     dst : destination register
   $dst = (get_a(context) instanceof Object)? a : dst;
 */

  JSValue a = get_a(context);
  if (is_jsobject(a))
    dst = a;
}
#undef dst

