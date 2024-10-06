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
#include <limits.h>

#ifdef USE_VMDL
#include "vmdl-extern.h"
#endif /* USE_VMDL */


#define not_implemented(s)                                              \
  LOG_EXIT("%s is not implemented yet\n", (s)); set_a(context, JS_UNDEFINED)

#define type_error_exception(s)  LOG_EXIT("%s\n", s)

#define mallocstr(n) ((char *)malloc(sizeof(char) * ((n) + 1)))

struct split_match_rettype{cint r0;/* endindex. -1 when state is failure */ JSValue r1; /* captures */};

static inline struct split_match_rettype split_match(Context *context, JSValue s, cint q, JSValue r){
  JSValue cap;
  cint sr, ss, i;
  struct split_match_rettype state;
  /* 1. */
  if(is_regexp(r)){
    /* TODO: Implement the case where the separator is of type regexp */
    not_implemented("split_match");
  }
  /* 2. */
  assert(is_string(r));
  sr = string_length(r);
  /* 3. */
  ss = string_length(s);
  /* 4. */
  if(q + sr > ss){
    state.r0 = -1;
    return state;
  }
  /* 5. */
  for(i=0; i<sr; i++){
    if(string_char_code_at(s, q + i) != string_char_code_at(r, i)){
      state.r0 = -1;
      return state;
    }
  }
  /* 6. */
  cap = new_array_object(context, DEBUG_NAME("split_match"), gshapes.g_shape_Array, 0);
  /* 7. */
  state.r0 = q + sr;
  state.r1 = cap;
  return state;
}

/*
 *  Step 1. - 3. of
 *   15.5.4.16 String.prototype.toLowerCase        (upper = FALSE)
 *   15.5.4.17 String.prototype.toLocaleLowerCase  (upper = FALSE)
 *   15.5.4.18 String.prototype.toUpperCase        (upper = TRUE)
 *   15.5.4.19 String.prototype.toLocaleUpperCase  (upper = TRUE)
 */
static JSValue to_upper_lower(Context *ctx, JSValue str, int upper)
{
  /* 1. check coercible */
  if (str == JS_NULL || str == JS_UNDEFINED)
    type_error_exception("to_upper_lower");

  /* 2. */
  str = to_string(ctx, str);

  /* 3. */
  return string_to_upper_lower_case(ctx, str, upper);
}

/*
 * Note that "abcdefg".lastIndexOf("efg", 4) must return not -1 but 4
 * and "abcdefg".indexOf("",4);
 */
JSValue string_indexOf_(Context *context, JSValue *args, int na,
                        int isLastIndexOf) {
  JSValue s0, s1;
  char *s, *searchStr;
  cint pos, len, start, searchLen, k, j;
  int delta;

  s0 = is_string(args[0]) ? args[0] : to_string(context, args[0]);
  GC_PUSH(s0);
  s1 = is_string(args[1]) ? args[1] : to_string(context, args[1]);
  s = string_to_cstr(s0);
  searchStr = string_to_cstr(s1);
  len = string_length(s0);
  GC_POP(s0);
  searchLen = string_length(s1);

  if (na >= 2 && !is_undefined(args[2])) pos = toInteger(context, args[2]);
  else if (isLastIndexOf) pos = INT_MAX;
  else pos = 0;
  start = min(max(pos, 0), len);
  if (searchLen == 0)
    return cint_to_number(context, start);

  if (isLastIndexOf) delta = -1;
  else delta = 1;
  k = min(start, len - searchLen);
  while (0 <= k && k <= len - searchLen) {
    for (j = 0; s[k+j] == searchStr[j]; j++)
      if (j == (searchLen - 1)) return cint_to_number(context, k);
    k += delta;
  }

  return FIXNUM_MINUS_ONE;
}

#ifdef USE_VMDL

#include "builtins/string_constr_nonew.inc"

#include "builtins/string_substring.inc"

