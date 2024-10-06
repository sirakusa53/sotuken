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

#define set_a_number(x) set_a(context, double_to_number(context, (x)))

/*
 * NOTE: 'math_func' and 'math_func2' have different definitions with and without the USE_VMDL definition.
 */
#ifdef USE_VMDL
JSValue math_func(Context *context, double (*fn)(double), JSValue v) {
  double x;

  if (!is_number(v)) v = to_number(context, v);
  if (is_nan(v)) {
    return double_to_number(context, v);
  }
  /* v is either fixnum or flonum */
  x = number_to_double(v);
  x = (*fn)(x);
  return double_to_number(context, x);
}

JSValue math_func2(Context *context, double (*fn)(double, double), JSValue v1, JSValue v2) {
  double x1, x2;

  if (!is_number(v1)) v1 = to_number(context, v1);
  if (is_nan(v1)) {
    return double_to_number(context, v1);
  }
  x1 = number_to_double(v1);
  if (!is_number(v2)) v2 = to_number(context, v2);
  if (is_nan(v2)) {
    return double_to_number(context, v2);
  }
  x2 = number_to_double(v2);
  x1 = (*fn)(x1, x2);
  return double_to_number(context, x1);
}
#else /* USE_VMDL */
void math_func(Context *context, int fp, double (*fn)(double)) {
  JSValue v;
  double x;

  builtin_prologue();
  v = args[1];
  if (!is_number(v)) v = to_number(context, v);
  if (is_nan(v)) {
    set_a(context, v);
    return;
  }
  /* v is either fixnum or flonum */
  x = number_to_double(v);
  x = (*fn)(x);
  set_a_number(x);
}

void math_func2(Context *context, int fp, double (*fn)(double, double)) {
  JSValue v1, v2;
  double x1, x2;

  builtin_prologue();

  v1 = args[1];
  if (!is_number(v1)) v1 = to_number(context, v1);
  if (is_nan(v1)) {
    set_a(context, v1);
    return;
  }
  x1 = number_to_double(v1);

  v2 = args[2];
  if (!is_number(v2)) v2 = to_number(context, v2);
  if (is_nan(v2)) {
    set_a(context, v2);
    return;
  }
  x2 = number_to_double(v2);

  x1 = (*fn)(x1, x2);
  set_a_number(x1);
}
#endif /* USE_VMDL */


#ifdef USE_VMDL

#include "builtins/math_max.inc"

#include "builtins/math_min.inc"

#include "builtins/math_abs.inc"

#include "builtins/math_sqrt.inc"

#include "builtins/math_sin.inc"

#include "builtins/math_cos.inc"

#include "builtins/math_tan.inc"

#include "builtins/math_asin.inc"

#include "builtins/math_acos.inc"

#include "builtins/math_atan.inc"

#include "builtins/math_atan2.inc"

#include "builtins/math_exp.inc"

#include "builtins/math_log.inc"

#include "builtins/math_ceil.inc"

#include "builtins/math_floor.inc"

#include "builtins/math_round.inc"

#include "builtins/math_pow.inc"

#include "builtins/math_random.inc"

#else /* USE_VMDL */

BUILTIN_FUNCTION(math_max)
{
  JSValue v;
  double x, r;
  int i;

  builtin_prologue();
  r = -INFINITY;
  for (i = 1; i <= na; i++) {
    v = args[i];
    if (!is_number(v)) v = to_number(context, v);
    if (is_nan(v)) r = NAN;
    /* v is either fixnum or flonum */
    x = number_to_double(v);
    if (r < x) r = x;
  }
  set_a_number(r);
}

BUILTIN_FUNCTION(math_min)
{
  JSValue v;
  double x, r;
  int i;

  builtin_prologue();
  r = INFINITY;
  for (i = 1; i <= na; i++) {
    v = args[i];
    if (!is_number(v)) v = to_number(context, v);
    if (is_nan(v)) r = NAN;
    /* v is either fixnum or flonum */
    x = number_to_double(v);
    if (x < r) r = x;
  }
  set_a_number(r);
}

