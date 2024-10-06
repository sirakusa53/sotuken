#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(add,v1,v2);Ladd0: __attribute__((unused));
TLadd_string_any: __attribute__((unused));
TLadd_fixnum_any: __attribute__((unused));
TLadd_boolean_object_any: __attribute__((unused));
TLadd_number_object_any: __attribute__((unused));
TLadd_flonum_any: __attribute__((unused));
TLadd_function_any: __attribute__((unused));
TLadd_special_any: __attribute__((unused));
TLadd_regexp_any: __attribute__((unused));
TLadd_string_object_any: __attribute__((unused));
TLadd_simple_object_any: __attribute__((unused));
TLadd_any_any: __attribute__((unused));
TLadd_iterator_any: __attribute__((unused));
TLadd_builtin_any: __attribute__((unused));
TLadd_array_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(4)
case TV_FLONUM:
case TV_SPECIAL:
Ladd1: __attribute__((unused));
TLadd_any_special: __attribute__((unused));
TLadd_any_flonum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@568(3)
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Ladd2: __attribute__((unused));
TLadd_boolean_object_iterator: __attribute__((unused));
TLadd_string_iterator: __attribute__((unused));
TLadd_iterator_function: __attribute__((unused));
TLadd_iterator_simple_object: __attribute__((unused));
TLadd_flonum_iterator: __attribute__((unused));
TLadd_regexp_iterator: __attribute__((unused));
TLadd_iterator_flonum: __attribute__((unused));
TLadd_special_special: __attribute__((unused));
TLadd_iterator_number_object: __attribute__((unused));
TLadd_function_iterator: __attribute__((unused));
TLadd_flonum_special: __attribute__((unused));
TLadd_iterator_array: __attribute__((unused));
TLadd_fixnum_special: __attribute__((unused));
TLadd_special_flonum: __attribute__((unused));
TLadd_iterator_fixnum: __attribute__((unused));
TLadd_builtin_iterator: __attribute__((unused));
TLadd_simple_object_iterator: __attribute__((unused));
TLadd_iterator_string_object: __attribute__((unused));
TLadd_iterator_iterator: __attribute__((unused));
TLadd_iterator_special: __attribute__((unused));
TLadd_iterator_string: __attribute__((unused));
TLadd_number_object_iterator: __attribute__((unused));
TLadd_iterator_boolean_object: __attribute__((unused));
TLadd_iterator_builtin: __attribute__((unused));
TLadd_flonum_flonum: __attribute__((unused));
TLadd_fixnum_iterator: __attribute__((unused));
TLadd_special_iterator: __attribute__((unused));
TLadd_flonum_fixnum: __attribute__((unused));
TLadd_string_object_iterator: __attribute__((unused));
TLadd_fixnum_flonum: __attribute__((unused));
TLadd_array_iterator: __attribute__((unused));
TLadd_iterator_regexp: __attribute__((unused));
TLadd_special_fixnum: __attribute__((unused));
{ // normal_iterator normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@54

  GC_PUSH(v2);
  double x1 = to_double(context, v1);
  GC_POP(v2);
  double x2 = to_double(context, v2);
  dst = double_to_number(context, x1 + x2);
}
break;
case TV_STRING:
case 3:
case 2:
case 1:
Ladd3: __attribute__((unused));
TLadd_string_fixnum: __attribute__((unused));
TLadd_string_special: __attribute__((unused));
TLadd_string_flonum: __attribute__((unused));
{ // normal_string normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@dbb

  GC_PUSH(v1);
  v2 = to_string(context, v2);
  GC_POP(v1);
  goto USELABEL(STRSTR);
}
break;
case TV_GENERIC:
Ladd4: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@26f6(2)
case HTAGV_ITERATOR:
goto Ladd2;
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
Ladd5: __attribute__((unused));
TLadd_builtin_string: __attribute__((unused));
TLadd_function_flonum: __attribute__((unused));
TLadd_string_object_string: __attribute__((unused));
TLadd_function_fixnum: __attribute__((unused));
TLadd_boolean_object_flonum: __attribute__((unused));
TLadd_simple_object_string: __attribute__((unused));
TLadd_builtin_fixnum: __attribute__((unused));
TLadd_string_object_flonum: __attribute__((unused));
TLadd_regexp_special: __attribute__((unused));
TLadd_array_special: __attribute__((unused));
TLadd_simple_object_flonum: __attribute__((unused));
TLadd_regexp_string: __attribute__((unused));
TLadd_number_object_special: __attribute__((unused));
TLadd_number_object_flonum: __attribute__((unused));
TLadd_regexp_flonum: __attribute__((unused));
TLadd_simple_object_special: __attribute__((unused));
TLadd_array_flonum: __attribute__((unused));
TLadd_function_special: __attribute__((unused));
TLadd_builtin_flonum: __attribute__((unused));
TLadd_boolean_object_special: __attribute__((unused));
TLadd_array_fixnum: __attribute__((unused));
TLadd_string_object_special: __attribute__((unused));
TLadd_number_object_string: __attribute__((unused));
TLadd_builtin_special: __attribute__((unused));
TLadd_array_string: __attribute__((unused));
TLadd_boolean_object_string: __attribute__((unused));
TLadd_boolean_object_fixnum: __attribute__((unused));
TLadd_number_object_fixnum: __attribute__((unused));
TLadd_regexp_fixnum: __attribute__((unused));
TLadd_function_string: __attribute__((unused));
TLadd_simple_object_fixnum: __attribute__((unused));
TLadd_string_object_fixnum: __attribute__((unused));
{ // normal_boolean_object normal_special vmgen.newsynth.DecisionDiagram$Leaf@97

  GC_PUSH(v2);
  v1 = object_to_string(context, v1);
  GC_POP(v2);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@26f6
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@568
break;
case TV_STRING:
case 3:
case 2:
case 1:
Ladd6: __attribute__((unused));
TLadd_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@685(3)
case TV_STRING:
case 3:
case 2:
case 1:
Ladd7: __attribute__((unused));
TLadd_string_string: __attribute__((unused));
{ // normal_string normal_string vmgen.newsynth.DecisionDiagram$Leaf@92e

DEFLABEL(STRSTR): __attribute__((unused));
  dst = ejs_string_concat(context, v1, v2);
}
break;
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Ladd8: __attribute__((unused));
TLadd_flonum_string: __attribute__((unused));
TLadd_special_string: __attribute__((unused));
TLadd_fixnum_string: __attribute__((unused));
{ // normal_flonum normal_string vmgen.newsynth.DecisionDiagram$Leaf@a53

  GC_PUSH(v2);
  v1 = to_string(context, v1);
  GC_POP(v2);
  goto USELABEL(STRSTR);
}
break;
case TV_GENERIC:
goto Ladd4;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@685
break;
case TV_FIXNUM:
default:
Ladd9: __attribute__((unused));
TLadd_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@b26(4)
case TV_FLONUM:
case TV_SPECIAL:
goto Ladd2;
break;
case TV_FIXNUM:
default:
Ladd10: __attribute__((unused));
TLadd_fixnum_fixnum: __attribute__((unused));
{ // normal_fixnum normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@d41

  cint s = fixnum_to_cint(v1) + fixnum_to_cint(v2);
  dst = cint_to_number(context, s);
}
break;
case TV_STRING:
case 3:
case 2:
case 1:
goto Ladd3;
break;
case TV_GENERIC:
goto Ladd4;
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@b26
break;
case TV_GENERIC:
Ladd11: __attribute__((unused));
TLadd_any_simple_object: __attribute__((unused));
TLadd_any_builtin: __attribute__((unused));
TLadd_any_string_object: __attribute__((unused));
TLadd_any_array: __attribute__((unused));
TLadd_any_function: __attribute__((unused));
TLadd_any_boolean_object: __attribute__((unused));
TLadd_any_regexp: __attribute__((unused));
TLadd_any_iterator: __attribute__((unused));
TLadd_any_number_object: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@10a6(2)
case TV_GENERIC:
Ladd12: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@447(2)
case HTAGV_ITERATOR:
goto Ladd2;
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
Ladd13: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@160c(2)
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
Ladd14: __attribute__((unused));
TLadd_builtin_function: __attribute__((unused));
TLadd_function_boolean_object: __attribute__((unused));
TLadd_function_regexp: __attribute__((unused));
TLadd_number_object_builtin: __attribute__((unused));
TLadd_function_number_object: __attribute__((unused));
TLadd_array_number_object: __attribute__((unused));
TLadd_string_object_array: __attribute__((unused));
TLadd_boolean_object_simple_object: __attribute__((unused));
TLadd_simple_object_regexp: __attribute__((unused));
TLadd_string_object_function: __attribute__((unused));
TLadd_regexp_array: __attribute__((unused));
TLadd_regexp_simple_object: __attribute__((unused));
TLadd_string_object_simple_object: __attribute__((unused));
TLadd_number_object_array: __attribute__((unused));
TLadd_simple_object_number_object: __attribute__((unused));
TLadd_array_boolean_object: __attribute__((unused));
TLadd_simple_object_string_object: __attribute__((unused));
TLadd_number_object_function: __attribute__((unused));
TLadd_number_object_string_object: __attribute__((unused));
TLadd_array_regexp: __attribute__((unused));
TLadd_simple_object_boolean_object: __attribute__((unused));
TLadd_regexp_function: __attribute__((unused));
TLadd_array_string_object: __attribute__((unused));
TLadd_regexp_boolean_object: __attribute__((unused));
TLadd_regexp_builtin: __attribute__((unused));
TLadd_boolean_object_function: __attribute__((unused));
TLadd_function_function: __attribute__((unused));
TLadd_builtin_simple_object: __attribute__((unused));
TLadd_boolean_object_string_object: __attribute__((unused));
TLadd_function_array: __attribute__((unused));
TLadd_regexp_string_object: __attribute__((unused));
TLadd_boolean_object_array: __attribute__((unused));
TLadd_number_object_regexp: __attribute__((unused));
TLadd_boolean_object_regexp: __attribute__((unused));
TLadd_simple_object_simple_object: __attribute__((unused));
TLadd_string_object_number_object: __attribute__((unused));
TLadd_function_builtin: __attribute__((unused));
TLadd_simple_object_array: __attribute__((unused));
TLadd_string_object_regexp: __attribute__((unused));
TLadd_array_simple_object: __attribute__((unused));
TLadd_array_function: __attribute__((unused));
TLadd_regexp_number_object: __attribute__((unused));
TLadd_number_object_number_object: __attribute__((unused));
TLadd_boolean_object_builtin: __attribute__((unused));
TLadd_function_string_object: __attribute__((unused));
TLadd_simple_object_function: __attribute__((unused));
TLadd_builtin_number_object: __attribute__((unused));
TLadd_array_array: __attribute__((unused));
TLadd_boolean_object_number_object: __attribute__((unused));
TLadd_string_object_boolean_object: __attribute__((unused));
TLadd_boolean_object_boolean_object: __attribute__((unused));
TLadd_builtin_builtin: __attribute__((unused));
TLadd_simple_object_builtin: __attribute__((unused));
TLadd_array_builtin: __attribute__((unused));
TLadd_string_object_string_object: __attribute__((unused));
TLadd_number_object_boolean_object: __attribute__((unused));
TLadd_builtin_array: __attribute__((unused));
TLadd_string_object_builtin: __attribute__((unused));
TLadd_number_object_simple_object: __attribute__((unused));
TLadd_builtin_string_object: __attribute__((unused));
TLadd_regexp_regexp: __attribute__((unused));
TLadd_function_simple_object: __attribute__((unused));
TLadd_builtin_boolean_object: __attribute__((unused));
TLadd_builtin_regexp: __attribute__((unused));
{ // normal_number_object normal_string_object vmgen.newsynth.DecisionDiagram$Leaf@16

  GC_PUSH(v2);
  v1 = object_to_string(context, v1);
  GC_POP(v2);
  GC_PUSH(v1);
  v2 = object_to_string(context, v2);
  GC_POP(v1);
  goto USELABEL(HEAD);
}
break;
case HTAGV_ITERATOR:
goto Ladd2;
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@160c
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@447
break;
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Ladd15: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@1af7(2)
case HTAGV_ITERATOR:
goto Ladd2;
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
Ladd16: __attribute__((unused));
TLadd_special_number_object: __attribute__((unused));
TLadd_fixnum_function: __attribute__((unused));
TLadd_fixnum_boolean_object: __attribute__((unused));
TLadd_fixnum_string_object: __attribute__((unused));
TLadd_special_simple_object: __attribute__((unused));
TLadd_fixnum_array: __attribute__((unused));
TLadd_special_array: __attribute__((unused));
TLadd_string_builtin: __attribute__((unused));
TLadd_string_boolean_object: __attribute__((unused));
TLadd_string_number_object: __attribute__((unused));
TLadd_fixnum_regexp: __attribute__((unused));
TLadd_flonum_function: __attribute__((unused));
TLadd_string_string_object: __attribute__((unused));
TLadd_flonum_simple_object: __attribute__((unused));
TLadd_fixnum_simple_object: __attribute__((unused));
TLadd_fixnum_builtin: __attribute__((unused));
TLadd_special_regexp: __attribute__((unused));
TLadd_special_builtin: __attribute__((unused));
TLadd_special_string_object: __attribute__((unused));
TLadd_special_boolean_object: __attribute__((unused));
TLadd_fixnum_number_object: __attribute__((unused));
TLadd_flonum_array: __attribute__((unused));
TLadd_special_function: __attribute__((unused));
TLadd_flonum_string_object: __attribute__((unused));
TLadd_string_array: __attribute__((unused));
TLadd_flonum_regexp: __attribute__((unused));
TLadd_flonum_number_object: __attribute__((unused));
TLadd_flonum_boolean_object: __attribute__((unused));
TLadd_string_simple_object: __attribute__((unused));
TLadd_string_function: __attribute__((unused));
TLadd_string_regexp: __attribute__((unused));
TLadd_flonum_builtin: __attribute__((unused));
{ // normal_flonum normal_array vmgen.newsynth.DecisionDiagram$Leaf@222

  GC_PUSH(v1);
  v2 = object_to_string(context, v2);
  GC_POP(v1);
  goto USELABEL(HEAD);
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@1af7
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@10a6
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