#include "builtins/string_slice.inc"

#include "builtins/string_charAt.inc"

#include "builtins/string_charCodeAt.inc"

#include "builtins/string_fromCharCode.inc"

#include "builtins/string_localeCompare.inc"

#include "builtins/string_constr.inc"

#include "builtins/string_valueOf.inc"

#include "builtins/string_concat.inc"

#include "builtins/string_toLowerCase.inc"

#include "builtins/string_toUpperCase.inc"

#include "builtins/string_indexOf.inc"

#include "builtins/string_lastIndexOf.inc"

#include "builtins/string_split.inc"

#include "builtins/string_trim.inc"

#else /* USE_VMDL */

/*
 * constrcutor of a string (not Object)
 */
BUILTIN_FUNCTION(string_constr_nonew)
{
  JSValue arg;
  
  builtin_prologue();
  if (na > 0)
    arg = to_string(context, args[1]);
  else
    arg = gconsts.g_string_empty;
  set_a(context, arg);
}

/*
 *  15.5.4.15 String.prototype.substring
 */
BUILTIN_FUNCTION(string_substring)
{
  JSValue str, ret;
  cint len, intStart, intEnd;
  cint finalStart, finalEnd, from, to;

  builtin_prologue();

  /* 1. check coercible */
  if (args[0] == JS_NULL || args[0] == JS_UNDEFINED)
    type_error_exception("string_substring");

  /* 2. */
  str = to_string(context, args[0]);
  GC_PUSH(str);

  /* 3. */
  len = string_length(str);

  /* 4. */
  intStart = na >= 1 ? toInteger(context, args[1]) : 0;

  /* 5. */
  intEnd =
    (na >= 2 && args[2] != JS_UNDEFINED) ? toInteger(context, args[2]) : len;

  /* 6. */
  finalStart = min(max(intStart, 0), len);

  /* 7. */
  finalEnd = min(max(intEnd, 0), len);

  /* 8. */
  from = min(finalStart, finalEnd);

  /* 9. */
  to = max(finalStart, finalEnd);

  /* 10. */
  ret = string_make_substring(context, str, from, to - from);
  set_a(context, ret);
  GC_POP(str);
}

/*
 *  15.5.4.13 String.prototype.slice
 */
BUILTIN_FUNCTION(string_slice)
{
  JSValue str, ret;
  cint len, intStart, intEnd;
  cint from, to, span;

  builtin_prologue();

  /* 1. check coercible */
  if (args[0] == JS_NULL || args[0] == JS_UNDEFINED)
    type_error_exception("string_slice");

  /* 2. */
  str = to_string(context, args[0]);
  GC_PUSH(str);

  /* 3. */
  len = string_length(str);

  /* 4. */
  intStart = na >= 1 ? toInteger(context, args[1]) : 0;

  /* 5. */
  intEnd =
    (na >= 2 && args[2] != JS_UNDEFINED) ? toInteger(context, args[2]) : len;

  /* 6. */
  from = intStart < 0 ? max(len + intStart, 0) : min(intStart, len);

  /* 7. */
  to = intEnd < 0 ? max(len + intEnd, 0) : min(intEnd, len);

  /* 8. */
  span = max(to - from, 0);

  /* 9. */
  ret = string_make_substring(context, str, from, span);
  set_a(context, ret);
  GC_POP(str);
}

/*
 *  15.5.4.4 String.prototype.charAt
 */
BUILTIN_FUNCTION(string_charAt)
{
  JSValue str, ret;
  cint pos, c;
  builtin_prologue();

  /* 1. check coercible */
  if (args[0] == JS_NULL || args[0] == JS_UNDEFINED)
    type_error_exception("string_charAt");

  /* 2. */
  str = to_string(context, args[0]);
  GC_PUSH(str);

  /* 3. */
  pos = na >= 1 ? toInteger(context, args[1]) : 0;

  /* 4. 5. */
  if (pos < 0 || string_length(str) <= ((uint32_t) pos))
    ret = gconsts.g_string_empty;
  else {
    /* 6. */
    c = string_char_code_at(str, pos);
    if (c < 0)
      ret = gconsts.g_string_blank;
    else {
      char s[2] = {c, '\0'};
      ret = cstr_to_string(context, s);
    }
  }

  set_a(context, ret);
  GC_POP(str);
}

