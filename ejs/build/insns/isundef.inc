#define dst regbase[r0]
#define v v1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(isundef,v);Lisundef0: __attribute__((unused));
TLisundef_fixnum: __attribute__((unused));
TLisundef_boolean_object: __attribute__((unused));
TLisundef_number_object: __attribute__((unused));
TLisundef_array: __attribute__((unused));
TLisundef_any: __attribute__((unused));
TLisundef_regexp: __attribute__((unused));
TLisundef_flonum: __attribute__((unused));
TLisundef_simple_object: __attribute__((unused));
TLisundef_function: __attribute__((unused));
TLisundef_string_object: __attribute__((unused));
TLisundef_string: __attribute__((unused));
TLisundef_builtin: __attribute__((unused));
TLisundef_iterator: __attribute__((unused));
TLisundef_special: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   isundef dst reg
     $dst = $reg == undefined
 */

  dst = true_false(is_undefined(v));
}
#undef dst
#undef v

