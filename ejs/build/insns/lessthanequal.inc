#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(lessthanequal,v1,v2);Llessthanequal0: __attribute__((unused));
TLlessthanequal_number_object_any: __attribute__((unused));
TLlessthanequal_boolean_object_any: __attribute__((unused));
TLlessthanequal_fixnum_any: __attribute__((unused));
TLlessthanequal_string_any: __attribute__((unused));
TLlessthanequal_builtin_any: __attribute__((unused));
TLlessthanequal_special_any: __attribute__((unused));
TLlessthanequal_simple_object_any: __attribute__((unused));
TLlessthanequal_iterator_any: __attribute__((unused));
TLlessthanequal_array_any: __attribute__((unused));
TLlessthanequal_regexp_any: __attribute__((unused));
TLlessthanequal_function_any: __attribute__((unused));
TLlessthanequal_any_any: __attribute__((unused));
TLlessthanequal_flonum_any: __attribute__((unused));
TLlessthanequal_string_object_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(5)
case TV_FLONUM:
Llessthanequal1: __attribute__((unused));
TLlessthanequal_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@54(3)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
Llessthanequal2: __attribute__((unused));
TLlessthanequal_special_flonum: __attribute__((unused));
TLlessthanequal_string_flonum: __attribute__((unused));
TLlessthanequal_string_fixnum: __attribute__((unused));
TLlessthanequal_special_fixnum: __attribute__((unused));
{ // normal_string normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@4ec

  v1 = to_number(context, v1);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Llessthanequal3: __attribute__((unused));
TLlessthanequal_fixnum_flonum: __attribute__((unused));
TLlessthanequal_flonum_fixnum: __attribute__((unused));
TLlessthanequal_flonum_flonum: __attribute__((unused));
{ // normal_fixnum normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@cf3

  double x1 = to_double(context, v1);
  double x2 = to_double(context, v2);
  dst = true_false(x1 <= x2);
}
break;
case TV_GENERIC:
Llessthanequal4: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@21b3(2)
case HTAGV_ITERATOR:
Llessthanequal5: __attribute__((unused));
TLlessthanequal_number_object_string_object: __attribute__((unused));
TLlessthanequal_string_object_string_object: __attribute__((unused));
TLlessthanequal_string_object_function: __attribute__((unused));
TLlessthanequal_iterator_boolean_object: __attribute__((unused));
TLlessthanequal_iterator_function: __attribute__((unused));
TLlessthanequal_iterator_builtin: __attribute__((unused));
TLlessthanequal_iterator_special: __attribute__((unused));
TLlessthanequal_simple_object_number_object: __attribute__((unused));
TLlessthanequal_array_string_object: __attribute__((unused));
TLlessthanequal_regexp_function: __attribute__((unused));
TLlessthanequal_fixnum_iterator: __attribute__((unused));
TLlessthanequal_simple_object_array: __attribute__((unused));
TLlessthanequal_string_object_iterator: __attribute__((unused));
TLlessthanequal_number_object_array: __attribute__((unused));
TLlessthanequal_builtin_simple_object: __attribute__((unused));
TLlessthanequal_boolean_object_number_object: __attribute__((unused));
TLlessthanequal_iterator_number_object: __attribute__((unused));
TLlessthanequal_function_function: __attribute__((unused));
TLlessthanequal_function_number_object: __attribute__((unused));
TLlessthanequal_string_object_array: __attribute__((unused));
TLlessthanequal_function_iterator: __attribute__((unused));
TLlessthanequal_string_object_number_object: __attribute__((unused));
TLlessthanequal_builtin_function: __attribute__((unused));
TLlessthanequal_number_object_function: __attribute__((unused));
TLlessthanequal_iterator_iterator: __attribute__((unused));
TLlessthanequal_function_regexp: __attribute__((unused));
TLlessthanequal_number_object_builtin: __attribute__((unused));
TLlessthanequal_regexp_iterator: __attribute__((unused));
TLlessthanequal_simple_object_function: __attribute__((unused));
TLlessthanequal_boolean_object_simple_object: __attribute__((unused));
TLlessthanequal_string_object_boolean_object: __attribute__((unused));
TLlessthanequal_array_iterator: __attribute__((unused));
TLlessthanequal_builtin_string_object: __attribute__((unused));
TLlessthanequal_array_boolean_object: __attribute__((unused));
TLlessthanequal_function_array: __attribute__((unused));
TLlessthanequal_regexp_builtin: __attribute__((unused));
TLlessthanequal_number_object_boolean_object: __attribute__((unused));
TLlessthanequal_special_iterator: __attribute__((unused));
TLlessthanequal_array_number_object: __attribute__((unused));
TLlessthanequal_boolean_object_iterator: __attribute__((unused));
TLlessthanequal_regexp_number_object: __attribute__((unused));
TLlessthanequal_builtin_builtin: __attribute__((unused));
TLlessthanequal_simple_object_boolean_object: __attribute__((unused));
TLlessthanequal_iterator_simple_object: __attribute__((unused));
TLlessthanequal_builtin_iterator: __attribute__((unused));
TLlessthanequal_boolean_object_regexp: __attribute__((unused));
TLlessthanequal_regexp_boolean_object: __attribute__((unused));
TLlessthanequal_number_object_iterator: __attribute__((unused));
TLlessthanequal_function_string_object: __attribute__((unused));
TLlessthanequal_regexp_simple_object: __attribute__((unused));
TLlessthanequal_boolean_object_builtin: __attribute__((unused));
TLlessthanequal_boolean_object_string_object: __attribute__((unused));
TLlessthanequal_simple_object_builtin: __attribute__((unused));
TLlessthanequal_iterator_array: __attribute__((unused));
TLlessthanequal_string_object_builtin: __attribute__((unused));
TLlessthanequal_boolean_object_array: __attribute__((unused));
TLlessthanequal_simple_object_simple_object: __attribute__((unused));
TLlessthanequal_iterator_string: __attribute__((unused));
TLlessthanequal_iterator_fixnum: __attribute__((unused));
TLlessthanequal_array_array: __attribute__((unused));
TLlessthanequal_regexp_array: __attribute__((unused));
TLlessthanequal_array_regexp: __attribute__((unused));
TLlessthanequal_array_simple_object: __attribute__((unused));
TLlessthanequal_builtin_array: __attribute__((unused));
TLlessthanequal_iterator_string_object: __attribute__((unused));
TLlessthanequal_array_builtin: __attribute__((unused));
TLlessthanequal_simple_object_iterator: __attribute__((unused));
TLlessthanequal_number_object_simple_object: __attribute__((unused));
TLlessthanequal_function_boolean_object: __attribute__((unused));
TLlessthanequal_number_object_number_object: __attribute__((unused));
TLlessthanequal_function_builtin: __attribute__((unused));
TLlessthanequal_iterator_flonum: __attribute__((unused));
TLlessthanequal_iterator_regexp: __attribute__((unused));
TLlessthanequal_flonum_iterator: __attribute__((unused));
TLlessthanequal_regexp_string_object: __attribute__((unused));
TLlessthanequal_function_simple_object: __attribute__((unused));
TLlessthanequal_simple_object_string_object: __attribute__((unused));
TLlessthanequal_number_object_regexp: __attribute__((unused));
TLlessthanequal_boolean_object_boolean_object: __attribute__((unused));
TLlessthanequal_builtin_regexp: __attribute__((unused));
TLlessthanequal_builtin_number_object: __attribute__((unused));
TLlessthanequal_regexp_regexp: __attribute__((unused));
TLlessthanequal_string_iterator: __attribute__((unused));
TLlessthanequal_string_object_simple_object: __attribute__((unused));
TLlessthanequal_builtin_boolean_object: __attribute__((unused));
TLlessthanequal_simple_object_regexp: __attribute__((unused));
TLlessthanequal_string_object_regexp: __attribute__((unused));
TLlessthanequal_array_function: __attribute__((unused));
TLlessthanequal_boolean_object_function: __attribute__((unused));
{ // normal_regexp normal_function vmgen.newsynth.DecisionDiagram$Leaf@4e

  v1 = object_to_primitive(context, v1, HINT_NUMBER);
  v2 = object_to_primitive(context, v2, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_ARRAY:
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
Llessthanequal6: __attribute__((unused));
TLlessthanequal_regexp_flonum: __attribute__((unused));
TLlessthanequal_string_object_string: __attribute__((unused));
TLlessthanequal_simple_object_string: __attribute__((unused));
TLlessthanequal_regexp_special: __attribute__((unused));
TLlessthanequal_simple_object_fixnum: __attribute__((unused));
TLlessthanequal_regexp_fixnum: __attribute__((unused));
TLlessthanequal_string_object_fixnum: __attribute__((unused));
TLlessthanequal_regexp_string: __attribute__((unused));
TLlessthanequal_boolean_object_fixnum: __attribute__((unused));
TLlessthanequal_number_object_fixnum: __attribute__((unused));
TLlessthanequal_number_object_special: __attribute__((unused));
TLlessthanequal_builtin_flonum: __attribute__((unused));
TLlessthanequal_number_object_flonum: __attribute__((unused));
TLlessthanequal_builtin_fixnum: __attribute__((unused));
TLlessthanequal_boolean_object_string: __attribute__((unused));
TLlessthanequal_builtin_special: __attribute__((unused));
TLlessthanequal_number_object_string: __attribute__((unused));
TLlessthanequal_simple_object_flonum: __attribute__((unused));
TLlessthanequal_array_string: __attribute__((unused));
TLlessthanequal_string_object_flonum: __attribute__((unused));
TLlessthanequal_builtin_string: __attribute__((unused));
TLlessthanequal_function_string: __attribute__((unused));
TLlessthanequal_function_special: __attribute__((unused));
TLlessthanequal_array_fixnum: __attribute__((unused));
TLlessthanequal_boolean_object_special: __attribute__((unused));
TLlessthanequal_array_flonum: __attribute__((unused));
TLlessthanequal_array_special: __attribute__((unused));
TLlessthanequal_boolean_object_flonum: __attribute__((unused));
TLlessthanequal_function_flonum: __attribute__((unused));
TLlessthanequal_function_fixnum: __attribute__((unused));
TLlessthanequal_simple_object_special: __attribute__((unused));
TLlessthanequal_string_object_special: __attribute__((unused));
{ // normal_builtin normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@222

  v1 = object_to_primitive(context, v1, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@21b3
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@54
break;
case TV_GENERIC:
Llessthanequal7: __attribute__((unused));
TLlessthanequal_any_string_object: __attribute__((unused));
TLlessthanequal_any_function: __attribute__((unused));
TLlessthanequal_any_simple_object: __attribute__((unused));
TLlessthanequal_any_iterator: __attribute__((unused));
TLlessthanequal_any_builtin: __attribute__((unused));
TLlessthanequal_any_array: __attribute__((unused));
TLlessthanequal_any_boolean_object: __attribute__((unused));
TLlessthanequal_any_regexp: __attribute__((unused));
TLlessthanequal_any_number_object: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@df(2)
case TV_GENERIC:
goto Llessthanequal5;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Llessthanequal8: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@1b7c(2)
case HTAGV_ITERATOR:
goto Llessthanequal5;
break;
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_ARRAY:
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
Llessthanequal9: __attribute__((unused));
TLlessthanequal_string_function: __attribute__((unused));
TLlessthanequal_flonum_builtin: __attribute__((unused));
TLlessthanequal_flonum_function: __attribute__((unused));
TLlessthanequal_special_string_object: __attribute__((unused));
TLlessthanequal_flonum_regexp: __attribute__((unused));
TLlessthanequal_fixnum_string_object: __attribute__((unused));
TLlessthanequal_string_simple_object: __attribute__((unused));
TLlessthanequal_string_boolean_object: __attribute__((unused));
TLlessthanequal_fixnum_regexp: __attribute__((unused));
TLlessthanequal_flonum_simple_object: __attribute__((unused));
TLlessthanequal_string_array: __attribute__((unused));
TLlessthanequal_special_boolean_object: __attribute__((unused));
TLlessthanequal_string_number_object: __attribute__((unused));
TLlessthanequal_fixnum_array: __attribute__((unused));
TLlessthanequal_fixnum_function: __attribute__((unused));
TLlessthanequal_fixnum_boolean_object: __attribute__((unused));
TLlessthanequal_fixnum_simple_object: __attribute__((unused));
TLlessthanequal_flonum_array: __attribute__((unused));
TLlessthanequal_flonum_boolean_object: __attribute__((unused));
TLlessthanequal_special_builtin: __attribute__((unused));
TLlessthanequal_special_simple_object: __attribute__((unused));
TLlessthanequal_fixnum_builtin: __attribute__((unused));
TLlessthanequal_fixnum_number_object: __attribute__((unused));
TLlessthanequal_string_regexp: __attribute__((unused));
TLlessthanequal_special_number_object: __attribute__((unused));
TLlessthanequal_special_array: __attribute__((unused));
TLlessthanequal_string_string_object: __attribute__((unused));
TLlessthanequal_flonum_string_object: __attribute__((unused));
TLlessthanequal_flonum_number_object: __attribute__((unused));
TLlessthanequal_special_function: __attribute__((unused));
TLlessthanequal_special_regexp: __attribute__((unused));
TLlessthanequal_string_builtin: __attribute__((unused));
{ // normal_special normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@69

  v2 = object_to_primitive(context, v2, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@1b7c
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@df
break;
case TV_STRING:
case 3:
case 2:
case 1:
Llessthanequal10: __attribute__((unused));
TLlessthanequal_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@41d(4)
case TV_FLONUM:
case TV_FIXNUM:
default:
Llessthanequal11: __attribute__((unused));
TLlessthanequal_flonum_special: __attribute__((unused));
TLlessthanequal_fixnum_string: __attribute__((unused));
TLlessthanequal_fixnum_special: __attribute__((unused));
TLlessthanequal_flonum_string: __attribute__((unused));
{ // normal_fixnum normal_special vmgen.newsynth.DecisionDiagram$Leaf@5b1

  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
case TV_SPECIAL:
Llessthanequal12: __attribute__((unused));
TLlessthanequal_special_special: __attribute__((unused));
TLlessthanequal_special_string: __attribute__((unused));
TLlessthanequal_string_special: __attribute__((unused));
{ // normal_string normal_special vmgen.newsynth.DecisionDiagram$Leaf@a75

  v1 = to_number(context, v1);
  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
case TV_STRING:
case 3:
case 2:
case 1:
Llessthanequal13: __attribute__((unused));
TLlessthanequal_string_string: __attribute__((unused));
{ // normal_string normal_string vmgen.newsynth.DecisionDiagram$Leaf@1254

  dst = true_false(strcmp(string_to_cstr(v1), string_to_cstr(v2)) <= 0);
}
break;
case TV_GENERIC:
goto Llessthanequal4;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@41d
break;
case TV_SPECIAL:
Llessthanequal14: __attribute__((unused));
TLlessthanequal_any_special: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(3)
case TV_FLONUM:
case TV_FIXNUM:
default:
goto Llessthanequal11;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
goto Llessthanequal12;
break;
case TV_GENERIC:
goto Llessthanequal4;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
case TV_FIXNUM:
default:
Llessthanequal15: __attribute__((unused));
TLlessthanequal_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@1d31(4)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
goto Llessthanequal2;
break;
case TV_FLONUM:
goto Llessthanequal3;
break;
case TV_FIXNUM:
default:
Llessthanequal16: __attribute__((unused));
TLlessthanequal_fixnum_fixnum: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@e83

  dst = true_false(((intjsv_t) v1) <= ((intjsv_t) v2));
}
break;
case TV_GENERIC:
goto Llessthanequal4;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@1d31
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