/*
 *  15.5.4.5 String.prototype.charCodeAt
 */
BUILTIN_FUNCTION(string_charCodeAt)
{
  JSValue str, ret;
  cint pos, c;
  builtin_prologue();

  /* 1. check coercible */
  if (args[0] == JS_NULL || args[0] == JS_UNDEFINED)
    type_error_exception("string_charCodeAt");

  /* 2. */
  str = to_string(context, args[0]);
  GC_PUSH(str);

  /* 3. */
  pos = na >= 1 ? toInteger(context, args[1]) : 0;

  /* 4. 5. */
  if (pos < 0 || string_length(str) <= ((uint32_t) pos))
    ret = gconsts.g_flonum_nan;
  else {
    /* 6. */
    c = string_char_code_at(str, pos);
    if (c < 0)
      ret = gconsts.g_flonum_nan;
    else
      ret = cint_to_number(context, c);
  }

  set_a(context, ret);
  GC_POP(str);
}

BUILTIN_FUNCTION(string_fromCharCode)
{
  JSValue a, ret;
  char *s;
  cint c;
  int i;

  builtin_prologue();
  s = (char *)malloc(sizeof(char) * (na + 1));
  for (i = 1; i <= na; i++) {
    a = args[i];
    if (is_fixnum(a)) c = fixnum_to_cint(a);
    else if (is_flonum(a)) c = flonum_to_int(a);
    else {
      a = to_number(context, a);
      if (is_fixnum(a)) c = fixnum_to_cint(a);
      else if (is_flonum(a)) c = flonum_to_int(a);
      else {
        printf("fromCharCode: cannot convert to a number\n");
        c = ' ';
      }
    }
    s[i - 1] = c;
  }
  s[na] = '\0';
  ret = cstr_to_string(context, s);
  free(s);
  set_a(context, ret);
}


BUILTIN_FUNCTION(string_localeCompare)
{
  JSValue s0, s1, ret;
  char *cs0, *cs1;
  int r;

  builtin_prologue();
  s0 = to_string(context, args[0]);
  GC_PUSH(s0);
  if (na >= 1) s1 = to_string(context, args[1]);
  else s1 = to_string(context, JS_UNDEFINED);
  cs0 = string_to_cstr(s0);
  GC_POP(s0);
  cs1 = string_to_cstr(s1);

  r = strcmp(cs0, cs1); /* implemantation-defined */
  if (r > 0) ret = FIXNUM_ONE;
  else if (r < 0) ret = FIXNUM_MINUS_ONE;
  else ret = FIXNUM_ZERO;

  set_a(context, ret);
  return;
}

/*
 * constrcutor of a string
 */
BUILTIN_FUNCTION(string_constr)
{
  JSValue rsv;

  builtin_prologue();
  rsv =
    new_string_object(context, DEBUG_NAME("string_constr"),
                      gshapes.g_shape_String,
                      na > 0? args[1]: gconsts.g_string_empty);
  set_a(context, rsv);
}

BUILTIN_FUNCTION(string_valueOf)
{
  JSValue arg;

  builtin_prologue();  
  arg = args[0];
  if (is_string_object(arg))
    arg = get_jsstring_object_value(arg);
  else if (!is_string(arg))
    arg = JS_UNDEFINED;
  set_a(context, arg);
}

/*
 * 15.5.4.6 String.prototype.concat
 */

