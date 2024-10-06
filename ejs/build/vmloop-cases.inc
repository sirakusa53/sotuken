I_FIXNUM: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    Register r0 __attribute__((unused)) = get_first_operand_reg(insn);
    SmallPrimitive i1 __attribute__((unused)) =get_small_immediate(insn);
#define USELABEL(x) fixnum_ ## x
#define DEFLABEL(x) fixnum_ ## x
#include "insns/fixnum.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_SPECCONST: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    Register r0 __attribute__((unused)) = get_first_operand_reg(insn);
    SmallPrimitive i1 __attribute__((unused)) =get_small_immediate(insn);
#define USELABEL(x) specconst_ ## x
#define DEFLABEL(x) specconst_ ## x
#include "insns/specconst.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_BIGPRIM: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    Register r0 __attribute__((unused)) = get_first_operand_reg(insn);
    ConstantDisplacement d1 __attribute__((unused)) =get_big_constant_disp(insn);
#define USELABEL(x) bigprim_ ## x
#define DEFLABEL(x) bigprim_ ## x
#include "insns/bigprim.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_ADDREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(add,v1,v2);
    goto TLadd_any_fixnum;
I_ADDREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_any_flonum;
I_ADDREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_any_string;
I_ADDREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_any_special;
I_ADDFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_fixnum_any;
I_ADDFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_fixnum_flonum;
I_ADDFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_fixnum_string;
I_ADDFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_fixnum_special;
I_ADDFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_flonum_any;
I_ADDFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(add,v1,v2);
    goto TLadd_flonum_fixnum;
I_ADDFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_flonum_string;
I_ADDFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_flonum_special;
I_ADDSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_string_any;
I_ADDSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(add,v1,v2);
    goto TLadd_string_fixnum;
I_ADDSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_string_flonum;
I_ADDSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_string_special;
I_ADDSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(add,v1,v2);
    goto TLadd_special_any;
I_ADDSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(add,v1,v2);
    goto TLadd_special_fixnum;
I_ADDSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_special_flonum;
I_ADDSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(add,v1,v2);
    goto TLadd_special_string;
I_ADD: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) add_ ## x
#define DEFLABEL(x) add_ ## x
#include "insns/add.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_SUBREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_any_fixnum;
I_SUBREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_any_flonum;
I_SUBREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_any_string;
I_SUBREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_any_special;
I_SUBFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_fixnum_any;
I_SUBFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_fixnum_flonum;
I_SUBFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_fixnum_string;
I_SUBFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_fixnum_special;
I_SUBFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_flonum_any;
I_SUBFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_flonum_fixnum;
I_SUBFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_flonum_string;
I_SUBFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_flonum_special;
I_SUBSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_string_any;
I_SUBSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_string_fixnum;
I_SUBSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_string_flonum;
I_SUBSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_string_special;
I_SUBSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_special_any;
I_SUBSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_special_fixnum;
I_SUBSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_special_flonum;
I_SUBSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(sub,v1,v2);
    goto TLsub_special_string;
I_SUB: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) sub_ ## x
#define DEFLABEL(x) sub_ ## x
#include "insns/sub.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_MULREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_any_fixnum;
I_MULREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_any_flonum;
I_MULREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_any_string;
I_MULREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_any_special;
I_MULFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_fixnum_any;
I_MULFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_fixnum_flonum;
I_MULFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_fixnum_string;
I_MULFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_fixnum_special;
I_MULFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_flonum_any;
I_MULFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_flonum_fixnum;
I_MULFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_flonum_string;
I_MULFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_flonum_special;
I_MULSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_string_any;
I_MULSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_string_fixnum;
I_MULSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_string_flonum;
I_MULSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_string_special;
I_MULSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_special_any;
I_MULSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_special_fixnum;
I_MULSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_special_flonum;
I_MULSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mul,v1,v2);
    goto TLmul_special_string;
