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

#define type_error_exception(s)  LOG_EXIT("%s\n", s)

#define INSERTION_SORT_THRESHOLD (20) /* must >= 1 */
void asort(Context*, JSValue, cint, cint, JSValue);
void quickSort(Context*, JSValue, cint, cint, JSValue);
void insertionSort(Context*, JSValue, cint, cint, JSValue);
void swap(JSValue*, JSValue*);

static inline int eq_helper(Context *context, JSValue v1, JSValue v2) {
  if(is_flonum(v1) && is_flonum(v2)){
    double x1 = to_double(context, v1);
    double x2 = to_double(context, v2);
    return x1 == x2;
  }
  if (v1 == v2){
    return !is_nan(v1);
  }
  return 0;
}

#ifdef USE_VMDL

#include "builtins/array_constr.inc"

#include "builtins/array_toString.inc"

#include "builtins/array_join.inc"

#include "builtins/array_concat.inc"

#include "builtins/array_pop.inc"

#include "builtins/array_push.inc"

#include "builtins/array_reverse.inc"

#include "builtins/array_shift.inc"

#include "builtins/array_slice.inc"

#include "builtins/array_sort.inc"

#include "builtins/array_debugarray.inc"

#include "builtins/array_isArray.inc"

#include "builtins/array_splice.inc"

#include "builtins/array_unshift.inc"

#include "builtins/array_indexOf.inc"

#include "builtins/array_lastIndexOf.inc"

#include "builtins/array_every.inc"

#include "builtins/array_some.inc"

#include "builtins/array_forEach.inc"

#include "builtins/array_map.inc"

#include "builtins/array_filter.inc"

static inline JSValue reduce_helper(Context *context, cint k, cint len, JSValue o, JSValue accumulator, JSValue callbackfn, int direction){
  JSValue js_k, k_value;

  assert(direction == 1 || direction == -1);
  GC_PUSH3(o, accumulator, callbackfn);
  while((direction == 1 && k < len) || (direction == -1 && k >= 0)){
    if(has_array_element(o, k)){
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      if (is_function(callbackfn))
        accumulator = send_function4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
      else
        accumulator = send_builtin4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
    }
    /* d. */
    k += direction;
  }
  GC_POP3(callbackfn, accumulator, o);
  return accumulator;
}

#include "builtins/array_reduce.inc"

#include "builtins/array_reduceRight.inc"

#else /* USE_VMDL */

/*
 * constructor for array
 */
BUILTIN_FUNCTION(array_constr)
{
  JSValue rsv;
  cint size, length;

  builtin_prologue();

  /* compute sizes */
  if (na == 0)
    length = 0;
  else if (na == 1) {
    JSValue n = args[1];
    if (!is_fixnum(n) || (length = fixnum_to_cint(n)) < 0)
      length = 0;
  } else {
    /*
     * na >= 2, e.g., Array(2,4,5,1)
     * This means that the array's length is four whose elements are
     * 2, 4, 5, and 1.
     */
    length = na;
  }
  size = length;

  /* allocate the array */
#ifdef ALLOC_SITE_CACHE
  rsv = create_array_object(context, DEBUG_NAME("array_ctor"), size);
#else /* ALLOC_SITE_CACHE */
  rsv = new_array_object(context, DEBUG_NAME("array_ctor"),
                         gshapes.g_shape_Array, size);
#endif /* ALLOC_SITE_CACHE */
  GC_PUSH(rsv);
  set_jsarray_length(rsv, cint_to_number(context, length));
  GC_POP(rsv);

  /* fill elements if supplied */
  if (na >= 2) {
    int i;
    JSValue *body = get_jsarray_body(rsv);
    for (i = 0; i < length; i++)
      body[i] = args[i + 1];
  }
  /* set as the return value */
  set_a(context, rsv);
}

BUILTIN_FUNCTION(array_toString)
{
  JSValue ret;

  builtin_prologue();  
  ret = array_to_string(context, args[0], gconsts.g_string_comma);
  set_a(context, ret);
  return;
}

/*
 * joins the elements of an array by using a specified separator,
 * where default separator is ','
 */
BUILTIN_FUNCTION(array_join)
{
  JSValue sep, ret;

  builtin_prologue();
  if (is_undefined(args[1])) {
    sep = gconsts.g_string_comma;
  } else {
    sep = to_string(context, args[1]);
    if (!is_string(sep))
      sep = gconsts.g_string_comma;
  }
  ret = array_to_string(context, args[0], sep);
  set_a(context, ret);
  return;
}

