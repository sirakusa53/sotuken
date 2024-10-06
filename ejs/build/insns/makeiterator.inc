#define dst regbase[r0]
#define obj v1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(makeiterator,obj);Lmakeiterator0: __attribute__((unused));
TLmakeiterator_string: __attribute__((unused));
TLmakeiterator_builtin: __attribute__((unused));
TLmakeiterator_iterator: __attribute__((unused));
TLmakeiterator_regexp: __attribute__((unused));
TLmakeiterator_flonum: __attribute__((unused));
TLmakeiterator_boolean_object: __attribute__((unused));
TLmakeiterator_number_object: __attribute__((unused));
TLmakeiterator_function: __attribute__((unused));
TLmakeiterator_simple_object: __attribute__((unused));
TLmakeiterator_array: __attribute__((unused));
TLmakeiterator_special: __attribute__((unused));
TLmakeiterator_fixnum: __attribute__((unused));
TLmakeiterator_string_object: __attribute__((unused));
TLmakeiterator_any: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   makeiterator obj dst
     dst : destination register
   $dst = iterator object for iterating $obj
 */

  if (!is_object(obj))
    LOG_EXIT("makeiterator: not an object\n");
  dst = new_iterator(context, obj);
}
#undef dst
#undef obj