I_MUL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) mul_ ## x
#define DEFLABEL(x) mul_ ## x
#include "insns/mul.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_DIVREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_any_fixnum;
I_DIVREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_any_flonum;
I_DIVREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_any_string;
I_DIVREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_any_special;
I_DIVFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_fixnum_any;
I_DIVFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_fixnum_flonum;
I_DIVFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_fixnum_string;
I_DIVFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_fixnum_special;
I_DIVFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_flonum_any;
I_DIVFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_flonum_fixnum;
I_DIVFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_flonum_string;
I_DIVFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_flonum_special;
I_DIVSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_string_any;
I_DIVSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_string_fixnum;
I_DIVSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_string_flonum;
I_DIVSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_string_special;
I_DIVSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_special_any;
I_DIVSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_special_fixnum;
I_DIVSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_special_flonum;
I_DIVSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(div,v1,v2);
    goto TLdiv_special_string;
I_DIV: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) div_ ## x
#define DEFLABEL(x) div_ ## x
#include "insns/div.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_MODREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_any_fixnum;
I_MODREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_any_flonum;
I_MODREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_any_string;
I_MODREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_any_special;
I_MODFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_fixnum_any;
I_MODFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_fixnum_flonum;
I_MODFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_fixnum_string;
I_MODFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_fixnum_special;
I_MODFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_flonum_any;
I_MODFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_flonum_fixnum;
I_MODFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_flonum_string;
I_MODFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_flonum_special;
I_MODSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_string_any;
I_MODSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_string_fixnum;
I_MODSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_string_flonum;
I_MODSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_string_special;
I_MODSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_special_any;
I_MODSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_special_fixnum;
I_MODSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_special_flonum;
I_MODSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(mod,v1,v2);
    goto TLmod_special_string;
I_MOD: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) mod_ ## x
#define DEFLABEL(x) mod_ ## x
#include "insns/mod.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_BITANDREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_any_fixnum;
I_BITANDREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_any_flonum;
I_BITANDREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_any_string;
I_BITANDREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_any_special;
I_BITANDFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_fixnum_any;
I_BITANDFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_fixnum_flonum;
I_BITANDFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_fixnum_string;
I_BITANDFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_fixnum_special;
I_BITANDFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_flonum_any;
I_BITANDFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_flonum_fixnum;
I_BITANDFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_flonum_string;
I_BITANDFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_flonum_special;
I_BITANDSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_string_any;
I_BITANDSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_string_fixnum;
I_BITANDSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_string_flonum;
I_BITANDSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_string_special;
I_BITANDSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_special_any;
I_BITANDSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_special_fixnum;
I_BITANDSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_special_flonum;
I_BITANDSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitand,v1,v2);
    goto TLbitand_special_string;
I_BITAND: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) bitand_ ## x
#define DEFLABEL(x) bitand_ ## x
#include "insns/bitand.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_BITORREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_any_fixnum;
I_BITORREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_any_flonum;
I_BITORREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_any_string;
I_BITORREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_any_special;
I_BITORFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_fixnum_any;
I_BITORFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_fixnum_flonum;
I_BITORFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_fixnum_string;
I_BITORFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_fixnum_special;
I_BITORFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_flonum_any;
I_BITORFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_flonum_fixnum;
I_BITORFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_flonum_string;
I_BITORFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_flonum_special;
I_BITORSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_string_any;
I_BITORSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_string_fixnum;
I_BITORSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_string_flonum;
I_BITORSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_string_special;
I_BITORSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_special_any;
I_BITORSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_special_fixnum;
I_BITORSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_special_flonum;
I_BITORSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(bitor,v1,v2);
    goto TLbitor_special_string;
I_BITOR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) bitor_ ## x
#define DEFLABEL(x) bitor_ ## x
#include "insns/bitor.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_LEFTSHIFTREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_any_fixnum;
I_LEFTSHIFTREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_any_flonum;
I_LEFTSHIFTREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_any_string;
I_LEFTSHIFTREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_any_special;
I_LEFTSHIFTFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_fixnum_any;
I_LEFTSHIFTFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_fixnum_flonum;
I_LEFTSHIFTFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_fixnum_string;
I_LEFTSHIFTFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_fixnum_special;
I_LEFTSHIFTFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_flonum_any;
I_LEFTSHIFTFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_flonum_fixnum;
I_LEFTSHIFTFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_flonum_string;
I_LEFTSHIFTFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_flonum_special;
I_LEFTSHIFTSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_string_any;
I_LEFTSHIFTSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_string_fixnum;
I_LEFTSHIFTSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_string_flonum;
I_LEFTSHIFTSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_string_special;
I_LEFTSHIFTSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_special_any;
I_LEFTSHIFTSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_special_fixnum;
I_LEFTSHIFTSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_special_flonum;
I_LEFTSHIFTSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(leftshift,v1,v2);
    goto TLleftshift_special_string;
