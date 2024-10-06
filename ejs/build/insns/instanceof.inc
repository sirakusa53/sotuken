#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(instanceof,v1,v2);Linstanceof0: __attribute__((unused));
TLinstanceof_any_string: __attribute__((unused));
TLinstanceof_any_regexp: __attribute__((unused));
TLinstanceof_any_string_object: __attribute__((unused));
TLinstanceof_any_function: __attribute__((unused));
TLinstanceof_any_simple_object: __attribute__((unused));
TLinstanceof_any_number_object: __attribute__((unused));
TLinstanceof_any_iterator: __attribute__((unused));
TLinstanceof_any_flonum: __attribute__((unused));
TLinstanceof_any_special: __attribute__((unused));
TLinstanceof_any_fixnum: __attribute__((unused));
TLinstanceof_any_any: __attribute__((unused));
TLinstanceof_any_builtin: __attribute__((unused));
TLinstanceof_any_boolean_object: __attribute__((unused));
TLinstanceof_any_array: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Linstanceof1: __attribute__((unused));
TLinstanceof_builtin_simple_object: __attribute__((unused));
TLinstanceof_iterator_builtin: __attribute__((unused));
TLinstanceof_array_fixnum: __attribute__((unused));
TLinstanceof_regexp_string_object: __attribute__((unused));
TLinstanceof_boolean_object_special: __attribute__((unused));
TLinstanceof_number_object_special: __attribute__((unused));
TLinstanceof_array_flonum: __attribute__((unused));
TLinstanceof_fixnum_function: __attribute__((unused));
TLinstanceof_flonum_number_object: __attribute__((unused));
TLinstanceof_string_function: __attribute__((unused));
TLinstanceof_function_special: __attribute__((unused));
TLinstanceof_iterator_special: __attribute__((unused));
TLinstanceof_simple_object_string_object: __attribute__((unused));
TLinstanceof_iterator_number_object: __attribute__((unused));
TLinstanceof_string_object_iterator: __attribute__((unused));
TLinstanceof_number_object_iterator: __attribute__((unused));
TLinstanceof_array_string: __attribute__((unused));
TLinstanceof_string_object_simple_object: __attribute__((unused));
TLinstanceof_fixnum_regexp: __attribute__((unused));
TLinstanceof_boolean_object_simple_object: __attribute__((unused));
TLinstanceof_regexp_special: __attribute__((unused));
TLinstanceof_special_array: __attribute__((unused));
TLinstanceof_iterator_string: __attribute__((unused));
TLinstanceof_simple_object_special: __attribute__((unused));
TLinstanceof_regexp_regexp: __attribute__((unused));
TLinstanceof_boolean_object_boolean_object: __attribute__((unused));
TLinstanceof_fixnum_boolean_object: __attribute__((unused));
TLinstanceof_builtin_array: __attribute__((unused));
TLinstanceof_string_object_regexp: __attribute__((unused));
TLinstanceof_simple_object_regexp: __attribute__((unused));
TLinstanceof_function_regexp: __attribute__((unused));
TLinstanceof_flonum_regexp: __attribute__((unused));
TLinstanceof_iterator_function: __attribute__((unused));
TLinstanceof_array_iterator: __attribute__((unused));
TLinstanceof_iterator_simple_object: __attribute__((unused));
TLinstanceof_function_flonum: __attribute__((unused));
TLinstanceof_flonum_flonum: __attribute__((unused));
TLinstanceof_boolean_object_number_object: __attribute__((unused));
TLinstanceof_simple_object_iterator: __attribute__((unused));
TLinstanceof_flonum_fixnum: __attribute__((unused));
TLinstanceof_regexp_flonum: __attribute__((unused));
TLinstanceof_function_fixnum: __attribute__((unused));
TLinstanceof_regexp_boolean_object: __attribute__((unused));
TLinstanceof_function_string_object: __attribute__((unused));
TLinstanceof_string_object_boolean_object: __attribute__((unused));
TLinstanceof_flonum_any: __attribute__((unused));
TLinstanceof_builtin_fixnum: __attribute__((unused));
TLinstanceof_number_object_string: __attribute__((unused));
TLinstanceof_function_number_object: __attribute__((unused));
TLinstanceof_number_object_boolean_object: __attribute__((unused));
TLinstanceof_regexp_iterator: __attribute__((unused));
TLinstanceof_array_boolean_object: __attribute__((unused));
TLinstanceof_string_object_array: __attribute__((unused));
TLinstanceof_fixnum_array: __attribute__((unused));
TLinstanceof_string_array: __attribute__((unused));
TLinstanceof_flonum_boolean_object: __attribute__((unused));
TLinstanceof_boolean_object_string: __attribute__((unused));
TLinstanceof_builtin_regexp: __attribute__((unused));
TLinstanceof_fixnum_string: __attribute__((unused));
TLinstanceof_special_function: __attribute__((unused));
TLinstanceof_number_object_number_object: __attribute__((unused));
TLinstanceof_special_number_object: __attribute__((unused));
TLinstanceof_string_regexp: __attribute__((unused));
TLinstanceof_array_string_object: __attribute__((unused));
TLinstanceof_simple_object_array: __attribute__((unused));
TLinstanceof_string_fixnum: __attribute__((unused));
TLinstanceof_string_string_object: __attribute__((unused));
TLinstanceof_special_regexp: __attribute__((unused));
TLinstanceof_string_object_number_object: __attribute__((unused));
TLinstanceof_iterator_flonum: __attribute__((unused));
TLinstanceof_function_simple_object: __attribute__((unused));
TLinstanceof_special_iterator: __attribute__((unused));
TLinstanceof_fixnum_builtin: __attribute__((unused));
TLinstanceof_string_iterator: __attribute__((unused));
TLinstanceof_special_string: __attribute__((unused));
TLinstanceof_array_regexp: __attribute__((unused));
TLinstanceof_fixnum_simple_object: __attribute__((unused));
TLinstanceof_special_boolean_object: __attribute__((unused));
TLinstanceof_special_special: __attribute__((unused));
TLinstanceof_special_simple_object: __attribute__((unused));
TLinstanceof_special_fixnum: __attribute__((unused));
TLinstanceof_fixnum_special: __attribute__((unused));
TLinstanceof_fixnum_fixnum: __attribute__((unused));
TLinstanceof_simple_object_string: __attribute__((unused));
TLinstanceof_string_simple_object: __attribute__((unused));
TLinstanceof_flonum_special: __attribute__((unused));
TLinstanceof_fixnum_any: __attribute__((unused));
TLinstanceof_special_flonum: __attribute__((unused));
TLinstanceof_regexp_array: __attribute__((unused));
TLinstanceof_flonum_builtin: __attribute__((unused));
TLinstanceof_string_boolean_object: __attribute__((unused));
TLinstanceof_string_flonum: __attribute__((unused));
TLinstanceof_string_special: __attribute__((unused));
TLinstanceof_simple_object_flonum: __attribute__((unused));
TLinstanceof_string_object_flonum: __attribute__((unused));
TLinstanceof_simple_object_fixnum: __attribute__((unused));
TLinstanceof_string_object_fixnum: __attribute__((unused));
TLinstanceof_number_object_simple_object: __attribute__((unused));
TLinstanceof_special_builtin: __attribute__((unused));
TLinstanceof_fixnum_iterator: __attribute__((unused));
TLinstanceof_regexp_simple_object: __attribute__((unused));
TLinstanceof_array_simple_object: __attribute__((unused));
TLinstanceof_fixnum_number_object: __attribute__((unused));
TLinstanceof_flonum_function: __attribute__((unused));
TLinstanceof_function_array: __attribute__((unused));
TLinstanceof_string_any: __attribute__((unused));
TLinstanceof_function_boolean_object: __attribute__((unused));
TLinstanceof_boolean_object_string_object: __attribute__((unused));
TLinstanceof_regexp_string: __attribute__((unused));
TLinstanceof_string_builtin: __attribute__((unused));
TLinstanceof_regexp_fixnum: __attribute__((unused));
TLinstanceof_simple_object_boolean_object: __attribute__((unused));
TLinstanceof_fixnum_flonum: __attribute__((unused));
TLinstanceof_boolean_object_flonum: __attribute__((unused));
TLinstanceof_number_object_fixnum: __attribute__((unused));
TLinstanceof_flonum_simple_object: __attribute__((unused));
TLinstanceof_array_array: __attribute__((unused));
TLinstanceof_string_object_string_object: __attribute__((unused));
TLinstanceof_builtin_number_object: __attribute__((unused));
TLinstanceof_string_number_object: __attribute__((unused));
TLinstanceof_simple_object_number_object: __attribute__((unused));
TLinstanceof_number_object_regexp: __attribute__((unused));
TLinstanceof_number_object_flonum: __attribute__((unused));
TLinstanceof_iterator_fixnum: __attribute__((unused));
TLinstanceof_string_object_string: __attribute__((unused));
TLinstanceof_flonum_string: __attribute__((unused));
TLinstanceof_builtin_iterator: __attribute__((unused));
TLinstanceof_iterator_array: __attribute__((unused));
TLinstanceof_array_number_object: __attribute__((unused));
TLinstanceof_builtin_flonum: __attribute__((unused));
TLinstanceof_function_string: __attribute__((unused));
TLinstanceof_string_object_special: __attribute__((unused));
TLinstanceof_function_iterator: __attribute__((unused));
TLinstanceof_special_string_object: __attribute__((unused));
TLinstanceof_number_object_string_object: __attribute__((unused));
TLinstanceof_flonum_array: __attribute__((unused));
TLinstanceof_special_any: __attribute__((unused));
TLinstanceof_iterator_string_object: __attribute__((unused));
TLinstanceof_boolean_object_array: __attribute__((unused));
TLinstanceof_iterator_regexp: __attribute__((unused));
TLinstanceof_boolean_object_regexp: __attribute__((unused));
TLinstanceof_builtin_string: __attribute__((unused));
TLinstanceof_builtin_string_object: __attribute__((unused));
TLinstanceof_boolean_object_fixnum: __attribute__((unused));
TLinstanceof_flonum_string_object: __attribute__((unused));
TLinstanceof_regexp_number_object: __attribute__((unused));
TLinstanceof_array_special: __attribute__((unused));
TLinstanceof_boolean_object_iterator: __attribute__((unused));
TLinstanceof_number_object_array: __attribute__((unused));
TLinstanceof_builtin_special: __attribute__((unused));
TLinstanceof_fixnum_string_object: __attribute__((unused));
TLinstanceof_string_string: __attribute__((unused));
TLinstanceof_iterator_boolean_object: __attribute__((unused));
TLinstanceof_iterator_iterator: __attribute__((unused));
TLinstanceof_simple_object_simple_object: __attribute__((unused));
TLinstanceof_builtin_boolean_object: __attribute__((unused));
TLinstanceof_flonum_iterator: __attribute__((unused));
{ // normal_flonum normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@16

  dst = JS_FALSE;
/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
}
break;
case TV_GENERIC:
Linstanceof2: __attribute__((unused));
TLinstanceof_number_object_any: __attribute__((unused));
TLinstanceof_iterator_any: __attribute__((unused));
TLinstanceof_boolean_object_any: __attribute__((unused));
TLinstanceof_builtin_any: __attribute__((unused));
TLinstanceof_string_object_any: __attribute__((unused));
TLinstanceof_array_any: __attribute__((unused));
TLinstanceof_function_any: __attribute__((unused));
TLinstanceof_regexp_any: __attribute__((unused));
TLinstanceof_simple_object_any: __attribute__((unused));
switch((unsigned int) get_ptag(v2).v){ // vmgen.newsynth.DecisionDiagram$PTNode@41d(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
goto Linstanceof1;
break;
case TV_GENERIC:
Linstanceof3: __attribute__((unused));switch((unsigned int) get_htag(v1).v){ // vmgen.newsynth.DecisionDiagram$HTNode@118b(2)
case HTAGV_ITERATOR:
goto Linstanceof1;
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
Linstanceof4: __attribute__((unused));switch((unsigned int) get_htag(v2).v){ // vmgen.newsynth.DecisionDiagram$HTNode@537(2)
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_ARRAY:
case HTAGV_ITERATOR:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
goto Linstanceof1;
break;
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
Linstanceof5: __attribute__((unused));
TLinstanceof_string_object_builtin: __attribute__((unused));
TLinstanceof_simple_object_builtin: __attribute__((unused));
TLinstanceof_number_object_function: __attribute__((unused));
TLinstanceof_builtin_function: __attribute__((unused));
TLinstanceof_string_object_function: __attribute__((unused));
TLinstanceof_function_function: __attribute__((unused));
TLinstanceof_builtin_builtin: __attribute__((unused));
TLinstanceof_simple_object_function: __attribute__((unused));
TLinstanceof_boolean_object_builtin: __attribute__((unused));
TLinstanceof_boolean_object_function: __attribute__((unused));
TLinstanceof_array_builtin: __attribute__((unused));
TLinstanceof_regexp_function: __attribute__((unused));
TLinstanceof_regexp_builtin: __attribute__((unused));
TLinstanceof_number_object_builtin: __attribute__((unused));
TLinstanceof_function_builtin: __attribute__((unused));
TLinstanceof_array_function: __attribute__((unused));
{ // normal_boolean_object normal_function vmgen.newsynth.DecisionDiagram$Leaf@185

/*
   instanceof dst r1 r2
     $dst = $r1 instanceof $r2
 */

  JSValue ctor_prototype = get_prop(v2, gconsts.g_string_prototype);
  if (!is_jsobject(ctor_prototype))
    dst = JS_FALSE;
  else {
    JSValue __proto__ = v1;
    JSValue ret = JS_FALSE;
    while ((__proto__ = get_prop(__proto__,
                                 gconsts.g_string___proto__)) != JS_EMPTY)
      if (__proto__ == ctor_prototype) {
        ret = JS_TRUE;
        break;
      }
    dst = ret;
  }
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@537
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@118b
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@41d
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