BUILTIN_FUNCTION(string_concat)
{
  JSValue retval;
  int i;

  builtin_prologue();

  /* 1. check coercible */
  if (args[0] == JS_NULL || args[0] == JS_UNDEFINED)
    type_error_exception("string_concat");

  /* 2. */
  retval = to_string(context, args[0]);

  /* 5. */
  for (i = 1; i <= na; i++) {
    JSValue append_str = to_string(context, args[i]);
    retval = ejs_string_concat(context, retval, append_str);
  }

  /* 6. */
  set_a(context, retval);
}

/*
 *  15.5.4.16 String.prototype.toLowerCase
 */
BUILTIN_FUNCTION(string_toLowerCase)
{
  JSValue ret;

  builtin_prologue();
  /* 1. - 3. */
  ret = to_upper_lower(context, args[0], FALSE);
  /* 4. */
  set_a(context, ret);
}

/*
 *  15.5.4.18 String.prototype.toUpperCase
 */
BUILTIN_FUNCTION(string_toUpperCase)
{
  JSValue ret;

  builtin_prologue();
  /* 1. - 3. */
  ret = to_upper_lower(context, args[0], TRUE);
  /* 4. */
  set_a(context, ret);
}

BUILTIN_FUNCTION(string_indexOf)
{
  JSValue ret;
  builtin_prologue();
  ret = string_indexOf_(context, args, na, FALSE);
  set_a(context, ret);
  return;
}

BUILTIN_FUNCTION(string_lastIndexOf)
{
  JSValue ret;
  builtin_prologue();
  ret = string_indexOf_(context, args, na, TRUE);
  set_a(context, ret);
  return;
}