I_LEFTSHIFT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) leftshift_ ## x
#define DEFLABEL(x) leftshift_ ## x
#include "insns/leftshift.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_RIGHTSHIFTREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_any_fixnum;
I_RIGHTSHIFTREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_any_flonum;
I_RIGHTSHIFTREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_any_string;
I_RIGHTSHIFTREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_any_special;
I_RIGHTSHIFTFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_fixnum_any;
I_RIGHTSHIFTFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_fixnum_flonum;
I_RIGHTSHIFTFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_fixnum_string;
I_RIGHTSHIFTFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_fixnum_special;
I_RIGHTSHIFTFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_flonum_any;
I_RIGHTSHIFTFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_flonum_fixnum;
I_RIGHTSHIFTFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_flonum_string;
I_RIGHTSHIFTFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_flonum_special;
I_RIGHTSHIFTSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_string_any;
I_RIGHTSHIFTSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_string_fixnum;
I_RIGHTSHIFTSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_string_flonum;
I_RIGHTSHIFTSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_string_special;
I_RIGHTSHIFTSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_special_any;
I_RIGHTSHIFTSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_special_fixnum;
I_RIGHTSHIFTSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_special_flonum;
I_RIGHTSHIFTSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(rightshift,v1,v2);
    goto TLrightshift_special_string;
I_RIGHTSHIFT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) rightshift_ ## x
#define DEFLABEL(x) rightshift_ ## x
#include "insns/rightshift.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_UNSIGNEDRIGHTSHIFTREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_any_fixnum;
I_UNSIGNEDRIGHTSHIFTREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_any_flonum;
I_UNSIGNEDRIGHTSHIFTREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_any_string;
I_UNSIGNEDRIGHTSHIFTREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_any_special;
I_UNSIGNEDRIGHTSHIFTFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_fixnum_any;
I_UNSIGNEDRIGHTSHIFTFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_fixnum_flonum;
I_UNSIGNEDRIGHTSHIFTFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_fixnum_string;
I_UNSIGNEDRIGHTSHIFTFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_fixnum_special;
I_UNSIGNEDRIGHTSHIFTFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_flonum_any;
I_UNSIGNEDRIGHTSHIFTFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_flonum_fixnum;
I_UNSIGNEDRIGHTSHIFTFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_flonum_string;
I_UNSIGNEDRIGHTSHIFTFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_flonum_special;
I_UNSIGNEDRIGHTSHIFTSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_string_any;
I_UNSIGNEDRIGHTSHIFTSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_string_fixnum;
I_UNSIGNEDRIGHTSHIFTSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_string_flonum;
I_UNSIGNEDRIGHTSHIFTSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_string_special;
I_UNSIGNEDRIGHTSHIFTSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_special_any;
I_UNSIGNEDRIGHTSHIFTSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_special_fixnum;
I_UNSIGNEDRIGHTSHIFTSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_special_flonum;
I_UNSIGNEDRIGHTSHIFTSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(unsignedrightshift,v1,v2);
    goto TLunsignedrightshift_special_string;
I_UNSIGNEDRIGHTSHIFT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) unsignedrightshift_ ## x
#define DEFLABEL(x) unsignedrightshift_ ## x
#include "insns/unsignedrightshift.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_LESSTHANREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_any_fixnum;
I_LESSTHANREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_any_flonum;
I_LESSTHANREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_any_string;
I_LESSTHANREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_any_special;
I_LESSTHANFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_fixnum_any;
I_LESSTHANFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_fixnum_flonum;
I_LESSTHANFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_fixnum_string;
I_LESSTHANFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_fixnum_special;
I_LESSTHANFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_flonum_any;
I_LESSTHANFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_flonum_fixnum;
I_LESSTHANFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_flonum_string;
I_LESSTHANFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_flonum_special;
I_LESSTHANSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_string_any;
I_LESSTHANSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_string_fixnum;
I_LESSTHANSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_string_flonum;
I_LESSTHANSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_string_special;
I_LESSTHANSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_special_any;
I_LESSTHANSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_special_fixnum;
I_LESSTHANSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_special_flonum;
I_LESSTHANSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthan,v1,v2);
    goto TLlessthan_special_string;
