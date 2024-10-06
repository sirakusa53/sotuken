#define dst regbase[r0]

DEFLABEL(HEAD): __attribute__((unused));
INSN_COUNT1(not,v1);Lnot0: __attribute__((unused));
TLnot_any: __attribute__((unused));
switch((unsigned int) get_ptag(v1).v){ // vmgen.newsynth.DecisionDiagram$PTNode@550(5)
case TV_GENERIC:
Lnot1: __attribute__((unused));
TLnot_builtin: __attribute__((unused));
TLnot_simple_object: __attribute__((unused));
TLnot_string_object: __attribute__((unused));
TLnot_array: __attribute__((unused));
TLnot_boolean_object: __attribute__((unused));
TLnot_iterator: __attribute__((unused));
TLnot_function: __attribute__((unused));
TLnot_number_object: __attribute__((unused));
TLnot_regexp: __attribute__((unused));
{ // normal_array vmgen.newsynth.DecisionDiagram$Leaf@54

  dst = JS_FALSE;
}
break;
case TV_FIXNUM:
default:
Lnot2: __attribute__((unused));
TLnot_fixnum: __attribute__((unused));
{ // normal_fixnum vmgen.newsynth.DecisionDiagram$Leaf@dbb

  dst = true_false(v1 == FIXNUM_ZERO);
}
break;
case TV_STRING:
case 3:
case 2:
case 1:
Lnot3: __attribute__((unused));
TLnot_string: __attribute__((unused));
{ // normal_string vmgen.newsynth.DecisionDiagram$Leaf@118b

  dst = true_false(v1 == gconsts.g_string_empty);
}
break;
case TV_SPECIAL:
Lnot4: __attribute__((unused));
TLnot_special: __attribute__((unused));
{ // normal_special vmgen.newsynth.DecisionDiagram$Leaf@1c49

  dst = v1 == JS_TRUE ? JS_FALSE : JS_TRUE;
}
break;
case TV_FLONUM:
Lnot5: __attribute__((unused));
TLnot_flonum: __attribute__((unused));
{ // normal_flonum vmgen.newsynth.DecisionDiagram$Leaf@1f5d

  dst = true_false(v1 == gconsts.g_flonum_nan);
}
break;
} // vmgen.newsynth.DecisionDiagram$PTNode@550
#undef dst

