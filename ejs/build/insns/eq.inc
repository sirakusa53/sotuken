#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(eq,v1,v2);Leq0: __attribute__((unused));
TLeq_string_object_any: __attribute__((unused));
TLeq_flonum_any: __attribute__((unused));
TLeq_any_any: __attribute__((unused));
TLeq_iterator_any: __attribute__((unused));
TLeq_string_any: __attribute__((unused));
TLeq_fixnum_any: __attribute__((unused));
TLeq_regexp_any: __attribute__((unused));
TLeq_boolean_object_any: __attribute__((unused));
TLeq_array_any: __attribute__((unused));
TLeq_special_any: __attribute__((unused));
TLeq_builtin_any: __attribute__((unused));
TLeq_simple_object_any: __attribute__((unused));
TLeq_function_any: __attribute__((unused));
TLeq_number_object_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_FIXNUM:
default:
case TV_GENERIC:
Leq1: __attribute__((unused));
TLeq_regexp_simple_object: __attribute__((unused));
TLeq_boolean_object_array: __attribute__((unused));
TLeq_fixnum_regexp: __attribute__((unused));
TLeq_regexp_function: __attribute__((unused));
TLeq_boolean_object_regexp: __attribute__((unused));
TLeq_array_number_object: __attribute__((unused));
TLeq_array_array: __attribute__((unused));
TLeq_any_array: __attribute__((unused));
TLeq_special_string_object: __attribute__((unused));
TLeq_string_array: __attribute__((unused));
TLeq_boolean_object_iterator: __attribute__((unused));
TLeq_function_builtin: __attribute__((unused));
TLeq_simple_object_special: __attribute__((unused));
TLeq_simple_object_flonum: __attribute__((unused));
TLeq_string_object_special: __attribute__((unused));
TLeq_string_object_string_object: __attribute__((unused));
TLeq_fixnum_number_object: __attribute__((unused));
TLeq_string_object_array: __attribute__((unused));
TLeq_array_iterator: __attribute__((unused));
TLeq_special_array: __attribute__((unused));
TLeq_function_boolean_object: __attribute__((unused));
TLeq_any_simple_object: __attribute__((unused));
TLeq_string_regexp: __attribute__((unused));
TLeq_function_fixnum: __attribute__((unused));
TLeq_number_object_function: __attribute__((unused));
TLeq_array_boolean_object: __attribute__((unused));
TLeq_number_object_array: __attribute__((unused));
TLeq_builtin_array: __attribute__((unused));
TLeq_string_number_object: __attribute__((unused));
TLeq_function_string: __attribute__((unused));
TLeq_array_flonum: __attribute__((unused));
TLeq_simple_object_array: __attribute__((unused));
TLeq_flonum_iterator: __attribute__((unused));
TLeq_array_builtin: __attribute__((unused));
TLeq_builtin_simple_object: __attribute__((unused));
TLeq_string_object_boolean_object: __attribute__((unused));
TLeq_fixnum_string_object: __attribute__((unused));
TLeq_special_boolean_object: __attribute__((unused));
TLeq_builtin_function: __attribute__((unused));
TLeq_flonum_fixnum: __attribute__((unused));
TLeq_fixnum_function: __attribute__((unused));
TLeq_flonum_string: __attribute__((unused));
TLeq_array_string_object: __attribute__((unused));
TLeq_iterator_string_object: __attribute__((unused));
TLeq_boolean_object_string_object: __attribute__((unused));
TLeq_any_string_object: __attribute__((unused));
TLeq_builtin_builtin: __attribute__((unused));
TLeq_regexp_special: __attribute__((unused));
TLeq_regexp_number_object: __attribute__((unused));
TLeq_regexp_string: __attribute__((unused));
TLeq_string_object_flonum: __attribute__((unused));
TLeq_function_array: __attribute__((unused));
TLeq_function_iterator: __attribute__((unused));
TLeq_regexp_builtin: __attribute__((unused));
TLeq_simple_object_simple_object: __attribute__((unused));
TLeq_special_fixnum: __attribute__((unused));
TLeq_simple_object_boolean_object: __attribute__((unused));
TLeq_any_fixnum: __attribute__((unused));
TLeq_any_iterator: __attribute__((unused));
TLeq_special_regexp: __attribute__((unused));
TLeq_special_number_object: __attribute__((unused));
TLeq_special_function: __attribute__((unused));
TLeq_builtin_regexp: __attribute__((unused));
TLeq_flonum_simple_object: __attribute__((unused));
TLeq_iterator_iterator: __attribute__((unused));
TLeq_array_regexp: __attribute__((unused));
TLeq_boolean_object_boolean_object: __attribute__((unused));
TLeq_array_fixnum: __attribute__((unused));
TLeq_string_fixnum: __attribute__((unused));
TLeq_flonum_number_object: __attribute__((unused));
TLeq_special_simple_object: __attribute__((unused));
TLeq_number_object_regexp: __attribute__((unused));
TLeq_any_function: __attribute__((unused));
TLeq_string_object_builtin: __attribute__((unused));
TLeq_simple_object_string_object: __attribute__((unused));
TLeq_fixnum_simple_object: __attribute__((unused));
TLeq_builtin_fixnum: __attribute__((unused));
TLeq_builtin_boolean_object: __attribute__((unused));
TLeq_special_builtin: __attribute__((unused));
TLeq_fixnum_iterator: __attribute__((unused));
TLeq_iterator_string: __attribute__((unused));
TLeq_any_regexp: __attribute__((unused));
TLeq_function_flonum: __attribute__((unused));
TLeq_simple_object_fixnum: __attribute__((unused));
TLeq_string_object_string: __attribute__((unused));
TLeq_regexp_flonum: __attribute__((unused));
TLeq_number_object_fixnum: __attribute__((unused));
TLeq_flonum_string_object: __attribute__((unused));
TLeq_fixnum_fixnum: __attribute__((unused));
TLeq_flonum_boolean_object: __attribute__((unused));
TLeq_builtin_iterator: __attribute__((unused));
TLeq_builtin_string_object: __attribute__((unused));
TLeq_boolean_object_fixnum: __attribute__((unused));
TLeq_fixnum_array: __attribute__((unused));
TLeq_fixnum_flonum: __attribute__((unused));
TLeq_flonum_function: __attribute__((unused));
TLeq_boolean_object_function: __attribute__((unused));
TLeq_boolean_object_string: __attribute__((unused));
TLeq_simple_object_regexp: __attribute__((unused));
TLeq_boolean_object_flonum: __attribute__((unused));
TLeq_simple_object_number_object: __attribute__((unused));
TLeq_array_function: __attribute__((unused));
TLeq_iterator_boolean_object: __attribute__((unused));
TLeq_flonum_builtin: __attribute__((unused));
TLeq_any_builtin: __attribute__((unused));
TLeq_fixnum_string: __attribute__((unused));
TLeq_boolean_object_builtin: __attribute__((unused));
TLeq_boolean_object_number_object: __attribute__((unused));
TLeq_string_boolean_object: __attribute__((unused));
TLeq_number_object_iterator: __attribute__((unused));
TLeq_special_special: __attribute__((unused));
TLeq_iterator_flonum: __attribute__((unused));
TLeq_builtin_number_object: __attribute__((unused));
TLeq_number_object_flonum: __attribute__((unused));
TLeq_iterator_simple_object: __attribute__((unused));
TLeq_number_object_boolean_object: __attribute__((unused));
TLeq_boolean_object_simple_object: __attribute__((unused));
TLeq_fixnum_builtin: __attribute__((unused));
TLeq_any_boolean_object: __attribute__((unused));
TLeq_string_object_iterator: __attribute__((unused));
TLeq_number_object_string_object: __attribute__((unused));
TLeq_string_flonum: __attribute__((unused));
TLeq_function_function: __attribute__((unused));
TLeq_regexp_iterator: __attribute__((unused));
TLeq_special_flonum: __attribute__((unused));
TLeq_iterator_function: __attribute__((unused));
TLeq_fixnum_special: __attribute__((unused));
TLeq_boolean_object_special: __attribute__((unused));
TLeq_flonum_special: __attribute__((unused));
TLeq_builtin_special: __attribute__((unused));
TLeq_regexp_boolean_object: __attribute__((unused));
TLeq_regexp_array: __attribute__((unused));
TLeq_builtin_flonum: __attribute__((unused));
TLeq_string_builtin: __attribute__((unused));
TLeq_iterator_special: __attribute__((unused));
TLeq_simple_object_iterator: __attribute__((unused));
TLeq_regexp_fixnum: __attribute__((unused));
TLeq_string_function: __attribute__((unused));
TLeq_flonum_regexp: __attribute__((unused));
TLeq_function_number_object: __attribute__((unused));
TLeq_array_special: __attribute__((unused));
TLeq_string_object_regexp: __attribute__((unused));
TLeq_iterator_builtin: __attribute__((unused));
TLeq_string_special: __attribute__((unused));
TLeq_string_object_number_object: __attribute__((unused));
TLeq_number_object_number_object: __attribute__((unused));
TLeq_simple_object_function: __attribute__((unused));
TLeq_function_string_object: __attribute__((unused));
TLeq_array_simple_object: __attribute__((unused));
TLeq_regexp_regexp: __attribute__((unused));
TLeq_any_string: __attribute__((unused));
TLeq_string_string_object: __attribute__((unused));
TLeq_special_iterator: __attribute__((unused));
TLeq_string_string: __attribute__((unused));
TLeq_function_regexp: __attribute__((unused));
TLeq_regexp_string_object: __attribute__((unused));
TLeq_number_object_special: __attribute__((unused));
TLeq_iterator_regexp: __attribute__((unused));
TLeq_special_string: __attribute__((unused));
TLeq_string_iterator: __attribute__((unused));
TLeq_function_special: __attribute__((unused));
TLeq_iterator_number_object: __attribute__((unused));
TLeq_fixnum_boolean_object: __attribute__((unused));
TLeq_simple_object_builtin: __attribute__((unused));
TLeq_string_object_function: __attribute__((unused));
TLeq_number_object_simple_object: __attribute__((unused));
TLeq_string_object_simple_object: __attribute__((unused));
TLeq_number_object_builtin: __attribute__((unused));
TLeq_number_object_string: __attribute__((unused));
TLeq_builtin_string: __attribute__((unused));
TLeq_string_object_fixnum: __attribute__((unused));
TLeq_string_simple_object: __attribute__((unused));
TLeq_flonum_array: __attribute__((unused));
TLeq_function_simple_object: __attribute__((unused));
TLeq_array_string: __attribute__((unused));
TLeq_any_special: __attribute__((unused));
TLeq_iterator_array: __attribute__((unused));
TLeq_iterator_fixnum: __attribute__((unused));
TLeq_simple_object_string: __attribute__((unused));
TLeq_any_number_object: __attribute__((unused));
{ // normal_simple_object normal_iterator vmgen.newsynth.DecisionDiagram$Leaf@4e

  if (v1 == v2) dst = false_true(is_nan(v1));
  else dst = JS_FALSE;
}
break;
case TV_FLONUM:
Leq2: __attribute__((unused));
TLeq_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_FIXNUM:
default:
case TV_GENERIC:
goto Leq1;
break;
case TV_FLONUM:
Leq3: __attribute__((unused));
TLeq_flonum_flonum: __attribute__((unused));
{ // normal_flonum normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@dbb

  double x1 = flonum_to_double(v1);
  double x2 = flonum_to_double(v2);
  dst = true_false(x1 == x2);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