BUILTIN_FUNCTION(array_concat)
{
  JSValue a, e, subElement;
  cint k, i, len;
  uintjsv_t n;

  builtin_prologue();
  a = new_array_object(context, DEBUG_NAME("array_concat"),
                       gshapes.g_shape_Array, 0);
  n = 0;
  GC_PUSH(a);
  for (i = 0; i <= na; i++) {
    e = args[i];
    if (is_array(e)) {
      k = 0;
      len = number_to_cint(get_jsarray_length(e));
      assert(len >= 0);
      if (n + ((uintjsv_t) len) > MAX_ARRAY_LENGTH)
        /* This should be improved */
        LOG_EXIT("New array length is more than VM limit (MAX_ARRAY_LENGTH)");
      while (k < len) {
        if (has_array_element(e, k)) {
          GC_PUSH(e);
          subElement = get_array_element(context, e, k);
          set_array_prop(context, a, cint_to_number(context, n), subElement);
          GC_POP(e);
        }
        n++;
        k++;
      }
    } else {
      if (n > MAX_ARRAY_LENGTH)
        /* This should be improved */
        LOG_EXIT("New array length is more than VM limit (MAX_ARRAY_LENGTH)");
      set_array_prop(context, a, cint_to_number(context, n), e);
      n++;
    }
  }
  /* is the two lines below necessary? */
  set_jsarray_length(a, n);
  set_prop_direct(context, a, gconsts.g_string_length,
                  cint_to_number(context, n), ATTR_NONE);
  GC_POP(a);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(array_pop)
{
  JSValue a, ret, flen;
  cint len;

  builtin_prologue();
  a = args[0];
  len = number_to_cint(get_jsarray_length(a)) - 1;    /* len >= -1 */
  if (len < 0) {
    set_a(context, JS_UNDEFINED);
    return;
  }

  flen = cint_to_number(context, len);
  if (((uintjsv_t) len) < get_jsarray_size(a)) {
    JSValue *body = get_jsarray_body(a);
    ret = body[len];
  } else
    ret = get_prop_prototype_chain(a, fixnum_to_string(flen));
  delete_array_element(a, len);
  set_jsarray_length(a, len);
  GC_PUSH(ret);
  set_prop_direct(context, a, gconsts.g_string_length, flen, ATTR_NONE);
  GC_POP(ret);
  set_a(context, ret);
  return;
}

BUILTIN_FUNCTION(array_push)
{
  JSValue a, ret;
  cint len;
  cint i;

  builtin_prologue();
  a = args[0];
  len = number_to_cint(get_jsarray_length(a));
  assert(len >= 0);
  /*
   * The following for-loop is very inefficient.
   * This is for simplicity of implementation.
   */
  GC_PUSH(a);
  for (i = 1; i <= na; i++)
    set_array_prop(context, a, cint_to_number(context, len++), args[i]);
  GC_POP(a);
  ret = (((uintjsv_t) len) <= MAX_ARRAY_LENGTH)?
    cint_to_number(context, len): cint_to_number(context, ((cint) MAX_ARRAY_LENGTH));
  set_a(context, ret);
  return;
}

BUILTIN_FUNCTION(array_reverse)
{
  cint len, mid, lower, upper;
  int lowerExists, upperExists;
  JSValue lowerValue, upperValue;

  builtin_prologue();
  len = number_to_cint(get_jsarray_length(args[0]));
  mid = len / 2;

  lowerValue = JS_NULL;
  GC_PUSH(lowerValue);
  for (lower = 0; lower < mid; lower++) {
    upper = len - lower - 1;
    lowerExists = has_array_element(args[0], lower);
    upperExists = has_array_element(args[0], upper);

    if (lowerExists)
      lowerValue = get_array_element(context, args[0], lower);
    // lowerValue = (lowerExists) ? get_array_element(context, args[0], lower) : JS_NULL;
    if (upperExists)
      upperValue = get_array_element(context, args[0], upper);

    if (lowerExists && upperExists) {
      set_array_prop(context, args[0], cint_to_number(context, lower),
                     upperValue);
      set_array_prop(context, args[0], cint_to_number(context, upper),
                     lowerValue);
    } else if (!lowerExists && upperExists) {
      set_array_prop(context, args[0], cint_to_number(context, lower),
                     upperValue);
      delete_array_element(args[0], upper);
    } else if (lowerExists && !upperExists) {
      set_array_prop(context, args[0], cint_to_number(context, upper),
                     lowerValue);
      delete_array_element(args[0], lower);
    } else {
      /* No action is required */
    }
  }
  GC_POP(lowerValue);
  set_a(context, args[0]);
  return;
}

BUILTIN_FUNCTION(array_shift)
{
  JSValue first, fromVal;
  cint len, from, to;

  builtin_prologue();
  len = number_to_cint(get_jsarray_length(args[0]));
  if (len <= 0) {
    set_a(context, JS_UNDEFINED);
    return;
  }

  first = get_array_element(context, args[0], 0);
  assert(first != JS_EMPTY);
  GC_PUSH(first);
  for (from = 1; from < len; from++) {
    to = from - 1;
    if (has_array_element(args[0], from)) {
      fromVal = get_array_element(context, args[0], from);
      set_array_prop(context, args[0], cint_to_number(context, to), fromVal);
    } else {
      delete_array_element(args[0], to);
    }
  }
  delete_array_element(args[0], len - 1);
  /* should reallocate (shorten) body array here? */
  set_jsarray_length(args[0], --len);
  set_prop_direct(context, args[0], gconsts.g_string_length,
                  cint_to_number(context, len), ATTR_NONE);
  GC_POP(first);
  set_a(context, first);
  return;
}

BUILTIN_FUNCTION(array_slice)
{
  JSValue o, a;
  cint len, relativeStart, relativeEnd, k, n, final, count;
  JSValue start, end, kValue;

  builtin_prologue();
  o = args[0];
  start = (na >= 1)? args[1]: 0;
  end = (na >= 2)? args[2]: JS_UNDEFINED;

  len = number_to_cint(get_jsarray_length(args[0]));
  GC_PUSH2(o, end);
  relativeStart = toInteger(context, start);
  GC_POP(end);

  if (relativeStart < 0) k = max((len + relativeStart), 0);
  else k = min(relativeStart, len);

  if (is_undefined(end)) relativeEnd = len;
  else relativeEnd = toInteger(context, end);

  if (relativeEnd < 0) final = max((len + relativeEnd), 0);
  else final = min(relativeEnd, len);

  count = max(final - k, 0);
  a = new_array_object(context, DEBUG_NAME("array_slice"),
                       gshapes.g_shape_Array, count);
  GC_PUSH(a);
  n = 0;
  while (k < final) {
    if (has_array_element(o,k)) {
      kValue = get_array_element(context, o, k);
      set_array_prop(context, a, cint_to_number(context, n), kValue);
    }
    k++;
    n++;
  }
  GC_POP2(a, o);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(array_sort)
{
  JSValue obj, comparefn;
  cint len;

  builtin_prologue();
  obj = args[0];
  comparefn = args[1];
  len = number_to_cint(get_jsarray_length(obj));
  GC_PUSH(obj);
  asort(context, obj, 0, len - 1, comparefn);
  GC_POP(obj);
  set_a(context, obj);
  return;
}

BUILTIN_FUNCTION(array_debugarray)
{
  /* BUG?: The method does not print a[i] (i >= max(size, ASIZE_LIMIT)) */
  JSValue a;
  cint size, length, to;
  int i;

  builtin_prologue();
  a = args[0];
  size = get_jsarray_size(a);
  length = number_to_cint(get_jsarray_length(a));
  to = length < size? length: size;
  printf("debugarray: size = %lld length = %lld, to = %lld\n",
         (long long) size, (long long) length, (long long) to);
  GC_PUSH(a);
  for (i = 0; i < to; i++) {
    JSValue *body = get_jsarray_body(a);
    printf("i = %d: ", i);
    print_value_simple(context, body[i]);
    printf("\n");
  }
  GC_POP(a);
  set_a(context, JS_UNDEFINED);
  return;
}

BUILTIN_FUNCTION(array_isArray)
{
  builtin_prologue();

  set_a(context, true_false(is_array(args[1])));
  return;
}

BUILTIN_FUNCTION(array_splice){
  JSValue arr, a, delete_count, e, from_value, new_length;
  cint len, relative_start, actual_start, actual_delete_count, k, from, item_count, to, i;

  builtin_prologue();
  /* 1. */
  arr = args[0];
  /* 3. 4. */
  len = number_to_cint(get_jsarray_length(arr));
  /* 5. */
  relative_start = toInteger(context, args[1]);
  /* 6. */
  actual_start = relative_start < 0 ? max((len + relative_start), 0) : min(relative_start, len);
  /* 7. */
  delete_count = na >= 2 ? args[2] : JS_UNDEFINED;
  GC_PUSH(arr);
  actual_delete_count = min(max(toInteger(context, delete_count), 0), len - actual_start);
  /* 2. */
  a = new_array_object(context, DEBUG_NAME("array_splice"), gshapes.g_shape_Array, actual_delete_count);
  GC_PUSH2(a, from_value);
  /* 8. */
  k = 0;
  /* 9. */
  while(k < actual_delete_count){
    /* a. */
    from = actual_start + k;
    /* b. */
    if(has_array_element(arr, from)){
      /* c. */
      /* i. */
      from_value = get_array_element(context, arr, from);
      /* ii. */
      set_array_element(context, a, k, from_value);
    }
    /* d. */
    k++;
  }
  /* 10. */
  // items = &args[3];
  /* 11. */
  item_count = na - 2;
  if(item_count < actual_delete_count){
    /* 12. */
    /* a. */
    k = actual_start;
    /* b. */
    while(k < len - actual_delete_count){
      /* i. */
      from = k + actual_delete_count;
      /* ii. */
      to = k + item_count;
      /* iii. */
      if(has_array_element(arr, from)){
        /* iv. */
        /* 1. */
        from_value = get_array_element(context, arr, from);
        /* 2. */
        set_array_element(context, arr, to, from_value);
      }else{
        /* v. */
        /* 1. */
        delete_array_element(arr, to);
      }
      /* vi. */
      k++;
    }
    /* c. */
    k = len;
    /* d. */
    while(k > len - actual_delete_count + item_count){
      /* i. */
      delete_array_element(arr, k-1);
      /* ii. */
      k--;
    }
  }else{
    /* 13. */
    /* a. */
    k = len - actual_delete_count;
    /* b. */
    while(k > actual_start){
      /* i. */
      from = k + actual_delete_count - 1;
      /* ii. */
      to = k + item_count - 1;
      /* iii. */
      if(has_array_element(arr, from)){
        /* iv. */
        /* 1. */
        from_value = get_array_element(context, arr, from);
        /* 2. */
        set_array_element(context, arr, to, from_value);
      }else{
        /* v. */
        /* 1. */
        delete_array_element(arr, to);
      }
      k--;
    }
  }
  GC_POP(from_value);
  /* 14. */
  k = actual_start;
  /* 15. */
  for(i=3; i<=na; i++){
    /* a. */
    e = args[i];
    /* b. */
    GC_PUSH(e);
    set_array_element(context, arr, k, e);
    GC_POP(e);
    /* c. */
    k++;
  }
  /* 16. */
  new_length = cint_to_number(context, len - actual_delete_count + item_count);
  set_jsarray_length(arr, new_length);
  /* 17. */
  GC_POP2(a, arr);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(array_unshift){
  JSValue o, from_value, e, new_length;
  cint len, k, from, to, j, i;

  builtin_prologue();

  /* 1. */
  o = args[0];
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 5. */
  k = len;
  /* 6. */
  GC_PUSH2(o, from_value);
  while(k > 0){
    /* a. */
    from = k - 1;
    /* b. */
    to = k + na - 1;
    /* c. */
    if(has_array_element(o, from)){
      /* d. */
      /* i. */
      from_value = get_array_element(context, o, from);
      /* ii. */
      set_array_element(context, o, to, from_value);
    }else{
      /* e. */
      /* i. */
      delete_array_element(o, to);
    }
    /* f. */
    k--;
  }
  /* 7. */
  j = 0;
  /* 8. 9. */
  for(i=1; i<=na; i++){
    /* a. */
    e = args[i];
    /* b. */
    GC_PUSH(e);
    set_array_element(context, o, j, e);
    GC_POP(e);
    /* c. */
    j++;
  }
  /* 10. */
  new_length = cint_to_number(context, len + na);
  set_jsarray_length(o, new_length);
  GC_POP2(from_value, o);
  /* 11. */
  set_a(context, new_length);
  return;
}

BUILTIN_FUNCTION(array_indexOf){
  JSValue o, element_k, ret;
  uint32_t len;
  cint n, k;

  builtin_prologue();
  /* 1. */
  o = args[0];
  /* 2. 3. */
  assert(number_to_cint(get_jsarray_length(o)) ==
         (uint32_t) number_to_cint(get_jsarray_length(o)));
  len = (uint32_t) number_to_cint(get_jsarray_length(o));
  /* 4. */
  if(len == 0){
    set_a(context, FIXNUM_MINUS_ONE);
    return;
  }
  GC_PUSH(o);
  /* 5. */
  n = na >= 2 ? toInteger(context, args[2]) : 0;
  /* 6. */
  if(n >= len){
    GC_POP(o);
    set_a(context, FIXNUM_MINUS_ONE);
    return;
  }
  /* 7. 8. */
  k = (n >= 0) ? n : max(len + n, 0);
  /* 9. */
  while(k < len){
    /* a. */
    if(has_array_element(o, k)){
      /* b. */
      /* i. */
      element_k = get_array_element(context, o, k);
      /* ii. */
      if(eq_helper(context, args[1], element_k)){
        /* iii. */
        ret = cint_to_number(context, k);
        GC_POP(o);
        set_a(context, ret);
        return;
      }
      /* c. */
      k++;
    }
  }
  /* 10. */
  GC_POP(o);
  set_a(context, FIXNUM_MINUS_ONE);
  return;
}

BUILTIN_FUNCTION(array_lastIndexOf){
  JSValue o, element_k, ret;
  cint len, n, k;

  builtin_prologue();
  /* 1. */
  o = args[0];
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  if(len == 0){
    set_a(context, FIXNUM_MINUS_ONE);
    return;
  }
  GC_PUSH(o);
  /* 5. */
  n = na >= 2 ? toInteger(context, args[2]) : len - 1;
  /* 6. 7. */
  k = (n >= 0) ? min(n, len - 1) : len + n;
  /* 8. */
  while(k >= 0){
    /* a. */
    if(has_array_element(o, k)){
      /* b. */
      /* i. */
      element_k = get_array_element(context, o, k);
      /* ii. */
      if(eq_helper(context, args[1], element_k)){
        /* iii. */
        ret = cint_to_number(context, k);
        GC_POP(o);
        set_a(context, ret);
        return;
      }
      /* c. */
      k--;
    }
  }
  /* 10. */
  GC_POP(o);
  set_a(context, FIXNUM_MINUS_ONE);
  return;
}

BUILTIN_FUNCTION(array_every){
  JSValue o, callbackfn, t, js_k, k_value, result;
  cint len, k;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("every: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  t = na >= 2 ? args[2] : JS_UNDEFINED;
  /* 6. */
  k = 0;
  /* 7. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        result = send_function3(context, t, callbackfn, k_value, js_k, o);
      else
        result = send_builtin3(context, t, callbackfn, k_value, js_k, o);
      /* iii. */
      if(result == JS_FALSE || (result != JS_TRUE && to_boolean(result) == JS_FALSE)){
        GC_POP2(callbackfn, o);
        set_a(context, JS_FALSE);
        return;
      }
    }
    /* d. */
    k++;
  }
  /* 8. */
  GC_POP2(callbackfn, o);
  set_a(context, JS_TRUE);
  return;
}

BUILTIN_FUNCTION(array_some){
  JSValue o, callbackfn, t, js_k, k_value, result;
  cint len, k;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("some: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  t = na >= 2 ? args[2] : JS_UNDEFINED;
  /* 6. */
  k = 0;
  /* 7. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        result = send_function3(context, t, callbackfn, k_value, js_k, o);
      else
        result = send_builtin3(context, t, callbackfn, k_value, js_k, o);
      /* iii. */
      if(result == JS_TRUE || (result != JS_FALSE && to_boolean(result) == JS_TRUE)){
        GC_POP2(callbackfn, o);
        set_a(context, JS_TRUE);
        return;
      }
    }
    /* d. */
    k++;
  }
  /* 8. */
  GC_POP2(callbackfn, o);
  set_a(context, JS_FALSE);
  return;
}

BUILTIN_FUNCTION(array_forEach){
  JSValue o, callbackfn, t, js_k, k_value;
  cint len, k;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("forEach: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  t = na >= 2 ? args[2] : JS_UNDEFINED;
  /* 6. */
  k = 0;
  /* 7. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        send_function3(context, t, callbackfn, k_value, js_k, o);
      else
        send_builtin3(context, t, callbackfn, k_value, js_k, o);
    }
    /* d. */
    k++;
  }
  /* 8. */
  GC_POP2(callbackfn, o);
  set_a(context, JS_UNDEFINED);
  return;
}

BUILTIN_FUNCTION(array_map){
  JSValue o, callbackfn, t, a, js_k, k_value, mapped_value;
  cint len, k;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("forEach: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  t = na >= 2 ? args[2] : JS_UNDEFINED;
  /* 6. */
  a = new_array_object(context, DEBUG_NAME("array_map"), gshapes.g_shape_Array, len);
  GC_PUSH(a);
  /* 7. */
  k = 0;
  /* 8. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        mapped_value = send_function3(context, t, callbackfn, k_value, js_k, o);
      else
        mapped_value = send_builtin3(context, t, callbackfn, k_value, js_k, o);
      GC_PUSH(mapped_value);
      set_array_element(context, a, k, mapped_value);
      GC_POP(mapped_value);
    }
    /* d. */
    k++;
  }
  /* 9. */
  GC_POP3(a, callbackfn, o);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(array_filter){
  JSValue o, callbackfn, t, a, js_k, k_value, selected;
  cint len, k, to;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("filter: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  t = na >= 2 ? args[2] : JS_UNDEFINED;
  /* 6. */
  a = new_array_object(context, DEBUG_NAME("array_filter"), gshapes.g_shape_Array, len);
  GC_PUSH(a);
  /* 7. */
  k = 0;
  /* 8. */
  to = 0;
  /* 9. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        selected = send_function3(context, t, callbackfn, k_value, js_k, o);
      else
        selected = send_builtin3(context, t, callbackfn, k_value, js_k, o);
      /* iii. */
      if(selected == JS_TRUE || (selected != JS_FALSE && to_boolean(selected) == JS_TRUE)){
        set_array_element(context, a, to, k_value);
        to++;
      }
    }
    /* d. */
    k++;
  }
  set_jsarray_length(a, cint_to_number(context, to));
  /* 10. */
  GC_POP3(a, callbackfn, o);
  set_a(context, a);
  return;
}

BUILTIN_FUNCTION(array_reduce){
  JSValue o, callbackfn, accumulator, js_k, k_value;
  cint len, k, k_present;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("reduce: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  if(len == 0 && na < 2){
    type_error_exception("array_reduce");
  }
  /* 6. */
  k = 0;
  GC_PUSH(accumulator);
  if(na >= 2){
    /* 7. */
    accumulator = args[2];
  }else{
    /* 8. */
    /* a. */
    k_present = FALSE;
    /* b. */
    while(k_present == FALSE && k < len){
      /* ii. */
      k_present = has_array_element(o, k);
      if(k_present){
        /* iii. */
        /* 1. */
        accumulator = get_array_element(context, o, k);
      }
      /* iv */
      k++;
    }
    /* c */
    if(k_present == FALSE){
      type_error_exception("array_reduce");
    }
  }
  /* 9. */
  while(k < len){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        accumulator = send_function4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
      else
        accumulator = send_builtin4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
    }
    /* d. */
    k++;
  }
  /* 10. */
  GC_POP3(accumulator, callbackfn, o);
  set_a(context, accumulator);
  return;
}

