#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(lessthan,v1,v2);Llessthan0: __attribute__((unused));
TLlessthan_string_object_any: __attribute__((unused));
TLlessthan_fixnum_any: __attribute__((unused));
TLlessthan_any_any: __attribute__((unused));
TLlessthan_function_any: __attribute__((unused));
TLlessthan_string_any: __attribute__((unused));
TLlessthan_flonum_any: __attribute__((unused));
TLlessthan_boolean_object_any: __attribute__((unused));
TLlessthan_array_any: __attribute__((unused));
TLlessthan_iterator_any: __attribute__((unused));
TLlessthan_builtin_any: __attribute__((unused));
TLlessthan_special_any: __attribute__((unused));
TLlessthan_simple_object_any: __attribute__((unused));
TLlessthan_regexp_any: __attribute__((unused));
TLlessthan_number_object_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(5)
case TV_SPECIAL:
Llessthan1: __attribute__((unused));
TLlessthan_any_special: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@41d(3)
case TV_GENERIC:
Llessthan2: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@7c(2)
case HTAGV_ITERATOR:
Llessthan3: __attribute__((unused));
TLlessthan_string_object_regexp: __attribute__((unused));
TLlessthan_simple_object_string_object: __attribute__((unused));
TLlessthan_regexp_array: __attribute__((unused));
TLlessthan_builtin_simple_object: __attribute__((unused));
TLlessthan_string_object_simple_object: __attribute__((unused));
TLlessthan_boolean_object_simple_object: __attribute__((unused));
TLlessthan_regexp_regexp: __attribute__((unused));
TLlessthan_iterator_number_object: __attribute__((unused));
TLlessthan_simple_object_boolean_object: __attribute__((unused));
TLlessthan_array_array: __attribute__((unused));
TLlessthan_string_object_iterator: __attribute__((unused));
TLlessthan_iterator_array: __attribute__((unused));
TLlessthan_iterator_string: __attribute__((unused));
TLlessthan_function_number_object: __attribute__((unused));
TLlessthan_array_simple_object: __attribute__((unused));
TLlessthan_string_object_function: __attribute__((unused));
TLlessthan_number_object_function: __attribute__((unused));
TLlessthan_boolean_object_string_object: __attribute__((unused));
TLlessthan_iterator_fixnum: __attribute__((unused));
TLlessthan_builtin_iterator: __attribute__((unused));
TLlessthan_flonum_iterator: __attribute__((unused));
TLlessthan_builtin_string_object: __attribute__((unused));
TLlessthan_function_string_object: __attribute__((unused));
TLlessthan_iterator_regexp: __attribute__((unused));
TLlessthan_iterator_flonum: __attribute__((unused));
TLlessthan_iterator_special: __attribute__((unused));
TLlessthan_function_boolean_object: __attribute__((unused));
TLlessthan_builtin_regexp: __attribute__((unused));
TLlessthan_iterator_function: __attribute__((unused));
TLlessthan_simple_object_builtin: __attribute__((unused));
TLlessthan_number_object_builtin: __attribute__((unused));
TLlessthan_simple_object_function: __attribute__((unused));
TLlessthan_array_boolean_object: __attribute__((unused));
TLlessthan_function_function: __attribute__((unused));
TLlessthan_array_regexp: __attribute__((unused));
TLlessthan_string_iterator: __attribute__((unused));
TLlessthan_regexp_number_object: __attribute__((unused));
TLlessthan_number_object_simple_object: __attribute__((unused));
TLlessthan_array_function: __attribute__((unused));
TLlessthan_array_string_object: __attribute__((unused));
TLlessthan_builtin_number_object: __attribute__((unused));
TLlessthan_simple_object_regexp: __attribute__((unused));
TLlessthan_builtin_function: __attribute__((unused));
TLlessthan_boolean_object_function: __attribute__((unused));
TLlessthan_iterator_iterator: __attribute__((unused));
TLlessthan_boolean_object_number_object: __attribute__((unused));
TLlessthan_string_object_boolean_object: __attribute__((unused));
TLlessthan_iterator_simple_object: __attribute__((unused));
TLlessthan_function_array: __attribute__((unused));
TLlessthan_regexp_function: __attribute__((unused));
TLlessthan_number_object_boolean_object: __attribute__((unused));
TLlessthan_simple_object_array: __attribute__((unused));
TLlessthan_function_builtin: __attribute__((unused));
TLlessthan_boolean_object_builtin: __attribute__((unused));
TLlessthan_number_object_iterator: __attribute__((unused));
TLlessthan_string_object_builtin: __attribute__((unused));
TLlessthan_fixnum_iterator: __attribute__((unused));
TLlessthan_boolean_object_array: __attribute__((unused));
TLlessthan_number_object_array: __attribute__((unused));
TLlessthan_number_object_string_object: __attribute__((unused));
TLlessthan_boolean_object_boolean_object: __attribute__((unused));
TLlessthan_regexp_simple_object: __attribute__((unused));
TLlessthan_string_object_string_object: __attribute__((unused));
TLlessthan_special_iterator: __attribute__((unused));
TLlessthan_simple_object_number_object: __attribute__((unused));
TLlessthan_string_object_array: __attribute__((unused));
TLlessthan_number_object_number_object: __attribute__((unused));
TLlessthan_builtin_boolean_object: __attribute__((unused));
TLlessthan_simple_object_simple_object: __attribute__((unused));
TLlessthan_array_builtin: __attribute__((unused));
TLlessthan_iterator_builtin: __attribute__((unused));
TLlessthan_number_object_regexp: __attribute__((unused));
TLlessthan_function_iterator: __attribute__((unused));
TLlessthan_boolean_object_regexp: __attribute__((unused));
TLlessthan_iterator_string_object: __attribute__((unused));
TLlessthan_regexp_string_object: __attribute__((unused));
TLlessthan_function_regexp: __attribute__((unused));
TLlessthan_regexp_iterator: __attribute__((unused));
TLlessthan_regexp_builtin: __attribute__((unused));
TLlessthan_string_object_number_object: __attribute__((unused));
TLlessthan_simple_object_iterator: __attribute__((unused));
TLlessthan_function_simple_object: __attribute__((unused));
TLlessthan_builtin_array: __attribute__((unused));
TLlessthan_regexp_boolean_object: __attribute__((unused));
TLlessthan_boolean_object_iterator: __attribute__((unused));
TLlessthan_array_number_object: __attribute__((unused));
TLlessthan_iterator_boolean_object: __attribute__((unused));
TLlessthan_array_iterator: __attribute__((unused));
TLlessthan_builtin_builtin: __attribute__((unused));
{ // normal_number_object normal_boolean_object vmgen.newsynth.DecisionDiagram$Leaf@16

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
Llessthan4: __attribute__((unused));
TLlessthan_regexp_string: __attribute__((unused));
TLlessthan_function_special: __attribute__((unused));
TLlessthan_string_object_string: __attribute__((unused));
TLlessthan_simple_object_string: __attribute__((unused));
TLlessthan_number_object_special: __attribute__((unused));
TLlessthan_regexp_flonum: __attribute__((unused));
TLlessthan_simple_object_fixnum: __attribute__((unused));
TLlessthan_regexp_special: __attribute__((unused));
TLlessthan_string_object_fixnum: __attribute__((unused));
TLlessthan_number_object_flonum: __attribute__((unused));
TLlessthan_array_flonum: __attribute__((unused));
TLlessthan_boolean_object_flonum: __attribute__((unused));
TLlessthan_builtin_fixnum: __attribute__((unused));
TLlessthan_number_object_fixnum: __attribute__((unused));
TLlessthan_simple_object_flonum: __attribute__((unused));
TLlessthan_builtin_special: __attribute__((unused));
TLlessthan_builtin_flonum: __attribute__((unused));
TLlessthan_string_object_flonum: __attribute__((unused));
TLlessthan_builtin_string: __attribute__((unused));
TLlessthan_array_special: __attribute__((unused));
TLlessthan_number_object_string: __attribute__((unused));
TLlessthan_boolean_object_string: __attribute__((unused));
TLlessthan_function_string: __attribute__((unused));
TLlessthan_boolean_object_special: __attribute__((unused));
TLlessthan_simple_object_special: __attribute__((unused));
TLlessthan_string_object_special: __attribute__((unused));
TLlessthan_array_string: __attribute__((unused));
TLlessthan_function_flonum: __attribute__((unused));
TLlessthan_array_fixnum: __attribute__((unused));
TLlessthan_regexp_fixnum: __attribute__((unused));
TLlessthan_boolean_object_fixnum: __attribute__((unused));
TLlessthan_function_fixnum: __attribute__((unused));
{ // normal_array normal_special vmgen.newsynth.DecisionDiagram$Leaf@54

  v1 = object_to_primitive(context, v1, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@7c
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
Llessthan5: __attribute__((unused));
TLlessthan_string_special: __attribute__((unused));
TLlessthan_special_special: __attribute__((unused));
TLlessthan_special_string: __attribute__((unused));
{ // normal_string normal_special vmgen.newsynth.DecisionDiagram$Leaf@281

  v1 = to_number(context, v1);
  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
Llessthan6: __attribute__((unused));
TLlessthan_fixnum_string: __attribute__((unused));
TLlessthan_flonum_special: __attribute__((unused));
TLlessthan_fixnum_special: __attribute__((unused));
TLlessthan_flonum_string: __attribute__((unused));
{ // normal_fixnum normal_special vmgen.newsynth.DecisionDiagram$Leaf@7a5

  v2 = to_number(context, v2);
  goto USELABEL(HEAD);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@41d
break;
case TV_FIXNUM:
default:
Llessthan7: __attribute__((unused));
TLlessthan_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@b26(4)
case TV_GENERIC:
goto Llessthan2;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
Llessthan8: __attribute__((unused));
TLlessthan_string_fixnum: __attribute__((unused));
TLlessthan_special_fixnum: __attribute__((unused));
TLlessthan_string_flonum: __attribute__((unused));
TLlessthan_special_flonum: __attribute__((unused));
{ // normal_special normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@f3

  v1 = to_number(context, v1);
  goto USELABEL(HEAD);
}
break;
case TV_FLONUM:
Llessthan9: __attribute__((unused));
TLlessthan_fixnum_flonum: __attribute__((unused));
TLlessthan_flonum_fixnum: __attribute__((unused));
TLlessthan_flonum_flonum: __attribute__((unused));
{ // normal_flonum normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@bfb

  double x1 = to_double(context, v1);
  double x2 = to_double(context, v2);
  dst = true_false(x1 < x2);
}
break;
case TV_FIXNUM:
default:
Llessthan10: __attribute__((unused));
TLlessthan_fixnum_fixnum: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@207f

  dst = true_false(((intjsv_t) v1) < ((intjsv_t) v2));
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@b26
break;
case TV_FLONUM:
Llessthan11: __attribute__((unused));
TLlessthan_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@173c(3)
case TV_GENERIC:
goto Llessthan2;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_SPECIAL:
goto Llessthan8;
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
goto Llessthan9;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@173c
break;
case TV_GENERIC:
Llessthan12: __attribute__((unused));
TLlessthan_any_array: __attribute__((unused));
TLlessthan_any_number_object: __attribute__((unused));
TLlessthan_any_regexp: __attribute__((unused));
TLlessthan_any_string_object: __attribute__((unused));
TLlessthan_any_simple_object: __attribute__((unused));
TLlessthan_any_boolean_object: __attribute__((unused));
TLlessthan_any_builtin: __attribute__((unused));
TLlessthan_any_function: __attribute__((unused));
TLlessthan_any_iterator: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@1986(2)
case TV_GENERIC:
goto Llessthan3;
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Llessthan13: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@1679(2)
case HTAGV_ITERATOR:
goto Llessthan3;
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
Llessthan14: __attribute__((unused));
TLlessthan_string_function: __attribute__((unused));
TLlessthan_fixnum_string_object: __attribute__((unused));
TLlessthan_flonum_function: __attribute__((unused));
TLlessthan_special_simple_object: __attribute__((unused));
TLlessthan_string_builtin: __attribute__((unused));
TLlessthan_flonum_builtin: __attribute__((unused));
TLlessthan_string_simple_object: __attribute__((unused));
TLlessthan_fixnum_array: __attribute__((unused));
TLlessthan_string_number_object: __attribute__((unused));
TLlessthan_flonum_string_object: __attribute__((unused));
TLlessthan_special_array: __attribute__((unused));
TLlessthan_special_function: __attribute__((unused));
TLlessthan_fixnum_regexp: __attribute__((unused));
TLlessthan_fixnum_function: __attribute__((unused));
TLlessthan_special_boolean_object: __attribute__((unused));
TLlessthan_special_number_object: __attribute__((unused));
TLlessthan_special_builtin: __attribute__((unused));
TLlessthan_flonum_boolean_object: __attribute__((unused));
TLlessthan_fixnum_simple_object: __attribute__((unused));
TLlessthan_string_boolean_object: __attribute__((unused));
TLlessthan_flonum_array: __attribute__((unused));
TLlessthan_flonum_number_object: __attribute__((unused));
TLlessthan_special_string_object: __attribute__((unused));
TLlessthan_fixnum_builtin: __attribute__((unused));
TLlessthan_string_array: __attribute__((unused));
TLlessthan_flonum_simple_object: __attribute__((unused));
TLlessthan_string_regexp: __attribute__((unused));
TLlessthan_flonum_regexp: __attribute__((unused));
TLlessthan_fixnum_boolean_object: __attribute__((unused));
TLlessthan_string_string_object: __attribute__((unused));
TLlessthan_special_regexp: __attribute__((unused));
TLlessthan_fixnum_number_object: __attribute__((unused));
{ // normal_string normal_simple_object vmgen.newsynth.DecisionDiagram$Leaf@241

  v2 = object_to_primitive(context, v2, HINT_NUMBER);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@1679
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@1986
break;
case TV_STRING:
case 3:
case 2:
case 1:
Llessthan15: __attribute__((unused));
TLlessthan_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@1c98(4)
case TV_GENERIC:
goto Llessthan2;
break;
case TV_SPECIAL:
goto Llessthan5;
break;
case TV_FLONUM:
case TV_FIXNUM:
default:
goto Llessthan6;
break;
case TV_STRING:
case 3:
case 2:
case 1:
Llessthan16: __attribute__((unused));
TLlessthan_string_string: __attribute__((unused));
{ // normal_string normal_string vmgen.newsynth.DecisionDiagram$Leaf@a14

  dst = true_false(strcmp(string_to_cstr(v1), string_to_cstr(v2)) < 0);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@1c98
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

