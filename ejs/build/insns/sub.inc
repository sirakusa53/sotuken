#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(sub,v1,v2);Lsub0: __attribute__((unused));
TLsub_special_any: __attribute__((unused));
TLsub_flonum_any: __attribute__((unused));
TLsub_string_object_any: __attribute__((unused));
TLsub_function_any: __attribute__((unused));
TLsub_number_object_any: __attribute__((unused));
TLsub_any_any: __attribute__((unused));
TLsub_boolean_object_any: __attribute__((unused));
TLsub_simple_object_any: __attribute__((unused));
TLsub_array_any: __attribute__((unused));
TLsub_regexp_any: __attribute__((unused));
TLsub_fixnum_any: __attribute__((unused));
TLsub_string_any: __attribute__((unused));
TLsub_builtin_any: __attribute__((unused));
TLsub_iterator_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(3)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lsub1: __attribute__((unused));
TLsub_any_iterator: __attribute__((unused));
TLsub_any_string_object: __attribute__((unused));
TLsub_any_string: __attribute__((unused));
TLsub_any_array: __attribute__((unused));
TLsub_any_builtin: __attribute__((unused));
TLsub_any_boolean_object: __attribute__((unused));
TLsub_any_number_object: __attribute__((unused));
TLsub_any_special: __attribute__((unused));
TLsub_any_simple_object: __attribute__((unused));
TLsub_any_function: __attribute__((unused));
TLsub_any_regexp: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@17c(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lsub2: __attribute__((unused));
TLsub_simple_object_array: __attribute__((unused));
TLsub_iterator_boolean_object: __attribute__((unused));
TLsub_string_object_array: __attribute__((unused));
TLsub_number_object_simple_object: __attribute__((unused));
TLsub_array_regexp: __attribute__((unused));
TLsub_iterator_number_object: __attribute__((unused));
TLsub_special_string: __attribute__((unused));
TLsub_boolean_object_function: __attribute__((unused));
TLsub_builtin_number_object: __attribute__((unused));
TLsub_number_object_regexp: __attribute__((unused));
TLsub_boolean_object_boolean_object: __attribute__((unused));
TLsub_string_object_boolean_object: __attribute__((unused));
TLsub_string_builtin: __attribute__((unused));
TLsub_boolean_object_array: __attribute__((unused));
TLsub_function_array: __attribute__((unused));
TLsub_number_object_array: __attribute__((unused));
TLsub_array_builtin: __attribute__((unused));
TLsub_iterator_string_object: __attribute__((unused));
TLsub_string_special: __attribute__((unused));
TLsub_array_function: __attribute__((unused));
TLsub_regexp_function: __attribute__((unused));
TLsub_builtin_array: __attribute__((unused));
TLsub_regexp_boolean_object: __attribute__((unused));
TLsub_boolean_object_special: __attribute__((unused));
TLsub_builtin_simple_object: __attribute__((unused));
TLsub_string_object_regexp: __attribute__((unused));
TLsub_string_object_iterator: __attribute__((unused));
TLsub_function_number_object: __attribute__((unused));
TLsub_regexp_simple_object: __attribute__((unused));
TLsub_array_number_object: __attribute__((unused));
TLsub_string_number_object: __attribute__((unused));
TLsub_function_function: __attribute__((unused));
TLsub_boolean_object_string: __attribute__((unused));
TLsub_special_array: __attribute__((unused));
TLsub_regexp_regexp: __attribute__((unused));
TLsub_iterator_simple_object: __attribute__((unused));
TLsub_number_object_builtin: __attribute__((unused));
TLsub_function_special: __attribute__((unused));
TLsub_boolean_object_simple_object: __attribute__((unused));
TLsub_builtin_string_object: __attribute__((unused));
TLsub_iterator_builtin: __attribute__((unused));
TLsub_array_simple_object: __attribute__((unused));
TLsub_function_string_object: __attribute__((unused));
TLsub_string_boolean_object: __attribute__((unused));
TLsub_array_iterator: __attribute__((unused));
TLsub_string_object_string_object: __attribute__((unused));
TLsub_simple_object_special: __attribute__((unused));
TLsub_simple_object_function: __attribute__((unused));
TLsub_function_regexp: __attribute__((unused));
TLsub_simple_object_iterator: __attribute__((unused));
TLsub_string_object_string: __attribute__((unused));
TLsub_builtin_string: __attribute__((unused));
TLsub_function_boolean_object: __attribute__((unused));
TLsub_regexp_array: __attribute__((unused));
TLsub_simple_object_builtin: __attribute__((unused));
TLsub_string_regexp: __attribute__((unused));
TLsub_function_builtin: __attribute__((unused));
TLsub_function_simple_object: __attribute__((unused));
TLsub_number_object_string_object: __attribute__((unused));
TLsub_simple_object_boolean_object: __attribute__((unused));
TLsub_simple_object_number_object: __attribute__((unused));
TLsub_boolean_object_string_object: __attribute__((unused));
TLsub_string_function: __attribute__((unused));
TLsub_simple_object_simple_object: __attribute__((unused));
TLsub_number_object_special: __attribute__((unused));
TLsub_regexp_number_object: __attribute__((unused));
TLsub_array_string_object: __attribute__((unused));
TLsub_iterator_array: __attribute__((unused));
TLsub_regexp_iterator: __attribute__((unused));
TLsub_special_special: __attribute__((unused));
TLsub_special_regexp: __attribute__((unused));
TLsub_simple_object_string_object: __attribute__((unused));
TLsub_array_string: __attribute__((unused));
TLsub_regexp_builtin: __attribute__((unused));
TLsub_string_object_function: __attribute__((unused));
TLsub_number_object_string: __attribute__((unused));
TLsub_string_iterator: __attribute__((unused));
TLsub_iterator_function: __attribute__((unused));
TLsub_boolean_object_number_object: __attribute__((unused));
TLsub_number_object_function: __attribute__((unused));
TLsub_string_string: __attribute__((unused));
TLsub_special_number_object: __attribute__((unused));
TLsub_boolean_object_iterator: __attribute__((unused));
TLsub_builtin_iterator: __attribute__((unused));
TLsub_simple_object_regexp: __attribute__((unused));
TLsub_regexp_special: __attribute__((unused));
TLsub_number_object_boolean_object: __attribute__((unused));
TLsub_iterator_special: __attribute__((unused));
TLsub_special_boolean_object: __attribute__((unused));
TLsub_special_builtin: __attribute__((unused));
TLsub_string_object_simple_object: __attribute__((unused));
TLsub_iterator_regexp: __attribute__((unused));
TLsub_function_string: __attribute__((unused));
TLsub_regexp_string: __attribute__((unused));
TLsub_boolean_object_regexp: __attribute__((unused));
TLsub_string_object_number_object: __attribute__((unused));
TLsub_number_object_number_object: __attribute__((unused));
TLsub_array_array: __attribute__((unused));
TLsub_iterator_string: __attribute__((unused));
TLsub_number_object_iterator: __attribute__((unused));
TLsub_regexp_string_object: __attribute__((unused));
TLsub_special_iterator: __attribute__((unused));
TLsub_string_object_special: __attribute__((unused));
TLsub_special_string_object: __attribute__((unused));
TLsub_boolean_object_builtin: __attribute__((unused));
TLsub_string_simple_object: __attribute__((unused));
TLsub_string_array: __attribute__((unused));
TLsub_simple_object_string: __attribute__((unused));
TLsub_builtin_regexp: __attribute__((unused));
TLsub_iterator_iterator: __attribute__((unused));
TLsub_special_function: __attribute__((unused));
TLsub_string_object_builtin: __attribute__((unused));
TLsub_builtin_builtin: __attribute__((unused));
TLsub_array_boolean_object: __attribute__((unused));
TLsub_function_iterator: __attribute__((unused));
TLsub_builtin_boolean_object: __attribute__((unused));
TLsub_builtin_function: __attribute__((unused));
TLsub_builtin_special: __attribute__((unused));
TLsub_array_special: __attribute__((unused));
TLsub_special_simple_object: __attribute__((unused));
TLsub_string_string_object: __attribute__((unused));
{ // normal_builtin normal_regexp vmgen.newsynth.DecisionDiagram$Leaf@16

  v1 = to_number(context, v1);
  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Lsub3: __attribute__((unused));
TLsub_fixnum_regexp: __attribute__((unused));
TLsub_fixnum_number_object: __attribute__((unused));
TLsub_flonum_string: __attribute__((unused));
TLsub_fixnum_string: __attribute__((unused));
TLsub_fixnum_function: __attribute__((unused));
TLsub_flonum_builtin: __attribute__((unused));
TLsub_flonum_array: __attribute__((unused));
TLsub_fixnum_boolean_object: __attribute__((unused));
TLsub_fixnum_builtin: __attribute__((unused));
TLsub_fixnum_string_object: __attribute__((unused));
TLsub_fixnum_simple_object: __attribute__((unused));
TLsub_fixnum_special: __attribute__((unused));
TLsub_flonum_regexp: __attribute__((unused));
TLsub_flonum_number_object: __attribute__((unused));
TLsub_fixnum_array: __attribute__((unused));
TLsub_fixnum_iterator: __attribute__((unused));
TLsub_flonum_boolean_object: __attribute__((unused));
TLsub_flonum_simple_object: __attribute__((unused));
TLsub_flonum_function: __attribute__((unused));
TLsub_flonum_special: __attribute__((unused));
TLsub_flonum_iterator: __attribute__((unused));
TLsub_flonum_string_object: __attribute__((unused));
{ // normal_fixnum normal_string vmgen.newsynth.DecisionDiagram$Leaf@222

  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@17c
break;
case TV_FLONUM:
Lsub4: __attribute__((unused));
TLsub_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
Lsub5: __attribute__((unused));
TLsub_iterator_flonum: __attribute__((unused));
TLsub_regexp_fixnum: __attribute__((unused));
TLsub_special_fixnum: __attribute__((unused));
TLsub_builtin_fixnum: __attribute__((unused));
TLsub_number_object_flonum: __attribute__((unused));
TLsub_function_fixnum: __attribute__((unused));
TLsub_iterator_fixnum: __attribute__((unused));
TLsub_boolean_object_flonum: __attribute__((unused));
TLsub_string_object_flonum: __attribute__((unused));
TLsub_string_flonum: __attribute__((unused));
TLsub_simple_object_flonum: __attribute__((unused));
TLsub_number_object_fixnum: __attribute__((unused));
TLsub_array_flonum: __attribute__((unused));
TLsub_builtin_flonum: __attribute__((unused));
TLsub_string_fixnum: __attribute__((unused));
TLsub_special_flonum: __attribute__((unused));
TLsub_string_object_fixnum: __attribute__((unused));
TLsub_regexp_flonum: __attribute__((unused));
TLsub_simple_object_fixnum: __attribute__((unused));
TLsub_array_fixnum: __attribute__((unused));
TLsub_function_flonum: __attribute__((unused));
TLsub_boolean_object_fixnum: __attribute__((unused));
{ // normal_regexp normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@df

  v1 = to_number(context, v1);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Lsub6: __attribute__((unused));
TLsub_fixnum_flonum: __attribute__((unused));
TLsub_flonum_fixnum: __attribute__((unused));
TLsub_flonum_flonum: __attribute__((unused));
{ // normal_flonum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@13e8

  dst = double_to_number(context, to_double(context, v1) - to_double(context, v2));
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
case TV_FIXNUM:
default:
Lsub7: __attribute__((unused));
TLsub_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@220f(3)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
case TV_GENERIC:
goto Lsub5;
break;
case TV_FIXNUM:
default:
Lsub8: __attribute__((unused));
TLsub_fixnum_fixnum: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@a53

  cint s = fixnum_to_cint(v1) - fixnum_to_cint(v2);
  dst = cint_to_number(context, s);
}
break;
case TV_FLONUM:
goto Lsub6;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@220f
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

