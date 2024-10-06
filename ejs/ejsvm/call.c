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

/*
 * calls a function
 *
 * When this function is called, the stack is:
 *
 *         ...
 * pos:    place where CF is saved
 *         place where PC is saved
 *         place where LP is saved
 *         place where FP is saved
 *         receiver                        <-- this place is new fp
 *         arg1
 *         arg2
 *         ...
 *  sp:     argN
 */
void call_function(Context *context, JSValue fn, int nargs, int sendp) {
  FunctionTable *t;
  JSValue *stack;
  int sp, pos;

  sp = get_sp(context);
  stack = &get_stack(context, 0);

  /*
   * saves special registers into the stack
   */
  pos = sp - nargs - 4;
  save_special_registers(context, stack, pos);

  /*
   * sets special registers
   */
  set_fp(context, sp - nargs);
  set_ac(context, nargs);
  set_lp(context, get_jsfunction_environment(fn));
  t = get_jsfunction_table_entry(fn);
  set_cf(context, t);
  if (sendp == TRUE)
    set_pc(context, ftab_send_entry(t));
  else
    set_pc(context, ftab_call_entry(t));
}

/*
 * call a function at the tail position
 */
void tailcall_function(Context *context, JSValue fn, int nargs, int sendp) {
  FunctionTable *t;
  int fp;

  fp = get_fp(context);
  set_sp(context, fp + nargs);
  set_ac(context, nargs);
  set_lp(context, get_jsfunction_environment(fn));
  t = get_jsfunction_table_entry(fn);
  set_cf(context, t);
  if (sendp == TRUE)
    set_pc(context, ftab_call_entry(t));
  else
    set_pc(context, ftab_send_entry(t));
}

/*
 * calls a builtin function
 *
 * When this function is called, the stack is:
 *
 *         ...
 * pos:    place where CF is saved
 *         place where PC is saved
 *         place where LP is saved
 *         place where FP is saved
 *         receiver                        <-- this place is new fp
 *         arg1
 *         arg2
 *         ...
 * sp:     argN
 */
void call_builtin(Context *context, JSValue fn, int nargs, int sendp,
                  int constrp) {
  builtin_function_t body;
  JSValue *stack;
  int na;
  int sp;

  body = ((constrp == TRUE) ?
          get_jsbuiltin_constructor(fn) :
          get_jsbuiltin_body(fn));
  na = get_jsbuiltin_nargs(fn);

  sp = get_sp(context);
  stack = &get_stack(context, 0);

  /*
   * printf("call_builtin: sp = %d, fp = %d, stack = %p, nargs = %d, sendp = %d, constrp = %d\n",
   *  sp, fp, stack, nargs, sendp, constrp);
   */

  /*
   * The original code called save_special_registers here, but this seems
   * to be unnecessary because builtin function code does not manipulate
   * special registers.  However, since the compiler takes rooms from
   * stack[pos] to stack[pos + 3] for saving the values of special registers,
   * it may be necessary to fill these rooms with harmless values, e.g.,
   * FIXNUM_ZERO to make the GC work correctly.
   * 2017/03/15:  It seems to be unnecessary bacause setfl instruction
   * stores JS_UNDEFINEDs into the stack area.
   *
   *  pos = sp - nargs - 4;
   *  save_special_registers(context, stack, pos);
   */

  /*
   * sets the value of the receiver to the global object if it is not set yet
   */
  if (sendp == FALSE)
    stack[sp - nargs] = context->global;

  while (nargs < na) {
    stack[++sp] = JS_UNDEFINED;
    nargs++;
  }

  set_sp(context, sp);
  (*body)(context, sp - nargs, nargs);    /* real-n-args? */
}

/*
 * calls a builtin function at a tail position
 */
void tailcall_builtin(Context *context, JSValue fn, int nargs, int sendp,
                      int constrp) {
  builtin_function_t body;
  JSValue *stack;
  int na;
  int fp;

  body = ((constrp == TRUE) ?
          get_jsbuiltin_constructor(fn) :
          get_jsbuiltin_body(fn));
  na = get_jsbuiltin_nargs(fn);

  fp = get_fp(context);
  stack = &get_stack(context, 0);

  /*
   * sets the value of the receiver to the global object if it is not set yet
   */
  if (sendp == FALSE)
    stack[0] = context->global;

  while (nargs < na)
    stack[++nargs + fp] = JS_UNDEFINED;

  set_sp(context, fp + nargs);
  (*body)(context, fp, nargs);    /* real-n-args? */
  stack = &get_stack(context, 0); /* stack may be moved by GC */
  restore_special_registers(context, stack, fp - 4);
}

JSValue invoke_function_inner(Context *context, JSValue fn, JSValue *stack, int pos, int newfp, int sp, int oldfp, int oldsp, int sendp, int nargs){
  FunctionTable *t;
  JSValue ret;

  save_special_registers(context, stack, pos);
  set_fp(context, newfp);
  set_sp(context, sp);
  set_ac(context, nargs);
  set_lp(context, get_jsfunction_environment(fn));
  t = get_jsfunction_table_entry(fn);
  set_cf(context, t);
  if (sendp == TRUE)
    set_pc(context, ftab_send_entry(t));
  else
    set_pc(context, ftab_call_entry(t));
  vmrun_threaded(context, newfp);
  ret = get_a(context);
  restore_special_registers(context, stack, pos);
  set_fp(context, oldfp);
  set_sp(context, oldsp);
  return ret;
}