BUILTIN_FUNCTION(array_reduceRight){
  JSValue o, callbackfn, accumulator, js_k, k_value;
  cint len, k, k_present;

  builtin_prologue();
  /* 1. */
  o = args[0]; 
  /* 2. 3. */
  len = number_to_cint(get_jsarray_length(o));
  /* 4. */
  callbackfn = args[1];
  if(!is_function(callbackfn) && !is_builtin(callbackfn)){
    LOG_EXIT("reduceRight: the callback function has to be a function/builtin");
  }
  GC_PUSH2(o, callbackfn);
  /* 5. */
  if(len == 0 && na < 2){
    type_error_exception("array_reduceRight");
  }
  /* 6. */
  k = len-1;
  GC_PUSH(accumulator);
  if(na >= 2){
    /* 7. */
    accumulator = args[2];
  }else{
    /* 8. */
    /* a. */
    k_present = FALSE;
    /* b. */
    while(k_present == FALSE && k >= 0){
      /* ii. */
      k_present = has_array_element(o, k);
      if(k_present){
        /* iii. */
        /* 1. */
        accumulator = get_array_element(context, o, k);
      }
      /* iv */
      k--;
    }
    /* c */
    if(k_present == FALSE){
      type_error_exception("array_reduceRight");
    }
  }
  /* 9. */
  while(k >= 0){
    /* b. */
    if(has_array_element(o, k)){
      /* c. */
      /* i. */
      js_k = cint_to_number(context, k);
      GC_PUSH(js_k);
      k_value = get_array_element(context, o, k);
      GC_POP(js_k);
      /* ii. */
      if (is_function(callbackfn))
        accumulator = send_function4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
      else
        accumulator = send_builtin4(context, JS_UNDEFINED, callbackfn, accumulator, k_value, js_k, o);
    }
    /* d. */
    k--;
  }
  /* 10. */
  GC_POP3(accumulator, callbackfn, o);
  set_a(context, accumulator);
  return;
}