I_LESSTHAN: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) lessthan_ ## x
#define DEFLABEL(x) lessthan_ ## x
#include "insns/lessthan.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_LESSTHANEQUALREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_any_fixnum;
I_LESSTHANEQUALREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_any_flonum;
I_LESSTHANEQUALREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_any_string;
I_LESSTHANEQUALREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_any_special;
I_LESSTHANEQUALFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_fixnum_any;
I_LESSTHANEQUALFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_fixnum_flonum;
I_LESSTHANEQUALFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_fixnum_string;
I_LESSTHANEQUALFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_fixnum_special;
I_LESSTHANEQUALFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_flonum_any;
I_LESSTHANEQUALFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_flonum_fixnum;
I_LESSTHANEQUALFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_flonum_string;
I_LESSTHANEQUALFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_flonum_special;
I_LESSTHANEQUALSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_string_any;
I_LESSTHANEQUALSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_string_fixnum;
I_LESSTHANEQUALSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_string_flonum;
I_LESSTHANEQUALSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_string_special;
I_LESSTHANEQUALSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_special_any;
I_LESSTHANEQUALSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_special_fixnum;
I_LESSTHANEQUALSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_special_flonum;
I_LESSTHANEQUALSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(lessthanequal,v1,v2);
    goto TLlessthanequal_special_string;
I_LESSTHANEQUAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) lessthanequal_ ## x
#define DEFLABEL(x) lessthanequal_ ## x
#include "insns/lessthanequal.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_EQREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_any_fixnum;
I_EQREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_any_flonum;
I_EQREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_any_string;
I_EQREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_any_special;
I_EQFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_fixnum_any;
I_EQFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_fixnum_flonum;
I_EQFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_fixnum_string;
I_EQFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_fixnum_special;
I_EQFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_flonum_any;
I_EQFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_flonum_fixnum;
I_EQFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_flonum_string;
I_EQFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_flonum_special;
I_EQSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_string_any;
I_EQSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_string_fixnum;
I_EQSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_string_flonum;
I_EQSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_string_special;
I_EQSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_special_any;
I_EQSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_special_fixnum;
I_EQSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_special_flonum;
I_EQSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(eq,v1,v2);
    goto TLeq_special_string;
I_EQ: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) eq_ ## x
#define DEFLABEL(x) eq_ ## x
#include "insns/eq.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_EQUALREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_any_fixnum;
I_EQUALREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_any_flonum;
I_EQUALREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_any_string;
I_EQUALREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_any_special;
I_EQUALFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_fixnum_any;
I_EQUALFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_fixnum_flonum;
I_EQUALFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_fixnum_string;
I_EQUALFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_fixnum_special;
I_EQUALFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_flonum_any;
I_EQUALFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_flonum_fixnum;
I_EQUALFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_flonum_string;
I_EQUALFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_flonum_special;
I_EQUALSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_string_any;
I_EQUALSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_string_fixnum;
I_EQUALSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_string_flonum;
I_EQUALSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_string_special;
I_EQUALSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_special_any;
I_EQUALSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_special_fixnum;
I_EQUALSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_special_flonum;
I_EQUALSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(equal,v1,v2);
    goto TLequal_special_string;
I_EQUAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) equal_ ## x
#define DEFLABEL(x) equal_ ## x
#include "insns/equal.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    int i1 __attribute__((unused));
    Subscript s2 __attribute__((unused));
I_GETARG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    i1 = get_second_operand_int(insn);
    s2 = get_third_operand_subscr(insn);
#define USELABEL(x) getarg_ ## x
#define DEFLABEL(x) getarg_ ## x
#include "insns/getarg.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    int i0 __attribute__((unused));
    Subscript s1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_SETARG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    i0 = get_first_operand_int(insn);
    s1 = get_second_operand_subscr(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) setarg_ ## x
