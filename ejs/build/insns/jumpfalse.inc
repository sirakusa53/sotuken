#define v v0
#define d d1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(jumpfalse,v);Ljumpfalse0: __attribute__((unused));
TLjumpfalse_any: __attribute__((unused));
TLjumpfalse_special: __attribute__((unused));
TLjumpfalse_function: __attribute__((unused));
TLjumpfalse_iterator: __attribute__((unused));
TLjumpfalse_simple_object: __attribute__((unused));
TLjumpfalse_string: __attribute__((unused));
TLjumpfalse_string_object: __attribute__((unused));
TLjumpfalse_number_object: __attribute__((unused));
TLjumpfalse_regexp: __attribute__((unused));
TLjumpfalse_flonum: __attribute__((unused));
TLjumpfalse_fixnum: __attribute__((unused));
TLjumpfalse_boolean_object: __attribute__((unused));
TLjumpfalse_builtin: __attribute__((unused));
TLjumpfalse_array: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   jumpfalse src disp
   if (!$src) pc = pc + $disp
 */

  if (v == JS_FALSE || (v != JS_TRUE && to_boolean(v) == JS_FALSE)) {
    set_pc_relative(d);
    NEXT_INSN_NOINCPC();
  }
}
#undef v
#undef d

