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


#define type_error_exception(s)  LOG_EXIT("Type error exception: " s "\n")
#define type_error(s)  LOG_EXIT("Type error: " s "\n")

#define invoke_function0(ctx, receiver, fn, sendp)              \
  invoke_function(ctx, receiver, fn, sendp, JS_UNDEFINED, 0)
#define invoke_builtin0(ctx, receiver, fn, sendp)               \
  invoke_builtin(ctx, receiver, fn, sendp, JS_UNDEFINED, 0)

/*
 * Data conversion rules of JavaScript
 *
 * source value  destination
 *               string       number     boolean     Object
 * ---------------------------------------------------------------------
 * undefined     "undefined"  NaN        false       TypeError exception
 * null          "null"       0          false       TypeError exception
 * ---------------------------------------------------------------------
 * true          "true"       1          ---         new Boolean(true)
 * false         "false"      0          ---         new Boolean(false)
 * ---------------------------------------------------------------------
 * ""            ---          0          false       new String("")
 * "1.2"         ---          1.2        true        new String("1.2")
 * "one"         ---          NaN        true        new String("one")
 * ---------------------------------------------------------------------
 * 0             "0"          ---        false       new Number(0)
 * -0            "0"          ---        false       new Number(-0)
 * NaN           "NaN"        ---        false       new Number("NaN")
 * Infinity      "Infinity"   ---        true        new Number("Infinity")
 * -Infinity     "-Infinity"  ---        true        new Number("-Infinity")
 * 1             "1"          ---        true        new Number(1)
 * ---------------------------------------------------------------------
 * Object        *1           *2         true        ---
 * []            ""           0          true        ---
 * [9]           "9"          9          true        ---
 * ['a']         use join()   NaN        true        ---
 * Function      *1           NaN        true        ---
 * ---------------------------------------------------------------------
 *
 * *1: object o -> string
 *
 *    if (o has toString() method) {
 *      v = o.toString();
 *      if (v is a primitive value, i.e., either boolean, number, or string)
 *        return convert_to_string(v);
 *    }
 *    // o does not have toString or toString does not return a basic value
 *    if (o has valueOf() method) {
 *      v = o.valueOf():
 *      if (v is a primitive value, i.e., either boolean, number, or string)
 *        return convert_to_string(v);
 *    }
 *    throws TypeError exception
 *
 * *2: object o -> number
 *
 *    if (o has valueOf() method) {
 *      v = o.valueOf():
 *      if (v is a basic value, i.e., either boolean, number, or string)
 *        return convert_to_number(v);
 *    }
 *    // o does not have valueOf or valueOf does not retuen a basic value
 *    if (o has toString() method) {
 *      v = o.toString();
 *      if (v is a basic value, i.e., either boolean, number, or string)
 *        return convert_to_number(v);
 *    }
 *    throws TypeError exception
 *
 */

/*
 * JSValue to JSValue conversion functions
 */

#ifdef USE_VMDL

/*
 * converts a special value to a string
 */
#include "funcs/special_to_string.inc"

/*
 * convers a special value to a number
 */
#include "funcs/special_to_number.inc"

/*
 * convers a special value to a boolean
 */
#include "funcs/special_to_boolean.inc"

/*
 * converts a special value to an object
 */
#include "funcs/special_to_object.inc"

/*
 * convers a string to a number
 */
#include "funcs/string_to_number.inc"

/*
 * converts a string to a boolean
 */
#include "funcs/string_to_boolean.inc"

/*
 * converts a string to an Object
 */
#include "funcs/string_to_object.inc"

#define BUFSIZE 1000
static char buf[BUFSIZE];

/*
 * converts a fixnum to a string
 */
#include "funcs/fixnum_to_string.inc"

/*
 * convers a flonum to a string
 */
#include "funcs/flonum_to_string.inc"

JSValue double_to_string(double d) {
  snprintf(buf, BUFSIZE, "%.15g", d);
  return cstr_to_string(NULL, buf);
}

/*
 * converts a number to a string
 */
#include "funcs/number_to_string.inc"

/*
 * converts a fixnum to a boolean
 */