#define DEFLABEL(x) setarg_ ## x
#include "insns/setarg.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_GETPROPREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_any_fixnum;
I_GETPROPREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_any_flonum;
I_GETPROPREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_any_string;
I_GETPROPREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_any_special;
I_GETPROPFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_fixnum_any;
I_GETPROPFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_fixnum_flonum;
I_GETPROPFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_fixnum_string;
I_GETPROPFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_fixnum_special;
I_GETPROPFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_flonum_any;
I_GETPROPFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_flonum_fixnum;
I_GETPROPFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_flonum_string;
I_GETPROPFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_flonum_special;
I_GETPROPSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_string_any;
I_GETPROPSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_string_fixnum;
I_GETPROPSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_string_flonum;
I_GETPROPSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_string_special;
I_GETPROPSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_special_any;
I_GETPROPSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_special_fixnum;
I_GETPROPSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_special_flonum;
I_GETPROPSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT2(getprop,v1,v2);
    goto TLgetprop_special_string;
I_GETPROP: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) getprop_ ## x
#define DEFLABEL(x) getprop_ ## x
#include "insns/getprop.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    JSValue v0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_SETPROPREGREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_any_fixnum;
I_SETPROPREGREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_any_flonum;
I_SETPROPREGREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_any_string;
I_SETPROPREGREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_any_special;
I_SETPROPREGFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_fixnum_any;
I_SETPROPREGFIXFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_fixnum_fixnum;
I_SETPROPREGFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_fixnum_flonum;
I_SETPROPREGFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_fixnum_string;
I_SETPROPREGFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_fixnum_special;
I_SETPROPREGFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_flonum_any;
I_SETPROPREGFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_flonum_fixnum;
I_SETPROPREGFLOFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_flonum_flonum;
I_SETPROPREGFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_flonum_string;
I_SETPROPREGFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_flonum_special;
I_SETPROPREGSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_string_any;
I_SETPROPREGSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_string_fixnum;
I_SETPROPREGSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_string_flonum;
I_SETPROPREGSTRSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_string_string;
I_SETPROPREGSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_string_special;
I_SETPROPREGSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_special_any;
I_SETPROPREGSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_special_fixnum;
I_SETPROPREGSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_special_flonum;
I_SETPROPREGSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_special_string;
I_SETPROPREGSPECSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_any_special_special;
I_SETPROPFIXREGREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_any_any;
I_SETPROPFIXREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_any_fixnum;
I_SETPROPFIXREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_any_flonum;
I_SETPROPFIXREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_any_string;
I_SETPROPFIXREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_any_special;
I_SETPROPFIXFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_fixnum_any;
I_SETPROPFIXFIXFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_fixnum_fixnum;
I_SETPROPFIXFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_fixnum_flonum;
I_SETPROPFIXFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_fixnum_string;
I_SETPROPFIXFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_fixnum_special;
I_SETPROPFIXFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_flonum_any;
I_SETPROPFIXFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_flonum_fixnum;
I_SETPROPFIXFLOFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_flonum_flonum;
I_SETPROPFIXFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_flonum_string;
I_SETPROPFIXFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_flonum_special;
I_SETPROPFIXSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_string_any;
I_SETPROPFIXSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_string_fixnum;
I_SETPROPFIXSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_string_flonum;
I_SETPROPFIXSTRSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_string_string;
I_SETPROPFIXSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_string_special;
I_SETPROPFIXSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_special_any;
I_SETPROPFIXSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_special_fixnum;
I_SETPROPFIXSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_special_flonum;
I_SETPROPFIXSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_special_string;
I_SETPROPFIXSPECSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = small_cint_to_fixnum(get_first_operand_int(insn));
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_fixnum_special_special;
I_SETPROPFLOREGREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_any_any;
I_SETPROPFLOREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_any_fixnum;
I_SETPROPFLOREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_any_flonum;
I_SETPROPFLOREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_any_string;
I_SETPROPFLOREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_any_special;
I_SETPROPFLOFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_fixnum_any;
I_SETPROPFLOFIXFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_fixnum_fixnum;
I_SETPROPFLOFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_fixnum_flonum;
I_SETPROPFLOFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_fixnum_string;
I_SETPROPFLOFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_fixnum_special;
I_SETPROPFLOFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_flonum_any;
I_SETPROPFLOFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_flonum_fixnum;
I_SETPROPFLOFLOFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_flonum_flonum;
I_SETPROPFLOFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_flonum_string;
I_SETPROPFLOFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_flonum_special;
I_SETPROPFLOSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_string_any;
I_SETPROPFLOSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_string_fixnum;
I_SETPROPFLOSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_string_flonum;
I_SETPROPFLOSTRSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_string_string;
I_SETPROPFLOSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_string_special;
I_SETPROPFLOSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_special_any;
I_SETPROPFLOSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_special_fixnum;
I_SETPROPFLOSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_special_flonum;
I_SETPROPFLOSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_special_string;
I_SETPROPFLOSPECSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_flonum_special_special;
I_SETPROPSTRREGREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_any_any;
I_SETPROPSTRREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_any_fixnum;
I_SETPROPSTRREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_any_flonum;
I_SETPROPSTRREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_any_string;
I_SETPROPSTRREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_any_special;
I_SETPROPSTRFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_fixnum_any;
I_SETPROPSTRFIXFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_fixnum_fixnum;
I_SETPROPSTRFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_fixnum_flonum;
I_SETPROPSTRFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_fixnum_string;
I_SETPROPSTRFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_fixnum_special;
I_SETPROPSTRFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_flonum_any;
I_SETPROPSTRFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_flonum_fixnum;
I_SETPROPSTRFLOFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_flonum_flonum;
I_SETPROPSTRFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_flonum_string;
I_SETPROPSTRFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_flonum_special;
I_SETPROPSTRSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_string_any;
I_SETPROPSTRSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_string_fixnum;
I_SETPROPSTRSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_string_flonum;
I_SETPROPSTRSTRSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_string_string;
I_SETPROPSTRSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_string_special;
I_SETPROPSTRSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_special_any;
I_SETPROPSTRSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_special_fixnum;
I_SETPROPSTRSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_special_flonum;
I_SETPROPSTRSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_special_string;
I_SETPROPSTRSPECSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = curfn->constants[get_first_operand_constant_disp(insn)];
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_string_special_special;
I_SETPROPSPECREGREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_any_any;
I_SETPROPSPECREGFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_value(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_any_fixnum;
I_SETPROPSPECREGFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_any_flonum;
I_SETPROPSPECREGSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_value(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_any_string;
I_SETPROPSPECREGSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_any_special;
I_SETPROPSPECFIXREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_fixnum_any;
I_SETPROPSPECFIXFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_fixnum_fixnum;
I_SETPROPSPECFIXFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_fixnum_flonum;
I_SETPROPSPECFIXSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_fixnum_string;
I_SETPROPSPECFIXSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = small_cint_to_fixnum(get_second_operand_int(insn));
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_fixnum_special;
I_SETPROPSPECFLOREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_flonum_any;
I_SETPROPSPECFLOFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_flonum_fixnum;
I_SETPROPSPECFLOFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_flonum_flonum;
I_SETPROPSPECFLOSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_flonum_string;
I_SETPROPSPECFLOSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_flonum_special;
I_SETPROPSPECSTRREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_string_any;
I_SETPROPSPECSTRFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_string_fixnum;
I_SETPROPSPECSTRFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_string_flonum;
I_SETPROPSPECSTRSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_string_string;
I_SETPROPSPECSTRSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = curfn->constants[get_second_operand_constant_disp(insn)];
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_string_special;
I_SETPROPSPECSPECREG: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_value(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_special_any;
I_SETPROPSPECSPECFIX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_int(insn);
    v2 = small_cint_to_fixnum(get_third_operand_int(insn));
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_special_fixnum;
I_SETPROPSPECSPECFLO: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_special_flonum;
I_SETPROPSPECSPECSTR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_int(insn);
    v2 = curfn->constants[get_third_operand_constant_disp(insn)];
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_special_string;
I_SETPROPSPECSPECSPEC: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_int(insn);
    v1 = get_second_operand_int(insn);
    v2 = get_third_operand_int(insn);
    INSN_COUNT3(setprop,v0,v1,v2);
    goto TLsetprop_special_special_special;
I_SETPROP: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) setprop_ ## x
#define DEFLABEL(x) setprop_ ## x
#include "insns/setprop.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_GETGLOBAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) getglobal_ ## x
#define DEFLABEL(x) getglobal_ ## x
#include "insns/getglobal.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    JSValue v0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_SETGLOBAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) setglobal_ ## x
#define DEFLABEL(x) setglobal_ ## x
#include "insns/setglobal.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    JSValue v2 __attribute__((unused));
I_INSTANCEOF: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    v2 = get_third_operand_value(insn);
#define USELABEL(x) instanceof_ ## x
#define DEFLABEL(x) instanceof_ ## x
#include "insns/instanceof.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_MOVE: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) move_ ## x
#define DEFLABEL(x) move_ ## x
#include "insns/move.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    Register r1 __attribute__((unused));
I_TYPEOF: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    r1 = get_second_operand_reg(insn);
#define USELABEL(x) typeof_ ## x
#define DEFLABEL(x) typeof_ ## x
#include "insns/typeof.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_NOT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) not_ ## x
#define DEFLABEL(x) not_ ## x
#include "insns/not.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_ISUNDEF: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) isundef_ ## x
#define DEFLABEL(x) isundef_ ## x
#include "insns/isundef.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_ISOBJECT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) isobject_ ## x
#define DEFLABEL(x) isobject_ ## x
#include "insns/isobject.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    int i0 __attribute__((unused));
I_SETFL: __attribute__((unused));
  ENTER_INSN(__LINE__);
    i0 = get_first_operand_int(insn);
#define USELABEL(x) setfl_ ## x
#define DEFLABEL(x) setfl_ ## x
#include "insns/setfl.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    JSValue v0 __attribute__((unused));
I_SETA: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
#define USELABEL(x) seta_ ## x
#define DEFLABEL(x) seta_ ## x
#include "insns/seta.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
I_GETA: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
#define USELABEL(x) geta_ ## x
#define DEFLABEL(x) geta_ ## x
#include "insns/geta.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
I_GETNEWA: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
#define USELABEL(x) getnewa_ ## x
#define DEFLABEL(x) getnewa_ ## x
#include "insns/getnewa.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
I_GETERR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
#define USELABEL(x) geterr_ ## x
#define DEFLABEL(x) geterr_ ## x
#include "insns/geterr.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
I_GETGLOBALOBJ: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
#define USELABEL(x) getglobalobj_ ## x
#define DEFLABEL(x) getglobalobj_ ## x
#include "insns/getglobalobj.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    int i0 __attribute__((unused));
    int i1 __attribute__((unused));
I_NEWFRAME: __attribute__((unused));
  ENTER_INSN(__LINE__);
    i0 = get_first_operand_int(insn);
    i1 = get_second_operand_int(insn);
#define USELABEL(x) newframe_ ## x
#define DEFLABEL(x) newframe_ ## x
#include "insns/newframe.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
I_EXITFRAME: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) exitframe_ ## x
#define DEFLABEL(x) exitframe_ ## x
#include "insns/exitframe.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
I_RET: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) ret_ ## x
#define DEFLABEL(x) ret_ ## x
#include "insns/ret.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
I_NOP: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) nop_ ## x
#define DEFLABEL(x) nop_ ## x
#include "insns/nop.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

