#define fn v0
#define nargs i1

  Opcode op = get_opcode(insn);
  int sendp = (op != CALL)? TRUE: FALSE;
  int newp = FALSE;

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(call,fn);Lcall0: __attribute__((unused));
TLcall_any: __attribute__((unused));
switch((unsigned int) get_ptag(fn).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Lcall1: __attribute__((unused));
TLcall_regexp: __attribute__((unused));
TLcall_fixnum: __attribute__((unused));
TLcall_number_object: __attribute__((unused));
TLcall_array: __attribute__((unused));
TLcall_special: __attribute__((unused));
TLcall_flonum: __attribute__((unused));
TLcall_string: __attribute__((unused));
TLcall_simple_object: __attribute__((unused));
TLcall_boolean_object: __attribute__((unused));
TLcall_iterator: __attribute__((unused));
TLcall_string_object: __attribute__((unused));
{ // normal_iterator vmgen.newsynth.DecisionDiagram$Leaf@54

  set_fp(context, fp);
  set_pc(context, pc);
#ifdef DEBUG
  print_value_simple(context, fn);
  printf(" is called in CALL instruction\n");
  abort();
#endif /* DEBUG */
  LOG_EXIT("CALL\n");
}
break;
case TV_GENERIC:
Lcall2: __attribute__((unused));switch((unsigned int) get_htag(fn).v){ // vmgen.newsynth.DecisionDiagram$HTNode@41d(3)
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
goto Lcall1;
break;
case HTAGV_FUNCTION:
Lcall3: __attribute__((unused));
TLcall_function: __attribute__((unused));
{ // normal_function vmgen.newsynth.DecisionDiagram$Leaf@1c49

  set_fp(context, fp);
  set_pc(context, pc);
  call_function(context, fn, nargs, sendp);
  update_context();
  NEXT_INSN_NOINCPC();
}
break;
case HTAGV_BUILTIN:
Lcall4: __attribute__((unused));
TLcall_builtin: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@1ec3

  set_fp(context, fp);
  set_pc(context, pc);
  call_builtin(context, fn, nargs, sendp, newp);
  update_context();
  NEXT_INSN_INCPC();
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@41d
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef fn
#undef nargs

