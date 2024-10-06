#define dst regbase[r0]
#define itr v1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(nextpropnameidx,itr);Lnextpropnameidx0: __attribute__((unused));
TLnextpropnameidx_string: __attribute__((unused));
TLnextpropnameidx_regexp: __attribute__((unused));
TLnextpropnameidx_builtin: __attribute__((unused));
TLnextpropnameidx_flonum: __attribute__((unused));
TLnextpropnameidx_number_object: __attribute__((unused));
TLnextpropnameidx_array: __attribute__((unused));
TLnextpropnameidx_string_object: __attribute__((unused));
TLnextpropnameidx_special: __attribute__((unused));
TLnextpropnameidx_boolean_object: __attribute__((unused));
TLnextpropnameidx_simple_object: __attribute__((unused));
TLnextpropnameidx_function: __attribute__((unused));
TLnextpropnameidx_any: __attribute__((unused));
TLnextpropnameidx_iterator: __attribute__((unused));
TLnextpropnameidx_fixnum: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   nextpropnameidx itr dst
     itr : iterator for enumerating properties in obj
     dst : destination
   $dst = the next property name of $obj in $itr
 */

  JSValue res = JS_UNDEFINED;
  iterator_get_next_propname(itr, &res);
  dst = res;
}
#undef dst
#undef itr