#include "funcs/fixnum_to_boolean.inc"

/*
 * converts a flonum to a boolean
 */
#include "funcs/flonum_to_boolean.inc"

/*
 * converts a fixnum to an object
 */
#include "funcs/fixnum_to_object.inc"

/*
 * converts a flonum to an object
 */
#include "funcs/flonum_to_object.inc"

/*
 * converts an object to a string
 */
#include "funcs/object_to_string.inc"

/*
 * converts an object to a number
 */
#include "funcs/object_to_number.inc"

  /* not completed yet */
  /*
   * if (is_array(v)) {
   *   if (array_size(v) == 0)    // empty array
   *     return FIXNUM_ZERO;
   *   if (array_size(v) == 1) {
   *     v = array_body_index(v, 0);
   *     if (is_number(v)) return v;
   *   }
   * }
   * return gconsts.g_flonum_nan;
   */

/*
 * converts an object to a primitive
 *
 * The third argument specifies the order of applying toString and valueOf.
 * The difference between this function and convert_to_string /
 * convert_to_number is that when toString / valueOf returned a
 * primitive value, this function returns it without converting
 * them into a string / number.
 */
#include "funcs/object_to_primitive.inc"

/*
 * converts an object to a boolean
 */
#include "funcs/object_to_boolean.inc"

#else /* USE_VMDL */

/*
 * converts a special value to a string
 */
JSValue special_to_string(JSValue v) {
  assert(is_special(v));
  switch (v) {
  case JS_UNDEFINED:
    return gconsts.g_string_undefined;
  case JS_NULL:
    return gconsts.g_string_null;
  case JS_TRUE:
    return gconsts.g_string_true;
#ifndef DEBUG
  default:
    return gconsts.g_string_false;
#else /* DEBUG */
  case JS_FALSE:
    return gconsts.g_string_false;
  default:
  type_error("special expected in special_to_string");
    return gconsts.g_string_empty;
#endif /* DEBUG */
  }
}

/*
 * convers a special value to a number
 */
JSValue special_to_number(JSValue v) {
  assert(is_special(v));
  switch (v) {
  case JS_UNDEFINED:
    return gconsts.g_flonum_nan;
  case JS_NULL:
  case JS_FALSE:
    return FIXNUM_ZERO;
#ifndef DEBUG
  default:
    return FIXNUM_ONE;
#else /* DEBUG */
  case JS_TRUE:
    return FIXNUM_ONE;
  default:
    type_error("special expected in special_to_number");
    return gconsts.g_flonum_nan;
#endif /* DEBUG */
  }
}

/*
 * convers a special value to a boolean
 */
JSValue special_to_boolean(JSValue v) {
  assert(is_special(v));
  switch (v) {
  case JS_UNDEFINED:
  case JS_NULL:
    return JS_FALSE;
#ifndef DEBUG
  default:
    return v;
#else /* DEBUG */
  case JS_TRUE:
  case JS_FALSE:
    return v;
  default:
    type_error("special expected in special_to_boolean");
    return JS_FALSE;
#endif /* DEBUG */
  }
}

/*
 * converts a special value to an object
 */
JSValue special_to_object(Context *ctx, JSValue v) {
  assert(is_special(v));
  switch (v) {
  case JS_UNDEFINED:
    type_error_exception("trying to convert undefined to an object");
    return JS_UNDEFINED;
  case JS_NULL:
    type_error_exception("trying to convert null to an object");
    return JS_UNDEFINED;
#ifndef DEBUG
  default:
    return new_boolean_object(ctx, DEBUG_NAME("special_to_object"),
                              gshapes.g_shape_Boolean, v);
#else /* DEBUG */
  case JS_TRUE:
  case JS_FALSE:
    return new_boolean_object(ctx, DEBUG_NAME("special_to_object"),
                              gshapes.g_shape_Boolean, v);
  default:
    type_error("special expected in special_to_object");
    return JS_UNDEFINED;
#endif /* DEBUG */

  }
}

/*
 * convers a string to a number
 */
