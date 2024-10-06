#define dst regbase[r0]
#define v v1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(isobject,v);Lisobject0: __attribute__((unused));
TLisobject_special: __attribute__((unused));
TLisobject_any: __attribute__((unused));
TLisobject_string: __attribute__((unused));
TLisobject_iterator: __attribute__((unused));
TLisobject_number_object: __attribute__((unused));
TLisobject_regexp: __attribute__((unused));
TLisobject_function: __attribute__((unused));
TLisobject_string_object: __attribute__((unused));
TLisobject_builtin: __attribute__((unused));
TLisobject_simple_object: __attribute__((unused));
TLisobject_flonum: __attribute__((unused));
TLisobject_boolean_object: __attribute__((unused));
TLisobject_array: __attribute__((unused));
TLisobject_fixnum: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   isobject dst reg
     $dst = $reg is an Object or not
 */

  dst = true_false(is_object(v));
}
#undef dst
#undef v

