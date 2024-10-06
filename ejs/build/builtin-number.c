/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN extern
#include "header.h"

#ifdef USE_VMDL
#include "vmdl-extern.h"
#endif /* USE_VMDL */

#define BUFSIZE 1000
static char buf[BUFSIZE];

static inline JSValue numobj_to_string_radix(Context *context, JSValue rsv, cint radix){
  char map[36] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
  };
  int i, ff, acc;
  cint numeric;
  double decimal;
  int nlen, dlen;
  char str[100];
  nlen = dlen = 0;
  JSValue v = get_jsnumber_object_value(rsv);

  /*
    * divides the number into numeric and decimal parts
    */
  if(is_fixnum(v)) {
    numeric = fixnum_to_cint(v);
    decimal = 0.0;
  }else{
    numeric = (cint) flonum_to_double(v);
    decimal = flonum_to_double(v) - numeric; }

  /*
    * makes a string for the numeric part in the reverse order
    */
  while(numeric >= radix){
    str[nlen++] = map[numeric%radix];
    numeric /= radix; }
  str[nlen++] = map[numeric];

  /*
    * corrects the order of the numeric string
    */
  for(i=0; i<nlen/2; i++){
    ff = str[nlen-1-i];
    str[nlen-1-i] = str[i];
    str[i] = ff; }
  str[nlen++] = '.';

  /*
    * makes a string for the decimal part
    * accuracy is determined by the following expression
    */
  acc = (int)(48/((int)(log(radix)/log(2))));
  while((decimal != 0.0) && (dlen < acc)){
    str[nlen+dlen++] = map[(int)(decimal*radix)];
    decimal = decimal*radix - (int)(decimal*radix); }
  str[nlen+dlen++] = '\0';

  return cstr_to_string(context, str);
}

#ifdef USE_VMDL

static inline JSValue toFixed_helper(JSValue num, int digit){
  if(is_fixnum(num)){
    cint inum = fixnum_to_cint(num);
    snprintf(buf, BUFSIZE, "%" PRIcint ".%0*d", inum, digit, 0);
  }else{
    double dnum = number_to_double(num);
    snprintf(buf, BUFSIZE, "%.*f", digit+1, dnum+((0<dnum) ? 0.5 : -0.5)*pow(10,-digit));
    buf[strlen(buf)-(digit ? 1 : 2)] = '\0';
  }
  return cstr_to_string(NULL, buf);
}

static inline JSValue toExponential_helper(Context *context, JSValue num, JSValue js_digit, cint is_digit_given){
  double dnum = number_to_double(num);
  if(!is_digit_given || js_digit == JS_UNDEFINED){
    /* TODO: Improve the code when an argument is omitted. */
    snprintf(buf, BUFSIZE, "%e", dnum);
  }else{
    int digit = toInteger(context, js_digit);
    snprintf(buf, BUFSIZE, "%.*e", digit, dnum);
  }
  return cstr_to_string(NULL, buf);
}

static inline JSValue toPrecision_helper(Context *context, JSValue num, JSValue js_precision){
  int precision = toInteger(context, js_precision);
  cint ipart = toInteger(context, num);
  int idigits = log10(ipart) + 1;
  double dnum = number_to_double(num);
  if(precision < idigits){
    snprintf(buf, BUFSIZE, "%.*e", precision-1, dnum);
  }else if(precision == idigits){
    snprintf(buf, BUFSIZE, "%" PRIcint, ipart);
  }else{
    snprintf(buf, BUFSIZE, "%.*f", precision-idigits, dnum);
  }
  return cstr_to_string(NULL, buf);
}

#include "builtins/number_constr.inc"

#include "builtins/number_constr_nonew.inc"

#include "builtins/number_valueOf.inc"

#include "builtins/number_toString.inc"

#include "builtins/number_toFixed.inc"

#include "builtins/number_toExponential.inc"

#include "builtins/number_toPrecision.inc"

#else /* USE_VMDL */

/*
 * constructor of a number 
 */
BUILTIN_FUNCTION(number_constr)
{
  JSValue rsv;

  builtin_prologue();
  rsv = new_number_object(context, DEBUG_NAME("number_constr"),
                          gshapes.g_shape_Number, FIXNUM_ZERO);
  GC_PUSH(rsv);
  /* set___proto___all(context, rsv, gconsts.g_number_proto); */
  if (na > 0)
    set_jsnumber_object_value(rsv, to_number(context, args[1]));
  set_a(context, rsv);
  GC_POP(rsv);
}

/*
 * Number(arg)
 *   If this is called without `new', it acts as a type conversion
 *   function to a number.
 */
BUILTIN_FUNCTION(number_constr_nonew)
{
  JSValue ret;
  
  builtin_prologue();
  ret = (na > 0)? to_number(context, args[1]): FIXNUM_ZERO;
  set_a(context, ret);
}

BUILTIN_FUNCTION(number_valueOf)
{
  JSValue rsv;

  builtin_prologue();
  rsv = args[0];
  if (is_number_object(rsv))
    set_a(context, get_jsnumber_object_value(rsv));
  else
    LOG_EXIT("Receiver of valueOf is not a Number instance\n");
}