I_JUMP: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    InstructionDisplacement d0 = get_operand_instruction_disp(insn);
#define USELABEL(x) jump_ ## x
#define DEFLABEL(x) jump_ ## x
#include "insns/jump.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_NOINCPC();

I_JUMPTRUE: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    JSValue v0 __attribute__((unused)) = get_first_operand_value(insn);
    InstructionDisplacement d1 = get_operand_instruction_disp(insn);
#define USELABEL(x) jumptrue_ ## x
#define DEFLABEL(x) jumptrue_ ## x
#include "insns/jumptrue.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_JUMPFALSE: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    JSValue v0 __attribute__((unused)) = get_first_operand_value(insn);
    InstructionDisplacement d1 = get_operand_instruction_disp(insn);
#define USELABEL(x) jumpfalse_ ## x
#define DEFLABEL(x) jumpfalse_ ## x
#include "insns/jumpfalse.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_GETLOCAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    Register r0 __attribute__((unused)) = get_first_operand_reg(insn);
    int i1 __attribute__((unused)) = get_second_operand_int(insn);
    Subscript s2 __attribute__((unused)) = get_third_operand_subscr(insn);
#define USELABEL(x) getlocal_ ## x
#define DEFLABEL(x) getlocal_ ## x
#include "insns/getlocal.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_SETLOCAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    int i0 __attribute__((unused)) = get_first_operand_int(insn);
    Subscript s1 __attribute__((unused)) = get_second_operand_subscr(insn);
    JSValue v2 __attribute__((unused)) = get_third_operand_value(insn);