BUILTIN_FUNCTION(math_abs)
{
  math_func(context, fp, &fabs);
}

BUILTIN_FUNCTION(math_sqrt)
{
  math_func(context, fp, &sqrt);
}

BUILTIN_FUNCTION(math_sin)
{
  math_func(context, fp, &sin);
}

BUILTIN_FUNCTION(math_cos)
{
  math_func(context, fp, &cos);
}

BUILTIN_FUNCTION(math_tan)
{
  math_func(context, fp, &tan);
}

BUILTIN_FUNCTION(math_asin)
{
  math_func(context, fp, &asin);
}

BUILTIN_FUNCTION(math_acos)
{
  math_func(context, fp, &acos);
}

BUILTIN_FUNCTION(math_atan)
{
  math_func(context, fp, &atan);
}

BUILTIN_FUNCTION(math_atan2)
{
  math_func2(context, fp, &atan2);
}

BUILTIN_FUNCTION(math_exp)
{
  math_func(context, fp, &exp);
}

BUILTIN_FUNCTION(math_log)
{
  math_func(context, fp, &log);
}

BUILTIN_FUNCTION(math_ceil)
{
  math_func(context, fp, &ceil);
}

BUILTIN_FUNCTION(math_floor)
{
  math_func(context, fp, &floor);
}

BUILTIN_FUNCTION(math_round)
{
  math_func(context, fp, &round);
}

BUILTIN_FUNCTION(math_pow)
{
  math_func2(context, fp, pow);
}

BUILTIN_FUNCTION(math_random)
{
  double x;

  x = ((double)rand()) / (((double)RAND_MAX) + 1);
  set_a_number(x);
}

#endif /* USE_VMDL*/

/*
 * property table
 */

/* instance */
ObjBuiltinProp Math_builtin_props[] = {
#ifndef ELIMINATED_MATH_ABS
  { "abs",    math_abs,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_SQRT
  { "sqrt",   math_sqrt,   1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_SIN
  { "sin",    math_sin,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_COS
  { "cos",    math_cos,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_TAN
  { "tan",    math_tan,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_ASIN
  { "asin",   math_asin,   1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_ACOS
  { "acos",   math_acos,   1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_ATAN
  { "atan",   math_atan,   1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_ATAN2
  { "atan2",  math_atan2,  2, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_EXP
  { "exp",    math_exp,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_LOG
  { "log",    math_log,    1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_CEIL
  { "ceil",   math_ceil,   1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_FLOOR
  { "floor",  math_floor,  1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_ROUND
  { "round",  math_round,  1, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_MAX
  { "max",    math_max,    0, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_MIN
  { "min",    math_min,    0, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_POW
  { "pow",    math_pow,    2, ATTR_DE },
#endif
#ifndef ELIMINATED_MATH_RANDOM
  { "random", math_random, 0, ATTR_DE },
#endif
};
ObjDoubleProp  Math_double_props[] = {
  { "E",         2.7182818284590452354, ATTR_ALL, -1 },
  { "LN10",      2.302585092994046,     ATTR_ALL, -1 },
  { "LN2",       0.6931471805599453,    ATTR_ALL, -1 },
  { "LOG2E",     1.4426950408889634,    ATTR_ALL, -1 },
  { "LOG10E",    0.4342944819032518,    ATTR_ALL, -1 },
  { "PI",        3.1415926535897932,    ATTR_ALL, -1 },
  { "SQRT1_2",   0.7071067811865476,    ATTR_ALL, -1 },
  { "SQRT2",     1.4142135623730951,    ATTR_ALL, -1 },
};
ObjGconstsProp Math_gconsts_props[] = {};
DEFINE_PROPERTY_TABLE_SIZES_I(Math);

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