JSValue string_to_number(Context *ctx, JSValue v) {
  char *p, *q;
  cint n;
  double d;

  assert(is_string(v));
  p = string_value(v);
  if (p[0] == '\0')    /* empty string */
    return FIXNUM_ZERO;

  /* try to read an integer from the string */
  n = strtol(p, &q, 10);
  if (p != q) {
    if (*q == '\0')
      return cint_to_number(ctx, n);
  }
  d = strtod(p, &q);
  if (p != q) {
    if (*q == '\0')
      return double_to_flonum(ctx, d); /* TODO: context */
  }
  return gconsts.g_flonum_nan;
}

/*
 * converts a string to a boolean
 */
JSValue string_to_boolean(JSValue v) {
  char *p;

  assert(is_string(v));
  p = string_value(v);
  return false_true(p[0] == '\0');
}

/*
 * converts a string to an Object
 */
JSValue string_to_object(Context *ctx, JSValue v) {
  assert(is_string(v));
  return new_string_object(ctx, DEBUG_NAME("string_to_object"),
                           gshapes.g_shape_String, v);
}

#define BUFSIZE 1000
static char buf[BUFSIZE];

/*
 * converts a fixnum to a string
 */
JSValue fixnum_to_string(JSValue v) {
  assert(is_fixnum(v));
  return cint_to_string(fixnum_to_cint(v));
}

/*
 * convers a flonum to a string
 */
JSValue flonum_to_string(JSValue v) {
  double d;
  char buf[BUFSIZE];

  assert(is_flonum(v));
  d = flonum_to_double(v);
  if (d == 0.0)
    return cstr_to_string(NULL, "0");
  if (isnan(d))
    return cstr_to_string(NULL, "NaN");
  if (isinf(d)) {
    if (d > 0) return cstr_to_string(NULL, "Infinity");
    else return cstr_to_string(NULL, "-Infinity");
  }
  snprintf(buf, BUFSIZE, "%.15g", d);
  return cstr_to_string(NULL, buf);
}

/*
 * converts a number to a string
 */
JSValue number_to_string(JSValue v) {
  assert(is_number(v));
  if (is_fixnum(v)) return fixnum_to_string(v);
  return flonum_to_string(v);
}

/*
 * converts a fixnum to a boolean
 */
JSValue fixnum_to_boolean(JSValue v) {
  assert(is_fixnum(v));
  return false_true(v == FIXNUM_ZERO);
}

/*
 * converts a flonum to a boolean
 */
JSValue flonum_to_boolean(JSValue v) {
  double d;

  assert(is_flonum(v));
  d = flonum_to_double(v);
  return false_true(isnan(d));
}

/*
 * converts a fixnum to an object
 */
JSValue fixnum_to_object(Context *ctx, JSValue v) {
  assert(is_fixnum(v));
  return new_number_object(ctx, DEBUG_NAME("fixnum_to_object"),
                           gshapes.g_shape_Number, v);
}

/*
 * converts a flonum to an object
 */
JSValue flonum_to_object(Context *ctx, JSValue v) {
  assert(is_flonum(v));
  return new_number_object(ctx, DEBUG_NAME("flonum_to_object"),
                           gshapes.g_shape_Number, v);
}

/*
 * converts an object to a string
 */
JSValue object_to_string(Context *context, JSValue v) {
  JSValue f;

  assert(is_object(v));
  if ((f = get_prop_prototype_chain(v, gconsts.g_string_tostring))
      != JS_UNDEFINED) {
    GC_PUSH(v);
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else {
      GC_POP(v);
      goto NEXT0;
    }
    GC_POP(v);
    if (is_string(f)) return f;
    if (is_fixnum(f)) return fixnum_to_string(f);
    if (is_flonum(f)) return flonum_to_string(f);
    if (is_boolean(f)) return special_to_string(f);
  }
 NEXT0:
  if ((f = get_prop_prototype_chain(v, gconsts.g_string_valueof))
      != JS_UNDEFINED) {
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else goto NEXT1;
    if (is_string(f)) return f;
    if (is_fixnum(f)) return fixnum_to_string(f);
    if (is_flonum(f)) return flonum_to_string(f);
    if (is_boolean(f)) return special_to_string(f);
  }
 NEXT1:
  type_error_exception("neither toString nor valueOf returned a string in object_to_string");
  return gconsts.g_string_undefined;     /* not reached */
}

