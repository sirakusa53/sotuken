#define dst regbase[r0]
#define src v1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(move,src);Lmove0: __attribute__((unused));
TLmove_boolean_object: __attribute__((unused));
TLmove_string: __attribute__((unused));
TLmove_regexp: __attribute__((unused));
TLmove_fixnum: __attribute__((unused));
TLmove_iterator: __attribute__((unused));
TLmove_function: __attribute__((unused));
TLmove_builtin: __attribute__((unused));
TLmove_array: __attribute__((unused));
TLmove_special: __attribute__((unused));
TLmove_any: __attribute__((unused));
TLmove_flonum: __attribute__((unused));
TLmove_number_object: __attribute__((unused));
TLmove_string_object: __attribute__((unused));
TLmove_simple_object: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   move dst src
     dst : destination register
     src : source register
   $dst = $src
 */
  dst = src;
}
#undef dst
#undef src

