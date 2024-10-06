#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(equal,v1,v2);Lequal0: __attribute__((unused));
TLequal_array_any: __attribute__((unused));
TLequal_any_any: __attribute__((unused));
TLequal_string_object_any: __attribute__((unused));
TLequal_function_any: __attribute__((unused));
TLequal_flonum_any: __attribute__((unused));
TLequal_special_any: __attribute__((unused));
TLequal_simple_object_any: __attribute__((unused));
TLequal_number_object_any: __attribute__((unused));
TLequal_fixnum_any: __attribute__((unused));
TLequal_string_any: __attribute__((unused));
TLequal_boolean_object_any: __attribute__((unused));
TLequal_builtin_any: __attribute__((unused));
TLequal_regexp_any: __attribute__((unused));
TLequal_iterator_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(5)
case TV_FIXNUM:
default:
Lequal1: __attribute__((unused));
TLequal_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@13fd(5)
case TV_FLONUM:
Lequal2: __attribute__((unused));
TLequal_fixnum_flonum: __attribute__((unused));
TLequal_special_flonum: __attribute__((unused));
TLequal_flonum_special: __attribute__((unused));
TLequal_flonum_fixnum: __attribute__((unused));
{ // normal_special normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@4e

  dst = JS_FALSE;
}
break;
case TV_GENERIC:
Lequal3: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@685(2)
case HTAGV_ITERATOR:
Lequal4: __attribute__((unused));
TLequal_iterator_iterator: __attribute__((unused));
TLequal_boolean_object_iterator: __attribute__((unused));
TLequal_simple_object_boolean_object: __attribute__((unused));
TLequal_regexp_boolean_object: __attribute__((unused));
TLequal_function_boolean_object: __attribute__((unused));
TLequal_simple_object_function: __attribute__((unused));
TLequal_regexp_function: __attribute__((unused));
TLequal_iterator_special: __attribute__((unused));
TLequal_array_simple_object: __attribute__((unused));
TLequal_builtin_array: __attribute__((unused));
TLequal_regexp_string_object: __attribute__((unused));
TLequal_array_builtin: __attribute__((unused));
TLequal_string_object_simple_object: __attribute__((unused));
TLequal_iterator_string_object: __attribute__((unused));
TLequal_builtin_regexp: __attribute__((unused));
TLequal_string_object_builtin: __attribute__((unused));
TLequal_simple_object_iterator: __attribute__((unused));
TLequal_simple_object_builtin: __attribute__((unused));
TLequal_boolean_object_function: __attribute__((unused));
TLequal_regexp_array: __attribute__((unused));
TLequal_fixnum_iterator: __attribute__((unused));
TLequal_iterator_function: __attribute__((unused));
TLequal_function_string_object: __attribute__((unused));
TLequal_iterator_boolean_object: __attribute__((unused));
TLequal_boolean_object_array: __attribute__((unused));
TLequal_number_object_simple_object: __attribute__((unused));
TLequal_function_regexp: __attribute__((unused));
TLequal_builtin_number_object: __attribute__((unused));
TLequal_string_object_function: __attribute__((unused));
TLequal_boolean_object_boolean_object: __attribute__((unused));
TLequal_regexp_iterator: __attribute__((unused));
TLequal_regexp_regexp: __attribute__((unused));
TLequal_special_iterator: __attribute__((unused));
TLequal_array_regexp: __attribute__((unused));
TLequal_regexp_simple_object: __attribute__((unused));
TLequal_boolean_object_string_object: __attribute__((unused));
TLequal_number_object_regexp: __attribute__((unused));
TLequal_regexp_builtin: __attribute__((unused));
TLequal_string_object_string_object: __attribute__((unused));
TLequal_number_object_string_object: __attribute__((unused));
TLequal_simple_object_number_object: __attribute__((unused));
TLequal_array_iterator: __attribute__((unused));
TLequal_function_iterator: __attribute__((unused));
TLequal_simple_object_regexp: __attribute__((unused));
TLequal_function_simple_object: __attribute__((unused));
TLequal_function_array: __attribute__((unused));
TLequal_builtin_builtin: __attribute__((unused));
TLequal_number_object_array: __attribute__((unused));
TLequal_boolean_object_regexp: __attribute__((unused));
TLequal_string_object_iterator: __attribute__((unused));
TLequal_builtin_boolean_object: __attribute__((unused));
TLequal_string_object_regexp: __attribute__((unused));
TLequal_string_object_number_object: __attribute__((unused));
TLequal_iterator_array: __attribute__((unused));
TLequal_number_object_boolean_object: __attribute__((unused));
TLequal_iterator_number_object: __attribute__((unused));
TLequal_array_number_object: __attribute__((unused));
TLequal_string_object_array: __attribute__((unused));
TLequal_builtin_iterator: __attribute__((unused));
TLequal_builtin_simple_object: __attribute__((unused));
TLequal_builtin_function: __attribute__((unused));
TLequal_iterator_fixnum: __attribute__((unused));
TLequal_string_object_boolean_object: __attribute__((unused));
TLequal_simple_object_array: __attribute__((unused));
TLequal_boolean_object_number_object: __attribute__((unused));
TLequal_simple_object_simple_object: __attribute__((unused));
TLequal_boolean_object_builtin: __attribute__((unused));
TLequal_number_object_iterator: __attribute__((unused));
TLequal_iterator_string: __attribute__((unused));
TLequal_array_string_object: __attribute__((unused));
TLequal_number_object_function: __attribute__((unused));
TLequal_string_iterator: __attribute__((unused));
TLequal_flonum_iterator: __attribute__((unused));
TLequal_function_number_object: __attribute__((unused));
TLequal_array_array: __attribute__((unused));
TLequal_iterator_flonum: __attribute__((unused));
TLequal_iterator_builtin: __attribute__((unused));
TLequal_boolean_object_simple_object: __attribute__((unused));
TLequal_function_function: __attribute__((unused));
TLequal_iterator_regexp: __attribute__((unused));
TLequal_iterator_simple_object: __attribute__((unused));
TLequal_array_boolean_object: __attribute__((unused));
TLequal_array_function: __attribute__((unused));
TLequal_regexp_number_object: __attribute__((unused));
TLequal_function_builtin: __attribute__((unused));
TLequal_number_object_number_object: __attribute__((unused));
TLequal_simple_object_string_object: __attribute__((unused));
TLequal_number_object_builtin: __attribute__((unused));
TLequal_builtin_string_object: __attribute__((unused));
{ // normal_string_object normal_regexp vmgen.newsynth.DecisionDiagram$Leaf@69

  if (v1 == v2) dst = JS_TRUE;
  else dst = JS_FALSE;
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
Lequal5: __attribute__((unused));
TLequal_boolean_object_fixnum: __attribute__((unused));
TLequal_function_fixnum: __attribute__((unused));
TLequal_number_object_fixnum: __attribute__((unused));
TLequal_string_object_fixnum: __attribute__((unused));
TLequal_regexp_fixnum: __attribute__((unused));
TLequal_simple_object_fixnum: __attribute__((unused));
TLequal_builtin_fixnum: __attribute__((unused));
TLequal_array_fixnum: __attribute__((unused));
{ // normal_array normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@86b

  v1 = object_to_primitive(context, v1, HINT_NUMBER);
  dst = true_false(v1 == v2);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@685
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lequal6: __attribute__((unused));
TLequal_string_fixnum: __attribute__((unused));
{ // normal_string normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@bd5

DEFLABEL(STRFIX): __attribute__((unused));
  v1 = string_to_number(context, v1);
  dst = true_false(v1 == v2);
}
break;
case TV_FIXNUM:
default:
Lequal7: __attribute__((unused));
TLequal_fixnum_fixnum: __attribute__((unused));
TLequal_string_string: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@13e8

  if (v1 == v2) dst = JS_TRUE;
  else dst = JS_FALSE;
}
break;
case TV_SPECIAL:
Lequal8: __attribute__((unused));
TLequal_special_fixnum: __attribute__((unused));
{ // normal_special normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@2690

  if (v1 == JS_UNDEFINED) dst = JS_FALSE;
  else if (v1 == JS_NULL) dst = JS_FALSE;
  else {
    if (v1 == JS_TRUE) v1 = FIXNUM_ONE;
    else if (v1 == JS_FALSE) v1 = FIXNUM_ZERO;
    dst = true_false(v1 == v2);
  }
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@13fd
break;
case TV_GENERIC:
Lequal9: __attribute__((unused));
TLequal_any_function: __attribute__((unused));
TLequal_any_number_object: __attribute__((unused));
TLequal_any_array: __attribute__((unused));
TLequal_any_string_object: __attribute__((unused));
TLequal_any_simple_object: __attribute__((unused));
TLequal_any_builtin: __attribute__((unused));
TLequal_any_regexp: __attribute__((unused));
TLequal_any_boolean_object: __attribute__((unused));
TLequal_any_iterator: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(3)
case TV_GENERIC:
goto Lequal4;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
Lequal10: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@7cf(2)
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
Lequal11: __attribute__((unused));
TLequal_flonum_regexp: __attribute__((unused));
TLequal_special_boolean_object: __attribute__((unused));
TLequal_flonum_array: __attribute__((unused));
TLequal_string_regexp: __attribute__((unused));
TLequal_string_builtin: __attribute__((unused));
TLequal_string_string_object: __attribute__((unused));
TLequal_string_simple_object: __attribute__((unused));
TLequal_special_string_object: __attribute__((unused));
TLequal_flonum_boolean_object: __attribute__((unused));
TLequal_flonum_simple_object: __attribute__((unused));
TLequal_flonum_builtin: __attribute__((unused));
TLequal_special_number_object: __attribute__((unused));
TLequal_special_simple_object: __attribute__((unused));
TLequal_special_function: __attribute__((unused));
TLequal_special_array: __attribute__((unused));
TLequal_string_number_object: __attribute__((unused));
TLequal_flonum_number_object: __attribute__((unused));
TLequal_string_array: __attribute__((unused));
TLequal_special_regexp: __attribute__((unused));
TLequal_flonum_function: __attribute__((unused));
TLequal_string_boolean_object: __attribute__((unused));
TLequal_flonum_string_object: __attribute__((unused));
TLequal_special_builtin: __attribute__((unused));
TLequal_string_function: __attribute__((unused));
{ // normal_flonum normal_string_object vmgen.newsynth.DecisionDiagram$Leaf@54

  v2 = object_to_primitive(context, v2, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
case HTAGV_ITERATOR:
goto Lequal4;
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@7cf
break;
case TV_FIXNUM:
default:
Lequal12: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@22c5(2)
case HTAGV_ITERATOR:
goto Lequal4;
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
Lequal13: __attribute__((unused));
TLequal_fixnum_number_object: __attribute__((unused));
TLequal_fixnum_boolean_object: __attribute__((unused));
TLequal_fixnum_function: __attribute__((unused));
TLequal_fixnum_simple_object: __attribute__((unused));
TLequal_fixnum_string_object: __attribute__((unused));
TLequal_fixnum_regexp: __attribute__((unused));
TLequal_fixnum_builtin: __attribute__((unused));
TLequal_fixnum_array: __attribute__((unused));
{ // normal_fixnum normal_boolean_object vmgen.newsynth.DecisionDiagram$Leaf@2be

  v2 = object_to_primitive(context, v2, HINT_NUMBER);
  dst = true_false(v1 == v2);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@22c5
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
case TV_SPECIAL:
Lequal14: __attribute__((unused));
TLequal_any_special: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@191c(5)
case TV_FLONUM:
goto Lequal2;
break;
case TV_GENERIC:
Lequal15: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@d1d(2)
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
Lequal16: __attribute__((unused));
TLequal_regexp_special: __attribute__((unused));
TLequal_simple_object_string: __attribute__((unused));
TLequal_string_object_string: __attribute__((unused));
TLequal_regexp_flonum: __attribute__((unused));
TLequal_string_object_special: __attribute__((unused));
TLequal_array_string: __attribute__((unused));
TLequal_array_special: __attribute__((unused));
TLequal_boolean_object_string: __attribute__((unused));
TLequal_builtin_flonum: __attribute__((unused));
TLequal_function_flonum: __attribute__((unused));
TLequal_simple_object_special: __attribute__((unused));
TLequal_array_flonum: __attribute__((unused));
TLequal_number_object_flonum: __attribute__((unused));
TLequal_simple_object_flonum: __attribute__((unused));
TLequal_regexp_string: __attribute__((unused));
TLequal_string_object_flonum: __attribute__((unused));
TLequal_builtin_special: __attribute__((unused));
TLequal_builtin_string: __attribute__((unused));
TLequal_function_string: __attribute__((unused));
TLequal_function_special: __attribute__((unused));
TLequal_number_object_string: __attribute__((unused));
TLequal_number_object_special: __attribute__((unused));
TLequal_boolean_object_flonum: __attribute__((unused));
TLequal_boolean_object_special: __attribute__((unused));
{ // normal_regexp normal_string vmgen.newsynth.DecisionDiagram$Leaf@16

  v1 = object_to_primitive(context, v1, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
case HTAGV_ITERATOR:
goto Lequal4;
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@d1d
break;
case TV_SPECIAL:
Lequal17: __attribute__((unused));
TLequal_special_special: __attribute__((unused));
{ // normal_special normal_special vmgen.newsynth.DecisionDiagram$Leaf@ed2

  if (v1 == v2) dst = JS_TRUE;
  else dst = true_false((is_undefined(v1) && is_null(v2)) || (is_undefined(v2) && is_null(v1)));
}
break;
case TV_FIXNUM:
default:
Lequal18: __attribute__((unused));
TLequal_fixnum_special: __attribute__((unused));
{ // normal_fixnum normal_special vmgen.newsynth.DecisionDiagram$Leaf@1098

  if (v2 == JS_UNDEFINED) dst = JS_FALSE;
  else if (v2 == JS_NULL) dst = JS_FALSE;
  else {
    if (v2 == JS_TRUE) v2 = FIXNUM_ONE;
    else if (v2 == JS_FALSE) v2 = FIXNUM_ZERO;
    dst = true_false(v1 == v2);
  }
}
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lequal19: __attribute__((unused));
TLequal_string_special: __attribute__((unused));
{ // normal_string normal_special vmgen.newsynth.DecisionDiagram$Leaf@2084

  if (v2 == JS_UNDEFINED) dst = JS_FALSE;
  else if (v2 == JS_NULL) dst = JS_FALSE;
  else {
    if (v2 == JS_TRUE) v2 = FIXNUM_ONE;
    else if (v2 == JS_FALSE) v2 = FIXNUM_ZERO;
    goto USELABEL(STRFIX);
  }
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@191c
break;
case TV_FLONUM:
Lequal20: __attribute__((unused));
TLequal_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@1b4a(4)
case TV_SPECIAL:
case TV_FIXNUM:
default:
goto Lequal2;
break;
case TV_FLONUM:
Lequal21: __attribute__((unused));
TLequal_flonum_flonum: __attribute__((unused));
{ // normal_flonum normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@222

  double x1, x2;
  if (v1 == v2) {
    dst = false_true(is_nan(v1));
  } else {
    x1 = flonum_to_double(v1);
    x2 = flonum_to_double(v2);
    dst = true_false(x1 == x2);
  }
}
break;
case TV_GENERIC:
goto Lequal15;
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lequal22: __attribute__((unused));
TLequal_string_flonum: __attribute__((unused));
{ // normal_string normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@24fe

  v1 = string_to_number(context, v1);
  goto USELABEL(HEAD);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@1b4a
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lequal23: __attribute__((unused));
TLequal_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@2478(5)
case TV_SPECIAL:
Lequal24: __attribute__((unused));
TLequal_special_string: __attribute__((unused));
{ // normal_special normal_string vmgen.newsynth.DecisionDiagram$Leaf@a53

  if (v1 == JS_UNDEFINED) dst = JS_FALSE;
  else if (v1 == JS_NULL) dst = JS_FALSE;
  else {
    if (v1 == JS_TRUE) v1 = FIXNUM_ONE;
    else if (v1 == JS_FALSE) v1 = FIXNUM_ZERO;
    goto USELABEL(FIXSTR);
  }
}
break;
case TV_GENERIC:
goto Lequal15;
break;
case TV_STRING:
case 3:
case 2:
case 1:
goto Lequal7;
break;
case TV_FIXNUM:
default:
Lequal25: __attribute__((unused));
TLequal_fixnum_string: __attribute__((unused));
{ // normal_fixnum normal_string vmgen.newsynth.DecisionDiagram$Leaf@1aaa

DEFLABEL(FIXSTR): __attribute__((unused));
  v2 = string_to_number(context, v2);
  dst = true_false(v1 == v2);
}
break;
case TV_FLONUM:
Lequal26: __attribute__((unused));
TLequal_flonum_string: __attribute__((unused));
{ // normal_flonum normal_string vmgen.newsynth.DecisionDiagram$Leaf@1b17

  v2 = string_to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@2478
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

