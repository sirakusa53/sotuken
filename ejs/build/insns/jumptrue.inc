#define v v0
#define d d1

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(jumptrue,v);Ljumptrue0: __attribute__((unused));
TLjumptrue_string: __attribute__((unused));
TLjumptrue_number_object: __attribute__((unused));
TLjumptrue_array: __attribute__((unused));
TLjumptrue_regexp: __attribute__((unused));
TLjumptrue_builtin: __attribute__((unused));
TLjumptrue_simple_object: __attribute__((unused));
TLjumptrue_string_object: __attribute__((unused));
TLjumptrue_flonum: __attribute__((unused));
TLjumptrue_any: __attribute__((unused));
TLjumptrue_boolean_object: __attribute__((unused));
TLjumptrue_function: __attribute__((unused));
TLjumptrue_special: __attribute__((unused));
TLjumptrue_fixnum: __attribute__((unused));
TLjumptrue_iterator: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@54

/*
   jumptrue src disp
   if (!$src) pc = pc + $disp
 */

  if (v == JS_TRUE || (v != JS_FALSE && to_boolean(v) == JS_TRUE)) {
    set_pc_relative(d);
    NEXT_INSN_NOINCPC();
  }
}
#undef v
#undef d

