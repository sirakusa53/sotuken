#define link i0
#define index_ s1
#define src v2

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(setlocal,src);Lsetlocal0: __attribute__((unused));
TLsetlocal_special: __attribute__((unused));
TLsetlocal_string: __attribute__((unused));
TLsetlocal_regexp: __attribute__((unused));
TLsetlocal_any: __attribute__((unused));
TLsetlocal_string_object: __attribute__((unused));
TLsetlocal_simple_object: __attribute__((unused));
TLsetlocal_flonum: __attribute__((unused));
TLsetlocal_builtin: __attribute__((unused));
TLsetlocal_number_object: __attribute__((unused));
TLsetlocal_fixnum: __attribute__((unused));
TLsetlocal_array: __attribute__((unused));
TLsetlocal_iterator: __attribute__((unused));
TLsetlocal_boolean_object: __attribute__((unused));
TLsetlocal_function: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@54

  FunctionFrame *fr;
  int i;
  fr = get_lp(context);
  for (i = 0; i < link; i++) fr = fframe_prev(fr);
  fframe_locals_idx(fr, index_) = src;
}
#undef link
#undef index_
#undef src