/*
 * converts an object to a number
 */
JSValue object_to_number(Context *context, JSValue v) {
  JSValue f = JS_NULL;

  assert(is_object(v));
  if ((f = get_prop_prototype_chain(v, gconsts.g_string_valueof)) != JS_EMPTY) {
    GC_PUSH(v);
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else {
      GC_POP(v);
      goto NEXT0;
    }
    GC_POP(v);
    if (is_number(f)) return f;
    if (is_string(f)) return string_to_number(context, f);
    if (is_boolean(f)) return special_to_number(f);
  }
 NEXT0:
  if ((f = get_prop_prototype_chain(v, gconsts.g_string_tostring)) != JS_EMPTY) {
    GC_PUSH(v);
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else {
      GC_POP(v);
      goto NEXT1;
    }
    GC_POP(v);
    if (is_number(f)) return f;
    if (is_string(f)) return string_to_number(context, f);
    if (is_boolean(f)) return special_to_number(f);
  }
 NEXT1:
  GC_PUSH(f);
  print_value_simple(context, v); putchar('\n');
  print_value_simple(context, f); putchar('\n');
  GC_POP(f);
  type_error_exception("neither valueOf nor toString returned a number in object_to_number");
  return FIXNUM_ZERO;       /* not reached */

  /* not completed yet */
  /*
   * if (is_array(v)) {
   *   if (array_size(v) == 0)    // empty array
   *     return FIXNUM_ZERO;
   *   if (array_size(v) == 1) {
   *     v = array_body_index(v, 0);
   *     if (is_number(v)) return v;
   *   }
   * }
   * return gconsts.g_flonum_nan;
   */
}

/*
 * converts an object to a primitive
 *
 * The third argument specifies the order of applying toString and valueOf.
 * The difference between this function and convert_to_string /
 * convert_to_number is that when toString / valueOf returned a
 * primitive value, this function returns it without converting
 * them into a string / number.
 */
JSValue object_to_primitive(Context *context, JSValue v, int hint) {
  JSValue f, fst, snd;

  assert(is_object(v));
  if (hint == HINT_STRING) {
    fst = gconsts.g_string_tostring;
    snd = gconsts.g_string_valueof;
  } else {                               /* hint == HINT_NUMBER */
    fst = gconsts.g_string_valueof;
    snd = gconsts.g_string_tostring;
  }
  if ((f = get_prop_prototype_chain(v, fst)) != JS_UNDEFINED) {
    GC_PUSH2(v, snd);
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else {
      GC_POP2(snd, v);
      goto NEXT0;
    }
    GC_POP2(snd, v);
    if (is_primitive(f)) return f;
  }
 NEXT0:
  if ((f = get_prop_prototype_chain(v, snd)) != JS_UNDEFINED) {
    if (is_function(f)) f = invoke_function0(context, v, f, TRUE);
    else if (is_builtin(f)) f = invoke_builtin0(context, v, f, TRUE);
    else goto NEXT1;
    if (is_primitive(f)) return f;
  }
 NEXT1:
  type_error_exception("neither toString nor valueOf returned a string in object_to_primitive");
  return JS_UNDEFINED;     /* not reached */
}

/*
 * converts an object to a boolean
 */
JSValue object_to_boolean(JSValue v) {
  assert(is_object(v));
  return JS_TRUE;
}

#endif /* USE_VMDL */

/*
 * converts an array to a string
 */
