#define src v0

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(throw,src);Lthrow0: __attribute__((unused));
TLthrow_array: __attribute__((unused));
TLthrow_special: __attribute__((unused));
TLthrow_iterator: __attribute__((unused));
TLthrow_number_object: __attribute__((unused));
TLthrow_function: __attribute__((unused));
TLthrow_regexp: __attribute__((unused));
TLthrow_flonum: __attribute__((unused));
TLthrow_string: __attribute__((unused));
TLthrow_any: __attribute__((unused));
TLthrow_boolean_object: __attribute__((unused));
TLthrow_builtin: __attribute__((unused));
TLthrow_fixnum: __attribute__((unused));
TLthrow_simple_object: __attribute__((unused));
TLthrow_string_object: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@54

  save_context();
  set_a(context, src);
  exhandler_throw(context);
  /* exhandler_throw never returns */
}
#undef src

