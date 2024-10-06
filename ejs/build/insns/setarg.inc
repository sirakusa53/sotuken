#define link i0
#define index_ s1
#define src v2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(setarg,src);Lsetarg0: __attribute__((unused));
TLsetarg_special: __attribute__((unused));
TLsetarg_string: __attribute__((unused));
TLsetarg_any: __attribute__((unused));
TLsetarg_array: __attribute__((unused));
TLsetarg_regexp: __attribute__((unused));
TLsetarg_fixnum: __attribute__((unused));
TLsetarg_simple_object: __attribute__((unused));
TLsetarg_builtin: __attribute__((unused));
TLsetarg_string_object: __attribute__((unused));
TLsetarg_number_object: __attribute__((unused));
TLsetarg_flonum: __attribute__((unused));
TLsetarg_function: __attribute__((unused));
TLsetarg_iterator: __attribute__((unused));
TLsetarg_boolean_object: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@54

  FunctionFrame *fr;
  JSValue arguments;
  int i;

  fr = get_lp(context);
  for (i = 0; i < link; i++) fr = fframe_prev(fr);
  // TODO: optimize
  arguments = fframe_arguments(fr);
  set_array_prop(context, arguments,
                 cint_to_number(context, (cint) index_), src);
}
#undef link
#undef index_
#undef src

