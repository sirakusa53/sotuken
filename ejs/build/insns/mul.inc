#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(mul,v1,v2);Lmul0: __attribute__((unused));
TLmul_boolean_object_any: __attribute__((unused));
TLmul_function_any: __attribute__((unused));
TLmul_flonum_any: __attribute__((unused));
TLmul_array_any: __attribute__((unused));
TLmul_special_any: __attribute__((unused));
TLmul_string_object_any: __attribute__((unused));
TLmul_iterator_any: __attribute__((unused));
TLmul_regexp_any: __attribute__((unused));
TLmul_builtin_any: __attribute__((unused));
TLmul_simple_object_any: __attribute__((unused));
TLmul_any_any: __attribute__((unused));
TLmul_number_object_any: __attribute__((unused));
TLmul_fixnum_any: __attribute__((unused));
TLmul_string_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(3)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lmul1: __attribute__((unused));
TLmul_any_iterator: __attribute__((unused));
TLmul_any_string_object: __attribute__((unused));
TLmul_any_function: __attribute__((unused));
TLmul_any_regexp: __attribute__((unused));
TLmul_any_simple_object: __attribute__((unused));
TLmul_any_builtin: __attribute__((unused));
TLmul_any_boolean_object: __attribute__((unused));
TLmul_any_array: __attribute__((unused));
TLmul_any_number_object: __attribute__((unused));
TLmul_any_special: __attribute__((unused));
TLmul_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@17c(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lmul2: __attribute__((unused));
TLmul_special_simple_object: __attribute__((unused));
TLmul_simple_object_boolean_object: __attribute__((unused));
TLmul_string_function: __attribute__((unused));
TLmul_builtin_builtin: __attribute__((unused));
TLmul_string_string_object: __attribute__((unused));
TLmul_boolean_object_special: __attribute__((unused));
TLmul_number_object_number_object: __attribute__((unused));
TLmul_function_boolean_object: __attribute__((unused));
TLmul_array_iterator: __attribute__((unused));
TLmul_special_iterator: __attribute__((unused));
TLmul_iterator_function: __attribute__((unused));
TLmul_iterator_string_object: __attribute__((unused));
TLmul_simple_object_iterator: __attribute__((unused));
TLmul_special_array: __attribute__((unused));
TLmul_number_object_iterator: __attribute__((unused));
TLmul_boolean_object_iterator: __attribute__((unused));
TLmul_builtin_regexp: __attribute__((unused));
TLmul_builtin_special: __attribute__((unused));
TLmul_regexp_number_object: __attribute__((unused));
TLmul_builtin_string_object: __attribute__((unused));
TLmul_boolean_object_number_object: __attribute__((unused));
TLmul_function_number_object: __attribute__((unused));
TLmul_string_object_iterator: __attribute__((unused));
TLmul_simple_object_simple_object: __attribute__((unused));
TLmul_function_array: __attribute__((unused));
TLmul_array_string: __attribute__((unused));
TLmul_boolean_object_array: __attribute__((unused));
TLmul_builtin_number_object: __attribute__((unused));
TLmul_function_string_object: __attribute__((unused));
TLmul_regexp_special: __attribute__((unused));
TLmul_number_object_array: __attribute__((unused));
TLmul_simple_object_function: __attribute__((unused));
TLmul_function_builtin: __attribute__((unused));
TLmul_number_object_string_object: __attribute__((unused));
TLmul_string_object_string_object: __attribute__((unused));
TLmul_builtin_iterator: __attribute__((unused));
TLmul_string_object_builtin: __attribute__((unused));
TLmul_string_object_simple_object: __attribute__((unused));
TLmul_regexp_iterator: __attribute__((unused));
TLmul_simple_object_number_object: __attribute__((unused));
TLmul_regexp_builtin: __attribute__((unused));
TLmul_iterator_simple_object: __attribute__((unused));
TLmul_regexp_array: __attribute__((unused));
TLmul_string_regexp: __attribute__((unused));
TLmul_regexp_regexp: __attribute__((unused));
TLmul_string_object_special: __attribute__((unused));
TLmul_array_number_object: __attribute__((unused));
TLmul_special_string_object: __attribute__((unused));
TLmul_function_simple_object: __attribute__((unused));
TLmul_iterator_builtin: __attribute__((unused));
TLmul_array_array: __attribute__((unused));
TLmul_function_regexp: __attribute__((unused));
TLmul_function_iterator: __attribute__((unused));
TLmul_string_object_string: __attribute__((unused));
TLmul_number_object_simple_object: __attribute__((unused));
TLmul_function_special: __attribute__((unused));
TLmul_simple_object_regexp: __attribute__((unused));
TLmul_boolean_object_regexp: __attribute__((unused));
TLmul_iterator_iterator: __attribute__((unused));
TLmul_number_object_regexp: __attribute__((unused));
TLmul_string_object_function: __attribute__((unused));
TLmul_iterator_number_object: __attribute__((unused));
TLmul_iterator_array: __attribute__((unused));
TLmul_iterator_boolean_object: __attribute__((unused));
TLmul_function_function: __attribute__((unused));
TLmul_boolean_object_function: __attribute__((unused));
TLmul_iterator_special: __attribute__((unused));
TLmul_boolean_object_simple_object: __attribute__((unused));
TLmul_string_array: __attribute__((unused));
TLmul_builtin_boolean_object: __attribute__((unused));
TLmul_number_object_special: __attribute__((unused));
TLmul_iterator_regexp: __attribute__((unused));
TLmul_boolean_object_boolean_object: __attribute__((unused));
TLmul_string_iterator: __attribute__((unused));
TLmul_builtin_simple_object: __attribute__((unused));
TLmul_array_function: __attribute__((unused));
TLmul_array_simple_object: __attribute__((unused));
TLmul_string_string: __attribute__((unused));
TLmul_special_string: __attribute__((unused));
TLmul_special_boolean_object: __attribute__((unused));
TLmul_string_object_number_object: __attribute__((unused));
TLmul_number_object_builtin: __attribute__((unused));
TLmul_builtin_string: __attribute__((unused));
TLmul_regexp_simple_object: __attribute__((unused));
TLmul_regexp_function: __attribute__((unused));
TLmul_array_string_object: __attribute__((unused));
TLmul_builtin_function: __attribute__((unused));
TLmul_special_number_object: __attribute__((unused));
TLmul_array_regexp: __attribute__((unused));
TLmul_array_boolean_object: __attribute__((unused));
TLmul_simple_object_builtin: __attribute__((unused));
TLmul_string_object_array: __attribute__((unused));
TLmul_number_object_boolean_object: __attribute__((unused));
TLmul_number_object_string: __attribute__((unused));
TLmul_simple_object_array: __attribute__((unused));
TLmul_string_builtin: __attribute__((unused));
TLmul_simple_object_string_object: __attribute__((unused));
TLmul_special_regexp: __attribute__((unused));
TLmul_regexp_string_object: __attribute__((unused));
TLmul_special_special: __attribute__((unused));
TLmul_simple_object_special: __attribute__((unused));
TLmul_function_string: __attribute__((unused));
TLmul_array_special: __attribute__((unused));
TLmul_string_number_object: __attribute__((unused));
TLmul_boolean_object_string: __attribute__((unused));
TLmul_regexp_boolean_object: __attribute__((unused));
TLmul_string_boolean_object: __attribute__((unused));
TLmul_string_special: __attribute__((unused));
TLmul_string_simple_object: __attribute__((unused));
TLmul_regexp_string: __attribute__((unused));
TLmul_string_object_boolean_object: __attribute__((unused));
TLmul_simple_object_string: __attribute__((unused));
TLmul_boolean_object_builtin: __attribute__((unused));
TLmul_builtin_array: __attribute__((unused));
TLmul_string_object_regexp: __attribute__((unused));
TLmul_iterator_string: __attribute__((unused));
TLmul_number_object_function: __attribute__((unused));
TLmul_boolean_object_string_object: __attribute__((unused));
TLmul_special_builtin: __attribute__((unused));
TLmul_array_builtin: __attribute__((unused));
TLmul_special_function: __attribute__((unused));
{ // normal_builtin normal_regexp vmgen.newsynth.DecisionDiagram$Leaf@16

  v1 = to_number(context, v1);
  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Lmul3: __attribute__((unused));
TLmul_flonum_special: __attribute__((unused));
TLmul_flonum_array: __attribute__((unused));
TLmul_flonum_string_object: __attribute__((unused));
TLmul_flonum_iterator: __attribute__((unused));
TLmul_flonum_boolean_object: __attribute__((unused));
TLmul_flonum_simple_object: __attribute__((unused));
TLmul_flonum_regexp: __attribute__((unused));
TLmul_fixnum_function: __attribute__((unused));
TLmul_fixnum_special: __attribute__((unused));
TLmul_fixnum_array: __attribute__((unused));
TLmul_fixnum_iterator: __attribute__((unused));
TLmul_flonum_builtin: __attribute__((unused));
TLmul_fixnum_builtin: __attribute__((unused));
TLmul_fixnum_regexp: __attribute__((unused));
TLmul_fixnum_number_object: __attribute__((unused));
TLmul_fixnum_string: __attribute__((unused));
TLmul_fixnum_boolean_object: __attribute__((unused));
TLmul_flonum_function: __attribute__((unused));
TLmul_fixnum_string_object: __attribute__((unused));
TLmul_fixnum_simple_object: __attribute__((unused));
TLmul_flonum_number_object: __attribute__((unused));
TLmul_flonum_string: __attribute__((unused));
{ // normal_fixnum normal_string vmgen.newsynth.DecisionDiagram$Leaf@222

  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@17c
break;
case TV_FLONUM:
Lmul4: __attribute__((unused));
TLmul_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lmul5: __attribute__((unused));
TLmul_iterator_flonum: __attribute__((unused));
TLmul_builtin_flonum: __attribute__((unused));
TLmul_string_flonum: __attribute__((unused));
TLmul_simple_object_flonum: __attribute__((unused));
TLmul_function_fixnum: __attribute__((unused));
TLmul_builtin_fixnum: __attribute__((unused));
TLmul_string_fixnum: __attribute__((unused));
TLmul_iterator_fixnum: __attribute__((unused));
TLmul_boolean_object_fixnum: __attribute__((unused));
TLmul_special_fixnum: __attribute__((unused));
TLmul_number_object_fixnum: __attribute__((unused));
TLmul_array_flonum: __attribute__((unused));
TLmul_boolean_object_flonum: __attribute__((unused));
TLmul_regexp_fixnum: __attribute__((unused));
TLmul_string_object_fixnum: __attribute__((unused));
TLmul_simple_object_fixnum: __attribute__((unused));
TLmul_function_flonum: __attribute__((unused));
TLmul_string_object_flonum: __attribute__((unused));
TLmul_array_fixnum: __attribute__((unused));
TLmul_special_flonum: __attribute__((unused));
TLmul_number_object_flonum: __attribute__((unused));
TLmul_regexp_flonum: __attribute__((unused));
{ // normal_regexp normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@df

  v1 = to_number(context, v1);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Lmul6: __attribute__((unused));
TLmul_flonum_flonum: __attribute__((unused));
TLmul_flonum_fixnum: __attribute__((unused));
TLmul_fixnum_flonum: __attribute__((unused));
{ // normal_flonum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@13e8

  double x1 = to_double(context, v1);
  double x2 = to_double(context, v2);
  dst = double_to_number(context, x1 * x2);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
case TV_FIXNUM:
default:
Lmul7: __attribute__((unused));
TLmul_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@220f(3)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
goto Lmul5;
break;
case TV_FIXNUM:
default:
Lmul8: __attribute__((unused));
TLmul_fixnum_fixnum: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@a53

  cint n1, n2;
  n1 = fixnum_to_cint(v1);
  n2 = fixnum_to_cint(v2);
  if (half_fixnum_range(n1) && half_fixnum_range(n2)) {
    cint p = n1 * n2;
    dst = small_cint_to_fixnum(p);
  } else {
    double p = (double) n1 * (double) n2;
    dst = double_to_number(context, p);
  }
}
break;
case TV_FLONUM:
goto Lmul6;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@220f
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