#define USELABEL(x) setlocal_ ## x
#define DEFLABEL(x) setlocal_ ## x
#include "insns/setlocal.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_MAKECLOSURE: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    Register r0 __attribute__((unused)) = get_first_operand_reg(insn);
    Subscript s1 __attribute__((unused)) = get_second_operand_subscr(insn);
#define USELABEL(x) makeclosure_ ## x
#define DEFLABEL(x) makeclosure_ ## x
#include "insns/makeclosure.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_MAKEITERATOR: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) makeiterator_ ## x
#define DEFLABEL(x) makeiterator_ ## x
#include "insns/makeiterator.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
I_NEXTPROPNAMEIDX: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
#define USELABEL(x) nextpropnameidx_ ## x
#define DEFLABEL(x) nextpropnameidx_ ## x
#include "insns/nextpropnameidx.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

I_SEND: __attribute__((unused));
I_CALL: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    JSValue v0 __attribute__((unused)) = get_first_operand_value(insn);
    int i1 __attribute__((unused)) = get_second_operand_int(insn);
#define USELABEL(x) call_ ## x
#define DEFLABEL(x) call_ ## x
#include "insns/call.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

I_TAILSEND: __attribute__((unused));
I_TAILCALL: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    JSValue v0 __attribute__((unused)) = get_first_operand_value(insn);
    int i1 __attribute__((unused)) = get_second_operand_int(insn);