BUILTIN_FUNCTION(number_toString)
{
  JSValue rsv;

  builtin_prologue();
  rsv = args[0];
  if (is_number_object(rsv)) {
    if (na == 0 || args[1] == FIXNUM_TEN || args[1] == JS_UNDEFINED)
      set_a(context, number_to_string(get_jsnumber_object_value(rsv)));
    else {
      if(!is_fixnum(args[1])){
        LOG_ERR("args[1] is not a fixnum.");
        set_a(context, JS_UNDEFINED);
      }
      cint n = fixnum_to_cint(args[1]);
      set_a(context, numobj_to_string_radix(context, rsv, n));
    }

  } else if (is_number(rsv))
    set_a(context, number_to_string(rsv));
  else {

    /*
     * Type Error [FIXME]
     */ 
    LOG_EXIT("Number Instance's valueOf received not Number Instance\n");
  }
}

BUILTIN_FUNCTION(number_toFixed)
{
  JSValue num;
  cint inum;
  int digit;
  double dnum;

  builtin_prologue();

  num = args[0];
  assert(is_number(num) || is_number_object(num));
  num = to_number(context, num);
  digit = na >= 1 ? toInteger(context, args[1]) : 0;
  if(is_fixnum(num)){
    inum = fixnum_to_cint(num);
    snprintf(buf, BUFSIZE, "%" PRIcint ".%0*d", inum, digit, 0);
  }else{
    dnum = number_to_double(num);
    snprintf(buf, BUFSIZE, "%.*f", digit+1, dnum+((0<dnum) ? 0.5 : -0.5)*pow(10,-digit));
    buf[strlen(buf)-(digit ? 1 : 2)] = '\0';
  }
  set_a(context, cstr_to_string(NULL, buf));
  return;
}

BUILTIN_FUNCTION(number_toExponential)
{
  JSValue num;
  int digit;
  double dnum;

  builtin_prologue();

  num = args[0];
  assert(is_number(num) || is_number_object(num));
  num = to_number(context, num);
  dnum = number_to_double(num);
  if(na < 1 || args[1] ==JS_UNDEFINED){
    /* TODO: Improve the code when an argument is omitted. */
    snprintf(buf, BUFSIZE, "%e", dnum);
  }else{
    digit = toInteger(context, args[1]);
    snprintf(buf, BUFSIZE, "%.*e", digit, dnum);
  }
  set_a(context, cstr_to_string(NULL, buf));
  return;
}

BUILTIN_FUNCTION(number_toPrecision)
{
  JSValue num;
  cint ipart;
  int precision, idigits;
  double dnum;

  builtin_prologue();

  num = args[0];
  assert(is_number(num) || is_number_object(num));
  num = to_number(context, num);
  if(na < 1 || args[1] ==JS_UNDEFINED){
    JSValue fn = get_prop(gconsts.g_prototype_Number, gconsts.g_string_tostring);
    assert(is_builtin(fn));
    assert(is_number(args[0]) || is_number_object(args[0]));
    JSValue ret = invoke_builtin(context, args[0], fn, TRUE, JS_UNDEFINED, 0);
    set_a(context, ret);
    return;
  }else{
    precision = toInteger(context, args[1]);
    ipart = toInteger(context, num);
    idigits = log10(ipart) + 1;
    dnum = number_to_double(num);
    if(precision < idigits){
      snprintf(buf, BUFSIZE, "%.*e", precision-1, dnum);
    }else if(precision == idigits){
      snprintf(buf, BUFSIZE, "%" PRIcint, ipart);
    }else{
      snprintf(buf, BUFSIZE, "%.*f", precision-idigits, dnum);
    }
  }
  set_a(context, cstr_to_string(NULL, buf));
  return;
}

#endif /* USE_VMDL */

/*
 * property table
 */

/* prototype */
ObjBuiltinProp NumberPrototype_builtin_props[] = {
#ifndef ELIMINATED_NUMBER_VALUEOF
  { "valueOf",        number_valueOf,       0, ATTR_DE },
#endif
#ifndef ELIMINATED_NUMBER_TOSTRING
  { "toString",       number_toString,      0, ATTR_DE },
  #endif
#ifndef ELIMINATED_NUMBER_TOFIXED
  { "toFixed",        number_toFixed,       0, ATTR_DE },
#endif
#ifndef ELIMINATED_NUMBER_TOEXPONENTIAL
  { "toExponential",  number_toExponential, 0, ATTR_DE },
#endif
#ifndef ELIMINATED_NUMBER_TOEXPONENTIAL
  { "toPrecision",    number_toPrecision,   0, ATTR_DE },
#endif
};
ObjDoubleProp  NumberPrototype_double_props[] = {
};
ObjGconstsProp NumberPrototype_gconsts_props[] = {};
/* constructor */
ObjBuiltinProp NumberConstructor_builtin_props[] = {};
ObjDoubleProp  NumberConstructor_double_props[] = {
  { "MAX_VALUE", DBL_MAX,               ATTR_ALL, -1 },
  { "MIN_VALUE", DBL_MIN,               ATTR_ALL, -1 },
};
ObjGconstsProp NumberConstructor_gconsts_props[] = {
  { "prototype", &gconsts.g_prototype_Number,  ATTR_ALL },
  { "INFINITY",  &gconsts.g_flonum_infinity,   ATTR_ALL },
  { "NEGATIVE_INFINITY", &gconsts.g_flonum_negative_infinity, ATTR_ALL },
  { "NaN",       &gconsts.g_flonum_nan,        ATTR_ALL },
};
/* instance */
ObjBuiltinProp Number_builtin_props[] = {};
ObjDoubleProp  Number_double_props[] = {};
ObjGconstsProp Number_gconsts_props[] = {};
DEFINE_PROPERTY_TABLE_SIZES_PCI(Number);

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