JSValue array_to_string(Context *context, JSValue array, JSValue separator)
{
  cint length;
  uint64_t seplen, sumlen;
  JSValue ret, item;
  JSValue *strs;
  char *sep, *cstr, *p;
  int i;

  assert(is_array(array));
  ret = gconsts.g_string_empty;
  length = number_to_cint(get_jsarray_length(array));
  if (length <= 0)
    return ret;

  /* length > 0 */
  strs = (JSValue *)malloc(sizeof(JSValue) * length);
  if (strs == NULL)
    LOG_EXIT("Out of memory\n");
  sep = string_to_cstr(separator);
  seplen = strlen(sep);
  sumlen = 0;

  for (i = 0; i < length; i++) {
    GC_PUSH(array);
    item = get_array_element(context, array, i);
    strs[i] = to_string(context, item);
    GC_POP(array);
    sumlen += string_length(strs[i]);
  }

  cstr = (char *)malloc(sizeof(char) * (sumlen + (length - 1) * seplen + 1));
  if (cstr == NULL)
    LOG_EXIT("Out of memory\n");

  for (i = 0, p = cstr; i < length; i++) {
    strcpy(p, string_value(strs[i]));
    p += string_length(strs[i]);
    if (i != length - 1) {
      strcpy(p, sep);
      p += seplen;
    }
  }
  *p = '\0';

  ret = cstr_to_string(context, cstr);

  free(cstr);
  free(strs);

  return ret;
}

/*
 * general functions
 */

#ifdef USE_VMDL
/*
 * converts to a string
 */
#include "funcs/to_string.inc"

/*
 * converts to a boolean
 */
#include "funcs/to_boolean.inc"

/*
 * converts to a number
 */
#include "funcs/to_number.inc"

/*
 * converts to an object
 */
#include "funcs/to_object.inc"
/*
 * conversion functions to C's data
 */
#include "funcs/special_to_double.inc"

/*
 * converts to a C's double
 */
#include "funcs/to_double.inc"

#include "funcs/number_to_cint.inc"

#include "funcs/number_to_double.inc"

#include "funcs/to_cint.inc"

#include "funcs/toInteger.inc"

#else /* USE_VMDL */

/*
 * converts to a string
 */
JSValue to_string(Context *context, JSValue v) {
  if (is_string(v)) return v;
  if (is_fixnum(v)) return fixnum_to_string(v);
  if (is_flonum(v)) return flonum_to_string(v);
  if (is_special(v)) return special_to_string(v);
  if (is_array(v)) return array_to_string(context, v, gconsts.g_string_comma);
#ifndef DEBUG
  return object_to_string(context, v);
#else /* DEBUG */
  if (is_object(v)) return object_to_string(context, v);
  LOG_ERR("This cannot happen in to_string");
  return gconsts.g_string_undefined;
#endif /* DEBUG */
}

/*
 * converts to a boolean
 */
JSValue to_boolean(JSValue v) {
  if (is_string(v)) return string_to_boolean(v);
  if (is_fixnum(v)) return fixnum_to_boolean(v);
  if (is_flonum(v)) return flonum_to_boolean(v);
  if (is_special(v)) return special_to_boolean(v);
#ifndef DEBUG
  return object_to_boolean(v);
#else /* DEBUG */
  if (is_object(v)) return object_to_boolean(v);
  LOG_ERR("This cannot happen in to_boolean");
  return JS_FALSE;
#endif /* DEBUG */
}

/*
 * converts to a number
 */
JSValue to_number(Context *context, JSValue v) {
  if (is_number(v)) return v;
  if (is_string(v)) return string_to_number(context, v);
  if (is_special(v)) return special_to_number(v);
#ifndef DEBUG
  return object_to_number(context, v);
#else /* DEBUG */
  if (is_object(v)) return object_to_number(context, v);
  LOG_ERR("This cannot happen in to_number");
  return gconsts.g_flonum_nan;
#endif /* DEBUG */
}

/*
 * converts to an object
 */
JSValue to_object(Context *ctx, JSValue v) {
  if (is_string(v)) return string_to_object(ctx, v);
  if (is_fixnum(v)) return fixnum_to_object(ctx, v);
  if (is_flonum(v)) return flonum_to_object(ctx, v);
  if (is_special(v)) return special_to_object(ctx, v);
#ifndef DEBUG
  return v;
#else /* DEBUG */
  if (is_object(v)) return v;
  LOG_ERR("This cannot happen in to_object");
  return JS_UNDEFINED;
#endif /* DEBUG */
}

/*
 * conversion functions to C's data
 */
