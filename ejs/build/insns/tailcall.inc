#define fn v0
#define nargs i1

  int sendp = (get_opcode(insn) == TAILSEND)? TRUE: FALSE;

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(tailcall,fn);Ltailcall0: __attribute__((unused));
TLtailcall_any: __attribute__((unused));
switch((unsigned int) get_ptag(fn).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(2)
case TV_STRING:
case 3:
case 2:
case 1:
case TV_FLONUM:
case TV_SPECIAL:
case TV_FIXNUM:
default:
Ltailcall1: __attribute__((unused));
TLtailcall_special: __attribute__((unused));
TLtailcall_array: __attribute__((unused));
TLtailcall_boolean_object: __attribute__((unused));
TLtailcall_flonum: __attribute__((unused));
TLtailcall_number_object: __attribute__((unused));
TLtailcall_regexp: __attribute__((unused));
TLtailcall_fixnum: __attribute__((unused));
TLtailcall_simple_object: __attribute__((unused));
TLtailcall_string_object: __attribute__((unused));
TLtailcall_string: __attribute__((unused));
TLtailcall_iterator: __attribute__((unused));
{ // normal_iterator vmgen.newsynth.DecisionDiagram$Leaf@54

  LOG_EXIT("TAILCALL: not a function\n");
}
break;
case TV_GENERIC:
Ltailcall2: __attribute__((unused));switch((unsigned int) get_htag(fn).v){ // vmgen.newsynth.DecisionDiagram$HTNode@41d(3)
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
goto Ltailcall1;
break;
case HTAGV_FUNCTION:
Ltailcall3: __attribute__((unused));
TLtailcall_function: __attribute__((unused));
{ // normal_function vmgen.newsynth.DecisionDiagram$Leaf@1c49

  set_fp(context, fp);
  set_pc(context, pc);
  try_gc(context);
  tailcall_function(context, fn, nargs, sendp);
  update_context();
  NEXT_INSN_NOINCPC();
}
break;
case HTAGV_BUILTIN:
Ltailcall4: __attribute__((unused));
TLtailcall_builtin: __attribute__((unused));
{ // normal_builtin vmgen.newsynth.DecisionDiagram$Leaf@1ec3

  set_fp(context, fp);
  set_pc(context, pc);
  try_gc(context);
  tailcall_builtin(context, fn, nargs, sendp, FALSE);
  update_context();
  NEXT_INSN_INCPC();
}
break;
}// vmgen.newsynth.DecisionDiagram$HTNode@41d
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef fn
#undef nargs