#endif /* USE_VMDL */

BUILTIN_FUNCTION(array_toLocaleString){
  not_implemented("toLocaleString");
}

/*
 * sortCompare(context, x, y, comparefn) returns
 *   x < y: minus
 *   x = y: 0
 *   x > y: plus
 */
cint sortCompare(Context *context, JSValue x, JSValue y, JSValue comparefn) {
  char *xString, *yString;
  JSValue *stack, ret;
  int oldsp, oldfp;
  
  GC_PUSH(y);
  if (is_undefined(x) && is_undefined(y)) {
    GC_POP(y);
    return 0;
  } else if (is_undefined(x)) {
    GC_POP(y);
    return 1;
  } else if (is_undefined(y)) {
    GC_POP(y);
    return -1;
  } else if (is_function(comparefn) ||
             (is_builtin(comparefn) && get_jsbuiltin_nargs(comparefn) >= 2)) {
    /*
     * printf(">> sortCompare(%d,%d)\n",fixnum_to_cint(x),
     *        fixnum_to_cint(y));
     */
    stack = &get_stack(context, 0);
    oldsp = get_sp(context);
    oldfp = get_fp(context);
    stack[oldsp] = y;
    stack[oldsp-1] = x;
    stack[oldsp-2] = context->global; /* is receiver always global object? */
    GC_PUSH(x);
    if (is_function(comparefn)) {
      call_function(context, comparefn, 2, TRUE);
      vmrun_threaded(context, get_fp(context));
    }
    else if (is_builtin(comparefn)) {
      save_special_registers(context, stack, oldsp - 6);
      set_fp(context, oldsp-2); /* for GC */
      /*
       * set_lp(context, NULL);
       * set_pc(context, -1);
       * set_cf(context, NULL);
       * set_ac(context, 2);
       */
      call_builtin(context, comparefn, 2, TRUE, FALSE);
    }
    restore_special_registers(context, stack, oldsp - 6);
    set_fp(context, oldfp);
    set_sp(context, oldsp);
    /* should refine lines below? */
    ret = get_a(context);
    if(is_nan(ret)) {
      GC_POP2(x, y);
      return FIXNUM_ZERO;
    }
    ret = to_number(context, ret);
    GC_POP(x);
    if(is_fixnum(ret)){
      GC_POP(y);
      return fixnum_to_cint(ret);
    } else if(is_flonum(ret)) {
      double dret = flonum_value(ret);
      if (dret > 0) {
        GC_POP(y);
        return fixnum_to_cint(1);
      } else if (dret < 0) {
        GC_POP(y);
        return fixnum_to_cint(-1);
      }
      GC_POP(y);
      return FIXNUM_ZERO;
    }
    /* LOG_EXIT("to_number(ret) is not a number"); */
  }
  {
    JSValue vx, vy;
    vx = to_string(context, x);
    GC_POP(y);
    GC_PUSH(vx);
    vy = to_string(context, y);
    GC_POP(vx);
    xString = string_to_cstr(vx);
    yString = string_to_cstr(vy);
    return strcmp(xString, yString);
  }
}