#define USELABEL(x) tailcall_ ## x
#define DEFLABEL(x) tailcall_ ## x
#include "insns/tailcall.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

  {
    Register r0 __attribute__((unused));
    JSValue v1 __attribute__((unused));
    int i2 __attribute__((unused));
I_CONSTRUCT: __attribute__((unused));
  ENTER_INSN(__LINE__);
    r0 = get_first_operand_reg(insn);
    v1 = get_second_operand_value(insn);
    i2 = get_third_operand_int(insn);
#define USELABEL(x) construct_ ## x
#define DEFLABEL(x) construct_ ## x
#include "insns/construct.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

I_PUSHHANDLER: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    InstructionDisplacement d0 = get_operand_instruction_disp(insn);
#define USELABEL(x) pushhandler_ ## x
#define DEFLABEL(x) pushhandler_ ## x
#include "insns/pushhandler.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

  {
I_POPHANDLER: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) pophandler_ ## x
#define DEFLABEL(x) pophandler_ ## x
#include "insns/pophandler.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
    JSValue v0 __attribute__((unused));
I_THROW: __attribute__((unused));
  ENTER_INSN(__LINE__);
    v0 = get_first_operand_value(insn);
#define USELABEL(x) throw_ ## x
#define DEFLABEL(x) throw_ ## x
#include "insns/throw.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_NOINCPC();
  }

I_LOCALCALL: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
    InstructionDisplacement d0 = get_operand_instruction_disp(insn);
#define USELABEL(x) localcall_ ## x
#define DEFLABEL(x) localcall_ ## x
#include "insns/localcall.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_NOINCPC();

  {
I_LOCALRET: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) localret_ ## x
#define DEFLABEL(x) localret_ ## x
#include "insns/localret.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

  {
I_POPLOCAL: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) poplocal_ ## x
#define DEFLABEL(x) poplocal_ ## x
#include "insns/poplocal.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

I_UNKNOWN: __attribute__((unused));
  ENTER_INSN(__LINE__);
  {
#define USELABEL(x) unknown_ ## x
#define DEFLABEL(x) unknown_ ## x
#include "insns/unknown.inc"
#undef USELABEL
#undef DEFLABEL
  }
  NEXT_INSN_INCPC();

  {
I_END: __attribute__((unused));
  ENTER_INSN(__LINE__);
#define USELABEL(x) end_ ## x
#define DEFLABEL(x) end_ ## x
#include "insns/end.inc"
#undef USELABEL
#undef DEFLABEL
  NEXT_INSN_INCPC();
  }