JSValue send_function3(Context *context, JSValue receiver, JSValue fn,
                        JSValue arg1, JSValue arg2, JSValue arg3) {
  JSValue *stack;
  int sp, newfp, pos, oldfp, oldsp;

  /* printf("invoke_function: nargs = %d\n", nargs); */
  stack = &get_stack(context, 0);
  oldsp = sp = get_sp(context);
  oldfp = get_fp(context);
  pos = sp + 1;           /* place where cf register will be saved */
  sp += 5;                /* makes room for cf, pc, lp, fp, and receiver */
  stack[sp] = receiver;   /* stores the receiver */
  newfp = sp;             /* place where the receiver is stored */ 
  stack[++sp] = arg1;     /* copies the actual arguments */
  stack[++sp] = arg2;
  stack[++sp] = arg3;

  return invoke_function_inner(context, fn, stack, pos, newfp, sp, oldfp, oldsp, TRUE, 3);
}

JSValue send_function4(Context *context, JSValue receiver, JSValue fn,
                        JSValue arg1, JSValue arg2, JSValue arg3, JSValue arg4) {
  JSValue *stack;
  int sp, newfp, pos, oldfp, oldsp;

  /* printf("invoke_function: nargs = %d\n", nargs); */
  stack = &get_stack(context, 0);
  oldsp = sp = get_sp(context);
  oldfp = get_fp(context);
  pos = sp + 1;           /* place where cf register will be saved */
  sp += 5;                /* makes room for cf, pc, lp, fp, and receiver */
  stack[sp] = receiver;   /* stores the receiver */
  newfp = sp;             /* place where the receiver is stored */ 
  stack[++sp] = arg1;     /* copies the actual arguments */
  stack[++sp] = arg2;
  stack[++sp] = arg3;
  stack[++sp] = arg4;

  return invoke_function_inner(context, fn, stack, pos, newfp, sp, oldfp, oldsp, TRUE, 4);
}
/*
 * Invokes a function fn with arguments args in a new vmloop.
 *   `as' is the array of arguments if `nargs' > 0.
 *   Otherwise, `as' is JS_UNDEFINED.
 */
JSValue invoke_function(Context *context, JSValue receiver, JSValue fn,
                        int sendp, JSValue as, int nargs) {
  JSValue *stack, *array_body;
  int sp, newfp, pos, oldfp, oldsp, i;

  /* printf("invoke_function: nargs = %d\n", nargs); */
  stack = &get_stack(context, 0);
  oldsp = sp = get_sp(context);
  oldfp = get_fp(context);
  pos = sp + 1;           /* place where cf register will be saved */
  sp += 5;                /* makes room for cf, pc, lp, fp, and receiver */
  stack[sp] = receiver;   /* stores the receiver */
  newfp = sp;             /* place where the receiver is stored */
  if (nargs > 0) { 
    array_body = get_jsarray_body(as);
    for (i = 0; i < nargs; i++)   /* copies the actual arguments */
      stack[++sp] = array_body[i];
  }

  return invoke_function_inner(context, fn, stack, pos, newfp, sp, oldfp, oldsp, sendp, nargs);
}

JSValue invoke_builtin_inner(Context *context, JSValue fn, int sp, int oldsp, int sendp, int nargs){
  set_sp(context, sp);
  call_builtin(context, fn, nargs, sendp, FALSE);
  set_sp(context, oldsp);
  return get_a(context);
}

JSValue send_builtin3(Context *context, JSValue receiver, JSValue fn,
                       JSValue arg1, JSValue arg2, JSValue arg3) {
  int oldsp, sp;
  JSValue *stack;

  oldsp = sp = get_sp(context);
  stack = &get_stack(context, 0);
  stack[++sp] = receiver;       /* set receiver */
  stack[++sp] = arg1;           /* copies the actual arguments */
  stack[++sp] = arg2;
  stack[++sp] = arg3;
  return invoke_builtin_inner(context, fn, sp, oldsp, TRUE, 3);
}

JSValue send_builtin4(Context *context, JSValue receiver, JSValue fn,
                       JSValue arg1, JSValue arg2, JSValue arg3, JSValue arg4) {
  int oldsp, sp;
  JSValue *stack;

  oldsp = sp = get_sp(context);
  stack = &get_stack(context, 0);
  stack[++sp] = receiver;       /* set receiver */
  stack[++sp] = arg1;           /* copies the actual arguments */
  stack[++sp] = arg2;
  stack[++sp] = arg3;
  stack[++sp] = arg4;
  return invoke_builtin_inner(context, fn, sp, oldsp, TRUE, 4);
}

/*
 * invokes a builtin function
 *   `as' is the array of arguments if `nargs' > 0.
 *   Otherwise, `as' is JS_UNDEFINED.
 */
JSValue invoke_builtin(Context *context, JSValue receiver, JSValue fn,
                       int sendp, JSValue as, int nargs) {
  int oldsp, sp, i;
  JSValue *stack;
  JSValue *array_body;

  oldsp = sp = get_sp(context);
  stack = &get_stack(context, 0);
  stack[++sp] = receiver;       /* set receiver */
  if (nargs > 0) {
    array_body = get_jsarray_body(as);
    for (i = 0; i < nargs; i++)   /* copies the actual arguments */
      stack[++sp] = array_body[i];
  }
  return invoke_builtin_inner(context, fn, sp, oldsp, sendp, nargs);
}

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