void swap(JSValue *a, JSValue *b) {
  JSValue tmp = *a;

  *a = *b;
  *b = tmp;
}

void insertionSort(Context* context, JSValue array, cint l, cint r, JSValue comparefn) {
  JSValue aj, tmp;
  cint i, j;
  GC_PUSH2(array, comparefn);
  for (i = l; i <= r; i++) {
    tmp = get_array_element(context, array, i); /* tmp = a[i] */
    GC_PUSH(tmp);
    for (j = i - 1; l <= j; j--) {
      aj = get_array_element(context, array, j);
      GC_PUSH(aj);
      if (sortCompare(context, aj, tmp, comparefn) > 0)
        set_array_prop(context, array, cint_to_number(context, j + 1), aj);
      /* a[j+1] = a[j] */
      else {
        GC_POP(aj);
        break;
      }
      GC_POP(aj);
    }
    GC_POP(tmp);
    set_array_prop(context, array, cint_to_number(context, j + 1), tmp);
    /* a[j+1] = tmp; */
  }
  GC_POP2(comparefn, array);
}

void quickSort(Context* context, JSValue array, cint l, cint r, JSValue comparefn) {
  JSValue p, tmp;
  cint i, j;
  /* Find pivot (2nd biggest value in a[l], a[r] and a[l+((r-l)/2)]) */
  JSValue v0, v1, v2;
  cint m = l + ((r - l) / 2);
  GC_PUSH2(array, comparefn);
  v0 = get_array_element(context, array, l);
  v1 = get_array_element(context, array, m);
  v2 = get_array_element(context, array, r);
  GC_PUSH3(v0, v1, v2);
  /* Sort v0 v1 v2 */
  if (sortCompare(context, v0, v1, comparefn) > 0)  /* v0 < v1 */
    swap(&v0, &v1);
  if (sortCompare(context, v1, v2, comparefn) > 0) { /* v0 < v1 and v2 < v1 */
    swap(&v1, &v2);
    if (sortCompare(context, v0, v1, comparefn) > 0) /* v2 < v0 < v1 */
      swap(&v0, &v1);
  }
  /*
   * Update array with
   * [v0, v1(=p), a[2], a[3],..., a[m-1], a[1], a[m+1],..., a[r-1], v2]
   *   l             i                                           j   r
   */
  p = v1;
  GC_PUSH(p);
  /* a[l] = v0 */
  set_array_prop(context, array, cint_to_number(context, l), v0);
 /* a[r] = v2 */
  set_array_prop(context, array, cint_to_number(context, r), v2);
  /* a[m] = a[l+1] */
  set_array_prop(context, array, cint_to_number(context, m),
                 get_array_element(context, array, l+1));
 /* a[l+1] = v1(=p) */
  set_array_prop(context, array, cint_to_number(context, l+1), v1);
  i = l+2;
  j = r-1;
  /* Sorting (from i to j) */
  while (1) {
    while (i < r && sortCompare(context, p,
                                get_array_element(context, array, i),
                                comparefn) > 0)
      i++;
    while (l < j && sortCompare(context, p,
                                get_array_element(context, array, j),
                                comparefn) < 0)
      j--;
    if (i >= j)
      break;
    /* Exchange a[i] and a[j] */
    tmp = get_array_element(context, array, i);
    assert(tmp != JS_EMPTY);
    GC_PUSH(tmp);
    set_array_prop(context, array, cint_to_number(context, i),
                   get_array_element(context, array, j));
    GC_POP(tmp);
    set_array_prop(context, array, cint_to_number(context, j), tmp);
    i++;
    j--;
  }
  GC_POP4(p, v2, v1, v0);
  asort(context, array, j + 1, r, comparefn);
  GC_POP2(comparefn, array);
  asort(context, array, l, i - 1, comparefn);
}

