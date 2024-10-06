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

#ifdef USE_VMDL

#include "builtins/boolean_constr.inc"

#include "builtins/boolean_constr_nonew.inc"

#include "builtins/boolean_toString.inc"

#include "builtins/boolean_valueOf.inc"

#else /* USE_VMDL */

/*
 * constructor of a boolean
 */
BUILTIN_FUNCTION(boolean_constr)
{
  JSValue rsv;

  builtin_prologue();  
  rsv = new_boolean_object(context, DEBUG_NAME("boolean_ctor"),
                           gshapes.g_shape_Boolean, JS_FALSE);
  if (na > 0)
    set_jsboolean_object_value(rsv, to_boolean(args[1]));
  set_a(context, rsv);
}

BUILTIN_FUNCTION(boolean_constr_nonew)
{
  JSValue ret;

  builtin_prologue();
  ret = (na > 0) ? to_boolean(args[1]) : JS_FALSE;
  set_a(context, ret);
}

BUILTIN_FUNCTION(boolean_toString)
{
  JSValue arg;

  builtin_prologue();  
  arg = args[0];
  if (is_boolean_object(arg))
    arg = get_jsboolean_object_value(arg);
  else if(!is_boolean(arg))
    type_error_exception("boolean_toString");
  arg = to_string(context, arg);
  set_a(context, arg);
}

BUILTIN_FUNCTION(boolean_valueOf)
{
  JSValue arg;

  builtin_prologue();  
  arg = args[0];
  if (is_boolean_object(arg))
    arg = get_jsboolean_object_value(arg);
  else if(!is_boolean(arg))
    type_error_exception("boolean_valueOf");
  set_a(context, arg);
}

#endif /* USE_VMDL */

/*
 * property table
 */

/* prototype */
ObjBuiltinProp BooleanPrototype_builtin_props[] = {
#ifndef ELIMINATED_BOOLEAN_TOSTRING
  { "toString",        boolean_valueOf,    0, ATTR_DE },
#endif
#ifndef ELIMINATED_BOOLEAN_VALUEOF
  { "valueOf",        boolean_valueOf,    0, ATTR_DE },
#endif
};
ObjDoubleProp  BooleanPrototype_double_props[] = {};
ObjGconstsProp BooleanPrototype_gconsts_props[] = {};
/* constructor */
ObjBuiltinProp BooleanConstructor_builtin_props[] = {};
ObjDoubleProp  BooleanConstructor_double_props[] = {};
ObjGconstsProp BooleanConstructor_gconsts_props[] = {
  { "prototype", &gconsts.g_prototype_Boolean,  ATTR_ALL },
};
/* instance */
ObjBuiltinProp Boolean_builtin_props[] = {};
ObjDoubleProp  Boolean_double_props[] = {};
ObjGconstsProp Boolean_gconsts_props[] = {};
DEFINE_PROPERTY_TABLE_SIZES_PCI(Boolean);

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