double special_to_double(JSValue x) {
  assert(is_special(x));
  switch (x) {
  case JS_TRUE:
    return 1.0;
  case JS_FALSE:
  case JS_NULL:
    return 0.0;
  case JS_UNDEFINED:
  default:
    return NAN;
  }
}

/*
 * converts to a C's double
 */
double to_double(Context *context, JSValue v) {
  if (is_fixnum(v))
    return fixnum_to_double(v);
  else if (is_flonum(v))
    return flonum_to_double(v);
  else if (is_string(v)) {
    char *p, *q;
    int n;
    double d;

    p = string_value(v);
    if (p[0] == '\0') return (double)0.0;
    n = strtol(p, &q, 10);
    if (p != q && *q == '\0') return (double)n;  /* succeeded */
    d = strtod(p, &q);
    if (p != q && *q == '\0') return d;
    return NAN;
  } else if (is_special(v))
    return special_to_double(v);
#ifndef DEBUG
  else {
    JSValue w;

    w = object_to_number(context, v);
    if (is_fixnum(w)) return fixnum_to_double(w);
    return flonum_to_double(w);
  }
#else /* DEBUG */
  else if (is_object(v)) {
    JSValue w;

    w = object_to_number(context, v);
    if (is_fixnum(w)) return fixnum_to_double(w);
    if (is_flonum(w)) return flonum_to_double(w);
  }
  return NAN;                 /* not reached */
#endif /* DEBUG */
}

cint number_to_cint(JSValue n)
{
  assert(is_number(n));
  if (is_fixnum(n))
    return fixnum_to_cint(n);
  else
    return (cint) flonum_to_double(n);
}

/* used in builtin methods */
cint toInteger(Context *context, JSValue a) {
  cint n;

  if (is_fixnum(a)) n = fixnum_to_cint(a);
  else if (is_nan(a)) n = 0;
  else if (is_flonum(a)) n = flonum_to_int(a);
  else {
    a = to_number(context, a);
    if (is_fixnum(a)) n = fixnum_to_cint(a);
    else if (is_nan(a)) n = 0;
    else if (is_flonum(a)) n = flonum_to_int(a);
    else {
      /* printf("cannot convert to a integer\n"); */
      n = 0;
    }
  }
  return n;
}

#endif /* USE_VMDL */

const char *type_name(JSValue v) {
  if (is_string(v)) return "String";
  if (is_fixnum(v)) return "Fixnum";
  if (is_flonum(v)) return "Flonum";
  if (is_special(v)) return "Special";
  if (is_array(v)) return "Array";
  if (is_function(v)) return "Function";
  if (is_builtin(v)) return "Builtin";
  if (is_iterator(v)) return "Iterator";
  if (is_number_object(v)) return "NumberObject";
  if (is_boolean_object(v)) return "BooleanObject";
  if (is_string_object(v)) return "StringObject";
#ifdef USE_REGEXP
  if (is_regexp(v)) return "Regexp";
#endif
  if (is_simple_object(v)) return "SimpleObject";
  /*  if (is_object(v)) return "Object";   could it happen? */
  return "???";
}

JSValue cint_to_string(cint n) {
  snprintf(buf, BUFSIZE, "%lld", (long long) n);
  return cstr_to_string(NULL, buf);
}


/*
 * converts a special JS string (for a constant) into a JSValue
 */
JSValue specstr_to_jsvalue(const char *str) {
  if (strcmp(str, "true") == 0)
    return JS_TRUE;
  else if (strcmp(str, "false") == 0)
    return JS_FALSE;
  else if (strcmp(str, "null") == 0)
    return JS_NULL;
  else if (strcmp(str, "undefined") == 0)
    return JS_UNDEFINED;
  else
    /* undefined name */
    LOG_EXIT("%s is an undefined symbol.", str);
}

const char *jsvalue_to_specstr(JSValue v) {
  const char *s;
  if (v == JS_TRUE) s = "true";
  else if (v == JS_FALSE) s = "false";
  else if (v == JS_NULL) s = "null";
  else if (v == JS_UNDEFINED) s = "undefined";
  else s = "unknown_specstr";
  return s;
}

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
