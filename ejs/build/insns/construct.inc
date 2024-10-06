#define dst regbase[r0]
#define con v1
#define nargs i2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(construct,con);Lconstruct0: __attribute__((unused));
TLconstruct_any: __attribute__((unused));
switch((unsigned int) get_ptag(con).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Lconstruct1: __attribute__((unused));
TLconstruct_fixnum: __attribute__((unused));
TLconstruct_regexp: __attribute__((unused));
TLconstruct_simple_object: __attribute__((unused));
TLconstruct_iterator: __attribute__((unused));
TLconstruct_number_object: __attribute__((unused));
TLconstruct_string: __attribute__((unused));
TLconstruct_flonum: __attribute__((unused));
TLconstruct_special: __attribute__((unused));
TLconstruct_array: __attribute__((unused));
TLconstruct_string_object: __attribute__((unused));
TLconstruct_boolean_object: __attribute__((unused));
{ // normal_number_object vmgen.newsynth.DecisionDiagram$Leaf@54

  set_fp(context, fp);
  set_pc(context, pc);
#ifdef DEBUG
  print_value_simple(context, con);
  printf(" is called in CALL instruction\n");
#endif /* DEBUG */
  LOG_EXIT("CALL\n");
}
break;
case TV_GENERIC:
Lconstruct2: __attribute__((unused));switch((unsigned int) get_htag(con).v){ // vmgen.newsynth.DecisionDiagram$HTNode@173c(3)
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
goto Lconstruct1;
break;
case HTAGV_BUILTIN:
Lconstruct3: __attribute__((unused));
TLconstruct_builtin: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@192f

  // new $dst $con
  {
    dst = JS_UNDEFINED;
  }

  // move this $dst
  {
    int sp = get_sp(context);
    JSValue *stack = &get_stack(context, 0);

    stack[sp - nargs] = dst;
  }

  // newsend $dst
  set_fp(context, fp);
  set_pc(context, pc);
  call_builtin(context, con, nargs, TRUE, TRUE);
  update_context();
  NEXT_INSN_INCPC();
}
break;
case HTAGV_FUNCTION:
Lconstruct4: __attribute__((unused));
TLconstruct_function: __attribute__((unused));
{ // normal_function vmgen.newsynth.DecisionDiagram$Leaf@1f5d

  JSValue obj;

  // new $dst $con
  {
    GC_PUSH(con);
    save_context();
    obj = create_simple_object_with_constructor(context, con);
    update_context();

    dst = obj;
  }

  // newsend
  set_fp(context, fp);
  set_pc(context, pc);
  int sendp = TRUE;
  GC_PUSH(obj);
  call_function(context, con, nargs, sendp);
  update_context();

  regbase[1] = obj; // this = $dst

  GC_POP2(obj, con);

  NEXT_INSN_NOINCPC();
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@173c
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst
#undef con
#undef nargs

