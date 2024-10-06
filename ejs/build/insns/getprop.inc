#define dst regbase[r0]
#define obj v1
#define prop v2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT2(getprop,obj,prop);Lgetprop0: __attribute__((unused));
TLgetprop_function_any: __attribute__((unused));
TLgetprop_any_any: __attribute__((unused));
TLgetprop_builtin_any: __attribute__((unused));
TLgetprop_string_object_any: __attribute__((unused));
TLgetprop_special_any: __attribute__((unused));
TLgetprop_regexp_any: __attribute__((unused));
TLgetprop_flonum_any: __attribute__((unused));
TLgetprop_iterator_any: __attribute__((unused));
TLgetprop_boolean_object_any: __attribute__((unused));
TLgetprop_number_object_any: __attribute__((unused));
TLgetprop_string_any: __attribute__((unused));
TLgetprop_fixnum_any: __attribute__((unused));
TLgetprop_array_any: __attribute__((unused));
TLgetprop_simple_object_any: __attribute__((unused));
switch((unsigned int) get_ptag(prop).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(3)
case TV_FIXNUM:
default:
Lgetprop1: __attribute__((unused));
TLgetprop_any_fixnum: __attribute__((unused));
switch((unsigned int) get_ptag(obj).v){ // vmgen.newsynth.DecisionDiagram$PTNode@e18(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Lgetprop2: __attribute__((unused));
TLgetprop_string_boolean_object: __attribute__((unused));
TLgetprop_fixnum_special: __attribute__((unused));
TLgetprop_flonum_boolean_object: __attribute__((unused));
TLgetprop_special_flonum: __attribute__((unused));
TLgetprop_fixnum_string_object: __attribute__((unused));
TLgetprop_special_string_object: __attribute__((unused));
TLgetprop_string_iterator: __attribute__((unused));
TLgetprop_fixnum_function: __attribute__((unused));
TLgetprop_string_builtin: __attribute__((unused));
TLgetprop_special_function: __attribute__((unused));
TLgetprop_special_special: __attribute__((unused));
TLgetprop_fixnum_boolean_object: __attribute__((unused));
TLgetprop_iterator_special: __attribute__((unused));
TLgetprop_iterator_simple_object: __attribute__((unused));
TLgetprop_fixnum_flonum: __attribute__((unused));
TLgetprop_flonum_number_object: __attribute__((unused));
TLgetprop_fixnum_iterator: __attribute__((unused));
TLgetprop_iterator_string: __attribute__((unused));
TLgetprop_special_simple_object: __attribute__((unused));
TLgetprop_string_number_object: __attribute__((unused));
TLgetprop_iterator_builtin: __attribute__((unused));
TLgetprop_iterator_fixnum: __attribute__((unused));
TLgetprop_special_builtin: __attribute__((unused));
TLgetprop_string_array: __attribute__((unused));
TLgetprop_special_string: __attribute__((unused));
TLgetprop_special_array: __attribute__((unused));
TLgetprop_special_fixnum: __attribute__((unused));
TLgetprop_fixnum_array: __attribute__((unused));
TLgetprop_fixnum_number_object: __attribute__((unused));
TLgetprop_special_regexp: __attribute__((unused));
TLgetprop_iterator_number_object: __attribute__((unused));
TLgetprop_flonum_flonum: __attribute__((unused));
TLgetprop_iterator_regexp: __attribute__((unused));
TLgetprop_flonum_array: __attribute__((unused));
TLgetprop_iterator_string_object: __attribute__((unused));
TLgetprop_iterator_array: __attribute__((unused));
TLgetprop_string_string: __attribute__((unused));
TLgetprop_iterator_function: __attribute__((unused));
TLgetprop_string_simple_object: __attribute__((unused));
TLgetprop_flonum_fixnum: __attribute__((unused));
TLgetprop_string_fixnum: __attribute__((unused));
TLgetprop_string_regexp: __attribute__((unused));
TLgetprop_flonum_string_object: __attribute__((unused));
TLgetprop_flonum_regexp: __attribute__((unused));
TLgetprop_flonum_function: __attribute__((unused));
TLgetprop_flonum_iterator: __attribute__((unused));
TLgetprop_iterator_flonum: __attribute__((unused));
TLgetprop_flonum_special: __attribute__((unused));
TLgetprop_iterator_iterator: __attribute__((unused));
TLgetprop_fixnum_string: __attribute__((unused));
TLgetprop_string_special: __attribute__((unused));
TLgetprop_fixnum_builtin: __attribute__((unused));
TLgetprop_flonum_string: __attribute__((unused));
TLgetprop_special_iterator: __attribute__((unused));
TLgetprop_fixnum_fixnum: __attribute__((unused));
TLgetprop_fixnum_simple_object: __attribute__((unused));
TLgetprop_special_boolean_object: __attribute__((unused));
TLgetprop_string_function: __attribute__((unused));
TLgetprop_string_flonum: __attribute__((unused));
TLgetprop_flonum_simple_object: __attribute__((unused));
TLgetprop_iterator_boolean_object: __attribute__((unused));
TLgetprop_string_string_object: __attribute__((unused));
TLgetprop_flonum_builtin: __attribute__((unused));
TLgetprop_special_number_object: __attribute__((unused));
TLgetprop_fixnum_regexp: __attribute__((unused));
{ // normal_flonum normal_iterator vmgen.newsynth.DecisionDiagram$Leaf@4e

  if (obj == JS_UNDEFINED)
     LOG_EXIT("GETPROP: attempt to get property of `undefined'\n");
  GC_PUSH(prop);
  obj = to_object(context, obj);
  GC_POP(prop);
  goto USELABEL(HEAD);
/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
}
break;
case TV_GENERIC:
Lgetprop3: __attribute__((unused));switch((unsigned int) get_htag(obj).v){ // vmgen.newsynth.DecisionDiagram$HTNode@2609(3)
case HTAGV_ITERATOR:
goto Lgetprop2;
break;
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
Lgetprop4: __attribute__((unused));
TLgetprop_function_array: __attribute__((unused));
TLgetprop_regexp_number_object: __attribute__((unused));
TLgetprop_string_object_flonum: __attribute__((unused));
TLgetprop_string_object_array: __attribute__((unused));
TLgetprop_boolean_object_regexp: __attribute__((unused));
TLgetprop_simple_object_special: __attribute__((unused));
TLgetprop_builtin_array: __attribute__((unused));
TLgetprop_string_object_special: __attribute__((unused));
TLgetprop_boolean_object_builtin: __attribute__((unused));
TLgetprop_simple_object_string_object: __attribute__((unused));
TLgetprop_string_object_regexp: __attribute__((unused));
TLgetprop_regexp_special: __attribute__((unused));
TLgetprop_builtin_string_object: __attribute__((unused));
TLgetprop_number_object_array: __attribute__((unused));
TLgetprop_regexp_builtin: __attribute__((unused));
TLgetprop_number_object_builtin: __attribute__((unused));
TLgetprop_builtin_boolean_object: __attribute__((unused));
TLgetprop_regexp_boolean_object: __attribute__((unused));
TLgetprop_boolean_object_number_object: __attribute__((unused));
TLgetprop_boolean_object_special: __attribute__((unused));
TLgetprop_string_object_fixnum: __attribute__((unused));
TLgetprop_boolean_object_fixnum: __attribute__((unused));
TLgetprop_builtin_flonum: __attribute__((unused));
TLgetprop_function_simple_object: __attribute__((unused));
TLgetprop_number_object_fixnum: __attribute__((unused));
TLgetprop_number_object_regexp: __attribute__((unused));
TLgetprop_regexp_regexp: __attribute__((unused));
TLgetprop_regexp_string_object: __attribute__((unused));
TLgetprop_number_object_number_object: __attribute__((unused));
TLgetprop_builtin_number_object: __attribute__((unused));
TLgetprop_number_object_flonum: __attribute__((unused));
TLgetprop_builtin_fixnum: __attribute__((unused));
TLgetprop_regexp_flonum: __attribute__((unused));
TLgetprop_string_object_builtin: __attribute__((unused));
TLgetprop_simple_object_builtin: __attribute__((unused));
TLgetprop_number_object_simple_object: __attribute__((unused));
TLgetprop_simple_object_function: __attribute__((unused));
TLgetprop_number_object_special: __attribute__((unused));
TLgetprop_function_boolean_object: __attribute__((unused));
TLgetprop_string_object_simple_object: __attribute__((unused));
TLgetprop_boolean_object_flonum: __attribute__((unused));
TLgetprop_function_string_object: __attribute__((unused));
TLgetprop_number_object_function: __attribute__((unused));
TLgetprop_string_object_function: __attribute__((unused));
TLgetprop_regexp_array: __attribute__((unused));
TLgetprop_function_flonum: __attribute__((unused));
TLgetprop_regexp_function: __attribute__((unused));
TLgetprop_builtin_regexp: __attribute__((unused));
TLgetprop_function_builtin: __attribute__((unused));
TLgetprop_simple_object_flonum: __attribute__((unused));
TLgetprop_simple_object_fixnum: __attribute__((unused));
TLgetprop_simple_object_boolean_object: __attribute__((unused));
TLgetprop_regexp_simple_object: __attribute__((unused));
TLgetprop_builtin_function: __attribute__((unused));
TLgetprop_simple_object_regexp: __attribute__((unused));
TLgetprop_builtin_iterator: __attribute__((unused));
TLgetprop_boolean_object_function: __attribute__((unused));
TLgetprop_simple_object_iterator: __attribute__((unused));
TLgetprop_function_fixnum: __attribute__((unused));
TLgetprop_number_object_string_object: __attribute__((unused));
TLgetprop_simple_object_number_object: __attribute__((unused));
TLgetprop_boolean_object_boolean_object: __attribute__((unused));
TLgetprop_function_function: __attribute__((unused));
TLgetprop_function_iterator: __attribute__((unused));
TLgetprop_boolean_object_array: __attribute__((unused));
TLgetprop_function_regexp: __attribute__((unused));
TLgetprop_boolean_object_string_object: __attribute__((unused));
TLgetprop_string_object_string_object: __attribute__((unused));
TLgetprop_function_special: __attribute__((unused));
TLgetprop_regexp_fixnum: __attribute__((unused));
TLgetprop_builtin_special: __attribute__((unused));
TLgetprop_string_object_number_object: __attribute__((unused));
TLgetprop_builtin_simple_object: __attribute__((unused));
TLgetprop_builtin_builtin: __attribute__((unused));
TLgetprop_simple_object_simple_object: __attribute__((unused));
TLgetprop_number_object_boolean_object: __attribute__((unused));
TLgetprop_boolean_object_iterator: __attribute__((unused));
TLgetprop_function_number_object: __attribute__((unused));
TLgetprop_string_object_iterator: __attribute__((unused));
TLgetprop_number_object_iterator: __attribute__((unused));
TLgetprop_string_object_boolean_object: __attribute__((unused));
TLgetprop_simple_object_array: __attribute__((unused));
TLgetprop_boolean_object_simple_object: __attribute__((unused));
TLgetprop_regexp_iterator: __attribute__((unused));
{ // normal_function normal_special vmgen.newsynth.DecisionDiagram$Leaf@69

#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag)
    printf("getprop: object (prop = %" PRIJSValue ")\n", prop);
#endif /* DEBUG_GETPROP_VALUE */
#ifdef INLINE_CACHE
  dst = get_object_prop(context, obj, prop, NULL);
#else /* INLINE_CACHE */
  dst = get_object_prop(context, obj, prop);
#endif /* INLINE_CACHE */
#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag) {
    printf("getprop: ");
    print_value(context, dst, 1);
    printf("\n");
  }
#endif /* DEBUG_GETPROP_VALUE */
}
break;
case HTAGV_ARRAY:
Lgetprop5: __attribute__((unused));
TLgetprop_array_fixnum: __attribute__((unused));
{ // normal_array normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@235a

#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag)
    printf("getprop: array (prop = fixnum(%" PRIcint "))\n", fixnum_to_cint(prop));
#endif /* DEBUG_GETPROP_VALUE */
  dst = get_array_element(context, obj, fixnum_to_cint(prop));
#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag) {
    printf("getprop: ");
    print_value(context, dst, 1);
    printf("\n");
  }
#endif /* DEBUG_GETPROP_VALUE */
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@2609
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@e18
break;
case TV_FLONUM:
case TV_SPECIAL:
case TV_GENERIC:
Lgetprop6: __attribute__((unused));
TLgetprop_any_function: __attribute__((unused));
TLgetprop_any_number_object: __attribute__((unused));
TLgetprop_any_array: __attribute__((unused));
TLgetprop_any_flonum: __attribute__((unused));
TLgetprop_any_iterator: __attribute__((unused));
TLgetprop_any_string_object: __attribute__((unused));
TLgetprop_any_regexp: __attribute__((unused));
TLgetprop_any_special: __attribute__((unused));
TLgetprop_any_boolean_object: __attribute__((unused));
TLgetprop_any_builtin: __attribute__((unused));
TLgetprop_any_simple_object: __attribute__((unused));
switch((unsigned int) get_ptag(obj).v){ // vmgen.newsynth.DecisionDiagram$PTNode@169a(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
goto Lgetprop2;
break;
case TV_GENERIC:
Lgetprop7: __attribute__((unused));switch((unsigned int) get_htag(obj).v){ // vmgen.newsynth.DecisionDiagram$HTNode@5a1(3)
case HTAGV_ITERATOR:
goto Lgetprop2;
break;
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
goto Lgetprop4;
break;
case HTAGV_ARRAY:
Lgetprop8: __attribute__((unused));
TLgetprop_array_string: __attribute__((unused));
TLgetprop_array_builtin: __attribute__((unused));
TLgetprop_array_special: __attribute__((unused));
TLgetprop_array_flonum: __attribute__((unused));
TLgetprop_array_regexp: __attribute__((unused));
TLgetprop_array_number_object: __attribute__((unused));
TLgetprop_array_iterator: __attribute__((unused));
TLgetprop_array_function: __attribute__((unused));
TLgetprop_array_array: __attribute__((unused));
TLgetprop_array_simple_object: __attribute__((unused));
TLgetprop_array_boolean_object: __attribute__((unused));
TLgetprop_array_string_object: __attribute__((unused));
{ // normal_array normal_array vmgen.newsynth.DecisionDiagram$Leaf@185

#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag)
    printf("getprop: array (prop = %" PRIJSValue ")\n", prop);
#endif /* DEBUG_GETPROP_VALUE */
  dst = get_array_prop(context, obj, prop);
#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag) {
    printf("getprop: ");
    print_value(context, dst, 1);
    printf("\n");
  }
#endif /* DEBUG_GETPROP_VALUE */
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@5a1
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@169a
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lgetprop9: __attribute__((unused));
TLgetprop_any_string: __attribute__((unused));
switch((unsigned int) get_ptag(obj).v){ // vmgen.newsynth.DecisionDiagram$PTNode@1986(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
goto Lgetprop2;
break;
case TV_GENERIC:
Lgetprop10: __attribute__((unused));switch((unsigned int) get_htag(obj).v){ // vmgen.newsynth.DecisionDiagram$HTNode@6c2(3)
case HTAGV_ITERATOR:
goto Lgetprop2;
break;
case HTAGV_ARRAY:
goto Lgetprop8;
break;
case HTAGV_SIMPLE_OBJECT:
case 5:
case 4:
case 3:
case 2:
case 1:
case 0:
case HTAGV_FUNCTION:
case HTAGV_BUILTIN:
case HTAGV_REGEXP:
case HTAGV_BOXED_STRING:
case HTAGV_BOXED_NUMBER:
case HTAGV_BOXED_BOOLEAN:
default:
Lgetprop11: __attribute__((unused));
TLgetprop_builtin_string: __attribute__((unused));
TLgetprop_function_string: __attribute__((unused));
TLgetprop_boolean_object_string: __attribute__((unused));
TLgetprop_regexp_string: __attribute__((unused));
TLgetprop_number_object_string: __attribute__((unused));
TLgetprop_simple_object_string: __attribute__((unused));
TLgetprop_string_object_string: __attribute__((unused));
{ // normal_builtin normal_string vmgen.newsynth.DecisionDiagram$Leaf@52d

#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag)
    printf("getprop: object (prop = %s)\n", string_to_cstr(prop));
#endif /* DEBUG_GETPROP_VALUE */
#ifdef INLINE_CACHE
  {
    InlineCache *ic = &(INSN_CACHE(curfn->index, pc).inl_cache);
#ifdef IC_PROF
    ic->count++;
    ic_prof_count++;
    if (ic->pm == NULL)
      ic->unavailable++;
#endif /* IC_PROF */

#ifdef PROTO_IC
    if (ic->pm == object_get_shape(obj)->pm && ic->prop_name == prop) {
      if (ic->owner == JS_EMPTY) {
        assert(ic->index <
               object_get_shape(obj)->n_embedded_slots +
               object_get_shape(obj)->n_extension_slots -
               (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
        dst = object_get_prop(obj, ic->index);
        if (dst == JS_EMPTY)
          goto GETPROP_OBJECT_INLINE_CACHE_MISS;
      } else {
        if (ic->epoch < prototype_ic_epoch)
          goto GETPROP_OBJECT_INVALIDATE_INLINE_CACHE;
        else {
          JSValue owner = ic->owner;
          assert(ic->index <
                 object_get_shape(owner)->n_embedded_slots +
                 object_get_shape(owner)->n_extension_slots -
                 (object_get_shape(owner)->n_extension_slots > 0 ? 1 : 0));
          dst = object_get_prop(owner, ic->index);
          /* Deletion of prototype property should invalidate inline
           * cache. So control should not reach hare in such a case. */
          assert(dst != JS_EMPTY);
        }
      }
#ifdef IC_PROF
      ic->hit++;
      ic_prof_hit++;
#endif /* IC_PROF */
    } else {
    GETPROP_OBJECT_INLINE_CACHE_MISS:
      if (++ic->miss > INLINE_CACHE_RESET_THRESHOLD) {
      GETPROP_OBJECT_INVALIDATE_INLINE_CACHE:
        ic->pm = NULL; /* invalidate */
      }
      dst = get_object_prop(context, obj, prop, ic);
    }
#else /* PROTO_IC */
    if (ic->pm == object_get_shape(obj)->pm && ic->prop_name == prop) {
      assert(ic->index <
             object_get_shape(obj)->n_embedded_slots +
             object_get_shape(obj)->n_extension_slots -
             (object_get_shape(obj)->n_extension_slots > 0 ? 1 : 0));
      dst = object_get_prop(obj, ic->index);
      if (dst == JS_EMPTY)
        goto GETPROP_OBJECT_INLINE_CACHE_MISS;
#ifdef IC_PROF
      ic->hit++;
      ic_prof_hit++;
#endif /* IC_PROF */
    } else {
    GETPROP_OBJECT_INLINE_CACHE_MISS:      
      if (++ic->miss > INLINE_CACHE_RESET_THRESHOLD) {
        ic->pm = NULL; /* invalidate */
      }
      dst = get_object_prop(context, obj, prop, ic);
    }
#endif /* PROTO_IC */
  }
#else /* INLINE_CACHE */
  dst = get_object_prop(context, obj, prop);
#endif /* INLINE_CACHE */
#ifdef DEBUG_GETPROP_VALUE
  if (trace_flag) {
    printf("getprop: ");
    print_value(context, dst, 1);
    printf("\n");
  }
#endif /* DEBUG_GETPROP_VALUE */
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@6c2
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@1986
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst
#undef obj
#undef prop