BUILTIN_FUNCTION(string_split)
{
  JSValue o, s, a, r, cap, t;
  cint length_a, lim, ss, p, q, e, i;
  struct split_match_rettype z;

  builtin_prologue();
  /* 1. */
  o = args[0];
  if (o == JS_NULL || o == JS_UNDEFINED)
    type_error_exception("string_split");
  GC_PUSH(o);
  /* 2. */
  s = to_string(context, o);
  GC_PUSH(s);
  /* 3. */
  a = new_array_object(context, DEBUG_NAME("string_split"), gshapes.g_shape_Array, 0);
  GC_PUSH(a);
  /* 4. */
  length_a = 0;
  /* 5. */
  lim = args[2] == JS_UNDEFINED ? (cint)((((uint64_t) 1) << 32) - 1) : toInteger(context, args[2]);
  /* 6. */
  ss = string_length(s);

  /* 7. */
  p = 0;
  /* 8. */
  if(is_regexp(args[1])){
    /* TODO: Implement the case where the args[1] (separator) is of type regexp */
    not_implemented("string_split");
  }
  r = to_string(context, args[1]);
  GC_PUSH(r);
  /* 9. */
  if(lim == 0){
    GC_POP4(r, a, s, o);
    set_a(context, a);
    return;
  }
  /* 10. */
  if(args[1] == JS_UNDEFINED){
    /* a. */
    set_array_element(context, a, 0, s);
    /* b. */
    GC_POP4(r, a, s, o);
    set_a(context, a);
    return;
  }
  /* 11. */
  if(ss == 0){
    /* a. */
    z = split_match(context, s, 0, r);
    /* b. */
    if(z.r0 != -1){
      GC_POP4(r, a, s, o);
      set_a(context, a);
      return;
    }
    /* c. */
    set_array_element(context, a, 0, s);
    /* d. */
    GC_POP4(r, a, s, o);
    set_a(context, a);
    return;
  }
  /* 12. */
  q = p;
  /* 13. */
  while(q != ss){
    /* a. */
    z = split_match(context, s, q, r);
    if(z.r0 == -1){
      /* b. */
      q = q + 1;
    }else{
      /* c. */
      /* i. */
      e = z.r0;
      cap = z.r1;
      GC_PUSH(cap);
      if(e == p){
        /* ii. */
        q = q + 1;
      }else{
        /* iii. */
        /* 1. */
        t = string_make_substring(context, s, p, q - p);
        GC_PUSH(t);
        /* 2. */
        set_array_element(context, a, length_a, t);
        /* 3. */
        length_a++;
        /* 4. */
        if(length_a == lim){
          GC_POP6(t, cap, r, a, s, o);
          set_a(context, a);
          return;
        }
        /* 5. */
        p = e;
        /* 6. */
        i = 0;
        /* 7. */
        while(i != number_to_cint(get_jsarray_length(cap))){
          /* a. */
          i++;
          /* b. */
          set_array_element(context, a, length_a, get_array_element(context, cap, i));
          /* c. */
          length_a++;
          /* d. */
          if(length_a == lim){
            GC_POP6(t, cap, r, a, s, o);
            set_a(context, a);
            return;
          }
        }
        /* 8. */
        q = p;
        GC_POP(t);
      }
      GC_POP(cap);
    }
  }
  /* 14. */
  t = string_make_substring(context, s, p, ss - p);
  GC_PUSH(t);
  /* 15. */
  set_array_element(context, a, length_a, t);
  /* 16. */
  GC_POP5(t, r, a, s, o);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(string_trim)
{
  JSValue o, s, t;

  builtin_prologue();
  /* 1. */
  o = args[0];
  if (o == JS_NULL || o == JS_UNDEFINED)
    type_error_exception("string_trim");
  /* 2. */
  s = to_string(context, o);
  /* 3. */
  t = ejs_string_trim(context, s);
  /* 4. */
  set_a(context, t);
  return;
}

#endif /* USE_VMDL */

/*
 * property table
 */

/* prototype */
ObjBuiltinProp StringPrototype_builtin_props[] = {
#ifndef ELIMINATED_STRING_VALUEOF
  { "valueOf",        string_valueOf,       0, ATTR_DE },
  { "toString",       string_valueOf,      0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_CONCAT
  { "concat",         string_concat,        0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_TOLOWERCASE
  { "toLowerCase",    string_toLowerCase,   0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_TOUPPERCASE
  { "toUpperCase",    string_toUpperCase,   0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_SUBSTRING
  { "substring",      string_substring,     2, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_SLICE
  { "slice",          string_slice,         2, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_CHARAT
  { "charAt",         string_charAt,        0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_CHARCODEAT
  { "charCodeAt",     string_charCodeAt,    0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_INDEXOF
  { "indexOf",        string_indexOf,       1, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_LASTINDEXOF
  { "lastIndexOf",    string_lastIndexOf,   1, ATTR_DE },
  #endif
#ifndef ELIMINATED_STRING_LOCALECOMPARE
  { "localeCompare",  string_localeCompare, 0, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_SPLIT
  { "split",          string_split,         2, ATTR_DE },
#endif
#ifndef ELIMINATED_STRING_TRIM
  { "trim",           string_trim,          0, ATTR_DE },
#endif
};
ObjDoubleProp  StringPrototype_double_props[] = {
  { "length", 0, ATTR_ALL, -1 },
};
ObjGconstsProp StringPrototype_gconsts_props[] = {};
/* constructor */
ObjBuiltinProp StringConstructor_builtin_props[] = {
#ifndef ELIMINATED_STRING_FROMCHARCODE
 { "fromCharCode",   string_fromCharCode,  0, ATTR_DE },
#endif
};
ObjDoubleProp  StringConstructor_double_props[] = {};
ObjGconstsProp StringConstructor_gconsts_props[] = {
  { "prototype", &gconsts.g_prototype_String, ATTR_ALL },
};
/* instance */
ObjBuiltinProp String_builtin_props[] = {};
ObjDoubleProp  String_double_props[] = {
  { "length", 0, ATTR_ALL, -1 },  /* placeholder */
};
ObjGconstsProp String_gconsts_props[] = {};
DEFINE_PROPERTY_TABLE_SIZES_PCI(String);

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