void asort(Context* context, JSValue array, cint l, cint r, JSValue comparefn) {
  /* DEBUG: print array
   *  for(cint z = 0; z < array_length(array); z++) {
   *    tmp = get_array_prop(context, array, cint_to_fixnum(z));
   *    if (l <= z && z <= r) print_value_simple(context, tmp);
   *    else printf("_");
   *    if (z < array_length(array)-1) printf(",");
   *    else printf("\n");
   *  }
   */
  if (l >= r) return;
  if(r - l <= INSERTION_SORT_THRESHOLD)
    insertionSort(context, array, l, r, comparefn);
  else quickSort(context, array, l, r, comparefn);
}

/*
 * property table
 */

/* prototype */
ObjBuiltinProp ArrayPrototype_builtin_props[] = {
#ifndef ELIMINATED_ARRAY_TOSTRING
  { "toString",       array_toString,       0, ATTR_DE },
#endif
  { "toLocaleString", array_toLocaleString, 0, ATTR_DE },
#ifndef ELIMINATED_ARRAY_JOIN
  { "join",           array_join,           1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_CONCAT
  { "concat",         array_concat,         0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_POP
  { "pop",            array_pop,            0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_PUSH
  { "push",           array_push,           1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_REVERSE
  { "reverse",        array_reverse,        0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_SHIFT
  { "shift",          array_shift,          1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_SLICE
  { "slice",          array_slice,          2, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_SORT
  { "sort",           array_sort,           1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_DEBUGARRAY
  { "debugarray",     array_debugarray,     0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_SPLICE
  { "splice",         array_splice,         2, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_UNSHIFT
  { "unshift",        array_unshift,        0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_INDEXOF
  { "indexOf",        array_indexOf,        0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_LASTINDEXOF
  { "lastIndexOf",    array_lastIndexOf,    0, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_EVERY
  { "every",          array_every,          1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_SOME
  { "some",           array_some,           1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_FOREACH
  { "forEach",        array_forEach,        1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_MAP
  { "map",            array_map,            1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_FILTER
  { "filter",         array_filter,         1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_REDUCE
  { "reduce",         array_reduce,         1, ATTR_DE },
#endif
#ifndef ELIMINATED_ARRAY_REDUCERIGHT
  { "reduceRight",    array_reduceRight,    1, ATTR_DE },
#endif
};
ObjDoubleProp  ArrayPrototype_double_props[] = {
  { "length",   0, ATTR_DDDE, 2},
};
ObjGconstsProp ArrayPrototype_gconsts_props[] = {};
/* constructor */
ObjBuiltinProp ArrayConstructor_builtin_props[] = {
#ifndef ELIMINATED_ARRAY_ISARRAY
  { "isArray", array_isArray, 1, ATTR_DE },
#endif
};
ObjDoubleProp  ArrayConstructor_double_props[] = {};
ObjGconstsProp ArrayConstructor_gconsts_props[] = {
  { "prototype", &gconsts.g_prototype_Array,  ATTR_ALL },
};
/* instance */
ObjBuiltinProp Array_builtin_props[] = {};
ObjDoubleProp  Array_double_props[] = {
  { "length",    0, ATTR_DDDE, 2 },  /* placeholder */
};
ObjGconstsProp Array_gconsts_props[] = {};
DEFINE_PROPERTY_TABLE_SIZES_PCI(Array);

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
