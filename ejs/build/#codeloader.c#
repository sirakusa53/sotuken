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

#define CPU_LITTLE_ENDIAN

#define OBC_FILE_MAGIC 0xec

#if !defined(USE_SBC) && !defined(USE_OBC)
#error Either USE_SBC or USE_OBC should be defined.
#endif

#if !defined(USE_SBC) && defined(PROFILE)
#error PROFILE can be defined only when USE_SBC is defined.
#endif

#define calc_displacement(ninsns, pc, index) ((InstructionDisplacement) index)

/*
 * Assign `var = val' with range check.
 */
#ifdef USE_CPP
#define TYPE_FROM_VAR(var) decltype(var)
#else /* USE_CPP */
#define TYPE_FROM_VAR(var) typeof(var)
#endif
#define load_value(var, val, min, max, type, msg)       \
  do {                                                  \
    TYPE_FROM_VAR(var) _val_tmp;                        \
    _val_tmp = (val);                                   \
    if (_val_tmp < (min))                               \
      LOG_EXIT("%s : %d IS LESS THAN MIN VALUE %d.",    \
               msg, _val_tmp, (min));                   \
    if ((max) < _val_tmp)                               \
      LOG_EXIT("%s : %d IS GREATER THAN MAX VALUE %d.", \
               msg, _val_tmp, (max));                   \
    var = (type) _val_tmp;                              \
  } while(0)

#define load_small_primitive(var, val, msg)     \
  load_value(var, val,                          \
             minval_small_primitive(),          \
             maxval_small_primitive(),          \
             SmallPrimitive, msg)

#define load_literal(var, val, msg)             \
  load_value(var, val,                          \
             minval_literal(),                  \
             maxval_literal(),                  \
             Literal, msg)

#define load_register(var, val, msg)            \
  load_value(var, val,                          \
             minval_register(),                 \
             maxval_register(),                 \
             Register, msg)

#define load_instruction_displacement(var, val, msg)    \
  load_value(var, val,                                  \
             minval_instruction_displacement(),         \
             maxval_instruction_displacement(),         \
             InstructionDisplacement, msg)

#define load_constant_displacement(var, val, msg)       \
  load_value(var, val,                                  \
             minval_constant_displacement(),            \
             maxval_constant_displacement(),            \
             ConstantDisplacement, msg)

#define load_subscript(var, val, msg)           \
  load_value(var, val,                          \
             minval_subscript(),                \
             maxval_subscript(),                \
             Subscript, msg)

#define constant_displacement_to_register(var, val, msg)                 \
  do {                                                                   \
    ConstantDisplacement _val_tmp = (val);                               \
    ConstantDisplacement min = (ConstantDisplacement) minval_register(); \
    ConstantDisplacement max = (ConstantDisplacement) maxval_register(); \
    if (_val_tmp < min)                                                  \
      LOG_EXIT("%s : %d IS LESS THAN MIN VALUE %d.",                     \
               msg, _val_tmp, min);                                      \
    if (max < _val_tmp)                                                  \
      LOG_EXIT("%s : %d IS GREATER THAN MAX VALUE %d.",                  \
               msg, _val_tmp, (max));                                    \
    var = (Register) _val_tmp;                                           \
  } while (0)


/*
 * OBC file header (magic + fingerprint).
 * The second byte is shared with SBC file.
 */
union obc_file_header {
  struct {
    unsigned char magic;
    unsigned char fingerprint;
  } s;
  unsigned short x;
};
union obc_file_header obc_file_header = {
  .s = {
    .magic = OBC_FILE_MAGIC,
    .fingerprint =
#include "specfile-fingerprint.h"
  }
};
#define FINGERPRINT_WILDCARD 0xff
#define OBC_FILE_HEADER_WILDCARD                        \
((union obc_file_header)                                \
 {.s = {.magic = OBC_FILE_MAGIC,                        \
         .fingerprint = FINGERPRINT_WILDCARD}})

/*
 * instruction table
 */

#define LOADBUFLEN (1024 * 1024)

#ifdef USE_SBC
static int insn_load_sbc(Context *, Instruction *, JSValue *, int, int, int, int, int);
#endif

#ifdef USE_OBC
static void const_load(Context *, int, JSValue *);
static int insn_load_obc(Context *, Instruction *, JSValue *, int, int, int, int, int);
#endif

static uint32_t decode_escape_char(char *);

static void set_function_table(FunctionTable *, int, Instruction *, JSValue *,
                               int, int, int, int, int);

static FILE *file_pointer;

#ifdef USE_SBC
/*
 * reads the next line from the input stream
 */
inline char *step_load_code(char *buf, int buflen) {
  return fgets(buf, buflen, file_pointer == NULL? stdin: file_pointer);
}

#define DELIM " \n\r"
#define DELIM2 "\n\r"
#define first_token(b) strtok(b, DELIM)
#define next_token()   strtok(NULL, DELIM)
#define next_token2()  strtok(NULL, DELIM2)

inline int check_read_token(char *buf, const char *tok) {
  char *p;
  p = first_token(buf);
  if (strcmp(p, tok) != 0)
    LOG_EXIT("Error: %s is not defined", tok);
  return atoi(next_token());
}
#endif /* USE_SBC */

/*
 * codeloader
 */
int code_loader(Context *ctx, FunctionTable *ftable, int ftbase)
{
  Instruction *insns;
  JSValue *consttop;
  int nfuncs, callentry, sendentry, nlocals, ninsns, nconsts;
  int i, j, ret;
#ifdef USE_SBC
  char buf[LOADBUFLEN];
#endif
#ifdef USE_OBC
  unsigned char b[2];
#endif

#ifdef USE_SBC
#define next_buf_sbc() (step_load_code(buf, LOADBUFLEN) != NULL)
#define buf_to_int_sbc(s)   check_read_token(buf, s)
#endif

#ifdef USE_OBC
#define next_buf_obc() (fread(b, sizeof(unsigned char), 2, file_pointer) > 0)
#ifdef CPU_LITTLE_ENDIAN
#define buf_to_int_obc(s)   (b[0] * 256 + b[1])
#else
#define buf_to_int_obc(s)   (b[1] * 256 + b[0])
#endif
#endif

#if defined(USE_OBC) && defined(USE_SBC)

#define IS_SBC() (obcsbc == FILE_SBC)
#define IS_OBC() (obcsbc == FILE_OBC)
#define next_buf()                                                   \
  if ((IS_OBC()? next_buf_obc(): next_buf_sbc()) == 0) return 0
#define buf_to_int(s)                                                \
  (IS_OBC()? buf_to_int_obc(s): buf_to_int_sbc(s))
#define insn_load_bc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase) \
  (IS_OBC()?                                                              \
    insn_load_obc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase)    \
  : insn_load_sbc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase))

#else

#ifdef USE_OBC
#define IS_SBC() (0)
#define IS_OBC() (1)
#define next_buf()      if (next_buf_obc() == 0) return 0
#define buf_to_int(s)   buf_to_int_obc(s)
#define insn_load_bc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase) \
            insn_load_obc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase)
#endif

#ifdef USE_SBC
#define IS_SBC() (1)
#define IS_OBC() (0)
#define next_buf()      if (next_buf_sbc() == 0) return 0
#define buf_to_int(s)   buf_to_int_sbc(s)
#define insn_load_bc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase) \
            insn_load_sbc(ctx, insns, ctop, fidx, ninsns, nconsts, pc, ftbase)
#endif

#endif

  /*
   * check file header
   */
  {
    next_buf();
    if (IS_SBC()) {
#ifdef USE_SBC
      int fingerprint = buf_to_int("fingerprint");
      if (fingerprint != obc_file_header.s.fingerprint &&
          fingerprint != FINGERPRINT_WILDCARD)
        LOG_EXIT("SBC file header mismatch. 0x%x is expected but saw 0x%x.\n",
                 obc_file_header.s.fingerprint, fingerprint);
#endif /* USE_SBC */
    }
    if (IS_OBC()) {
#ifdef USE_OBC
      union obc_file_header hdr;
      hdr.s.magic = b[0];
      hdr.s.fingerprint = b[1];
      if (hdr.x != obc_file_header.x &&
          hdr.x != OBC_FILE_HEADER_WILDCARD.x)
        LOG_EXIT("OBC file header mismatch. 0x%x is expected but saw 0x%x.\n",
                 obc_file_header.s.fingerprint, hdr.s.fingerprint);
#endif /* USE_OBC */
    }
  }

  /*
   * checks the funclength and obtain the number of functions
   */
  next_buf();
  nfuncs = buf_to_int("funcLength");
  ctx->nfuncs += nfuncs;

  /*
   * reads each function
   */
  for (i = 0; i < nfuncs; i++) {
    /* callentry */
    next_buf();
    callentry = buf_to_int("callentry");

    /* sendentry */
    next_buf();
    sendentry = buf_to_int("sendentry");

    /* numberOfLocals */
    next_buf();
    nlocals = buf_to_int("numberOfLocals");

    /* numberOfInstructions */
    next_buf();
    ninsns = buf_to_int("numberOfInstructions");

    /* numberOfConstants */
    next_buf();
    nconsts = buf_to_int("numberOfConstants");

    insns = ((Instruction *)malloc(sizeof(Instruction) * ninsns));
    if (insns == NULL)
      LOG_EXIT("Allocating instruction array failed.");

    consttop = ((JSValue *)malloc(sizeof(JSValue) * nconsts));
    if (consttop == NULL)
      LOG_EXIT("Allocating constant array failed.");
    for (j = 0; j < nconsts; j++) consttop[j] = JS_UNDEFINED;

#ifdef NEED_INSTRUCTION_CACHE
    init_instruction_cache(i + ftbase, ninsns);
#endif /* NEED_INSTRUCTION_CACHE */

    /*
     * Registers various information into the function table.
     * It is necessary to do this here because gc might occur during
     * loading constants.
     */
    set_function_table(ftable, i + ftbase, insns, consttop,
                       callentry, sendentry, nlocals, ninsns, nconsts);
    
    /* loads instructions for each function */
    for (j = 0; j < ninsns; j++) {
      ret = insn_load_bc(ctx, insns, consttop, i + ftbase, ninsns, nconsts, j, ftbase);
      if (ret == LOAD_FAIL)
        LOG_EXIT("Function #%d, instruction #%d: load failed", i, j);
    }

    if (IS_OBC()) {
#ifdef USE_OBC
      const_load(ctx, nconsts, consttop);
#endif /* USE_OBC */
    }
  }

#ifdef DEBUG
  if (ftable_flag == TRUE)
    print_function_table(ftable, i + ftbase);
#endif /* DEBUG */
  return nfuncs;

#undef IS_SBC
#undef IS_OBC
#undef next_buf
#undef buf_to_int
#undef insn_load_bc
}

#ifdef USE_OBC
JSValue string_load(Context *ctx, int size)
{
  char *str;
  JSValue v;

  assert(size > 0);

  str = (char*) malloc(sizeof(char) * size);
  if (fread(str, sizeof(char), size, file_pointer) < ((size_t) size))
    LOG_ERR("string literal too short.");
  decode_escape_char(str);
  v = cstr_to_string(NULL, str);
  free(str);
  return v;
}

JSValue double_load(Context *ctx)
{
  union {
    double d;
    unsigned char b[8];
  } u;

  fread(&u.b, sizeof(unsigned char), 8, file_pointer);

#ifdef CPU_LITTLE_ENDIAN
  {
    int i;
    for (i = 0; i < 4; i++) {
      unsigned char c;
      c = u.b[i]; u.b[i] = u.b[7 - i]; u.b[7 - i] = c;
    }
  }
#endif
  /* printf("double loaded, value = %lf\n", u.d); */
  return double_to_number(ctx, u.d);
}

#ifdef USE_REGEXP
JSValue regexp_load(Context *ctx, int size, int flag)
{
  char *str;
  JSValue v;
  Shape *os = gshapes.g_shape_RegExp;

  assert(size > 0);

  str = (char*) malloc(sizeof(char) * size);
  if (fread(str, sizeof(char), size, file_pointer) < ((size_t) size))
    LOG_ERR("string literal too short.");
  decode_escape_char(str);
  v = new_regexp_object(ctx, DEBUG_NAME("regexp_load"), os, str, flag);
  free(str); /* TODO: is this free need? */
  return v;
}
#endif /* USE_REGEXP */

void const_load(Context *ctx, int nconsts, JSValue *ctop)
{
  int i;
  unsigned char b[2];

#define next_buf()      fread(b, sizeof(unsigned char), 2, file_pointer)
#define buf_to_int(s)   (b[0] * 256 + b[1])
  
  for (i = 0; i < nconsts; i++) {
    int size;
    JSValue v = JS_UNDEFINED;

    next_buf();
    size = buf_to_int();
    if (size > 0) {
      next_buf();
      InsnOperandType type = (InsnOperandType) buf_to_int();

      switch (type) {
      case STR:
        v = string_load(ctx, size);
        break;
      case NUM:
        v = double_load(ctx);
        break;
#ifdef USE_REGEXP
      case REX:
      {
        next_buf();
        int flag = buf_to_int();
        v = regexp_load(ctx, size, flag);
        break;
      }
#endif /* USE_REGEXP */
      default:
        LOG_ERR("Error: unexpected operand type in loading constants");
        break;
      }
      ctop[i] = v;
    }
  }

#undef next_buf
#undef buf_to_int
}
#endif

/*
 * initializes the code loader
 */
void init_code_loader(FILE *fp) {
  file_pointer = fp;
}

/*
 * finalizes the code loader
 */
void end_code_loader() {
  if (repl_flag == TRUE)
    return;
  if (file_pointer != NULL)
    fclose(file_pointer);
}

#ifdef USE_SBC
#define NOT_OPCODE ((Opcode)(-1))

Opcode find_insn(char* s) {
  int i;
  for (i = 0; i < numinsts; i++)
    if (strcmp(insn_info_table[i].insn_name, s) == 0)
      return (Opcode) i;
  /* not found in the instruction table */
  return NOT_OPCODE;
}
#endif /* USE_SBC */

#ifdef USE_OBC
Bytecode convertToBc(unsigned char buf[sizeof(Bytecode)]) {
  size_t i;
  Bytecode ret;

  ret = 0;
  for (i = 0; i < sizeof(Bytecode); i++)
    ret = ret * 256 + buf[i];
  return ret;
}
#endif /* USE_OBC */

#ifdef USE_SBC
#define load_op(ctx, op_type, op)                               \
  do {                                                          \
    op = 0;                                                     \
    switch (op_type) {                                          \
    case NONE:                                                  \
      break;                                                    \
    case LIT:                                                   \
      {                                                         \
        load_literal(*((Literal *)&(op)), atoi(next_token()),   \
                             "load_op LIT");                    \
      }                                                         \
      break;                                                    \
    case REG:                                                   \
      {                                                         \
        load_register(op, atoi(next_token()),                   \
                      "load_op REG");                           \
      }                                                         \
      break;                                                    \
    case STR:                                                   \
      {                                                         \
        char *src;                                              \
        int index;                                              \
        ConstantDisplacement disp;                              \
        src = next_token();                                     \
        index = load_jsvalue_sbc(                               \
            ctx, src, ctop, ninsns, nconsts);                   \
        disp = calc_displacement(ninsns, pc, index);            \
        constant_displacement_to_register(                      \
            op, disp, "load_op STR");                           \
      }                                                         \
      break;                                                    \
    case NUM:                                                   \
      {                                                         \
        char *src;                                              \
        int index;                                              \
        ConstantDisplacement disp;                              \
        src = next_token();                                     \
        index = load_jsvalue_sbc(                               \
            ctx, src, ctop, ninsns, nconsts);                   \
        disp = calc_displacement(ninsns, pc, index);            \
        constant_displacement_to_register(                      \
            op, disp, "load_op STR");                           \
      }                                                         \
      break;                                                    \
    case SPEC:                                                  \
      { op = specstr_to_jsvalue(next_token()); }                \
      break;                                                    \
    default:                                                    \
      return LOAD_FAIL;                                         \
    }                                                           \
  } while(0)
#endif /* USE_SBC */

/*
 * loads an instruction
 */
#ifdef USE_SBC

/*
 * Reads the constant at the operand field of an instruction in a sbc file
 * and stores the constant into *d (for double) or *str (for char *)..
 * Format of constant is ``#<n>:<type>=constant'' or ``#<n>:<type>=<opt>=constant'',
 * where <n> is the zero-origined index within the constant table.
 * Return value is the index (<n>) or -1 (in an error case).
 */
int load_const_sbc(char *start, int nconsts, InsnOperandType *ptype, double *d, char **str, int *opt) {
  char *s, *p;
  int index;
  InsnOperandType type = NONE;

  s = start;
  if (s == NULL || *s++ != '#') {
    LOG_ERR("%s: constant format error", start);
    return -1;
  }

  /* read index (<n>) */
  for (p = s; *p != ':' && *p != '\0'; p++);
  if (*p == '\0') {
    LOG_ERR("%s: constant format error", start);
    return -1;
  }
  *p++ = '\0';
  index = atoi(s);
  if (index < 0 || nconsts <= index) {
    LOG_ERR("%s: invalid index of the constant", start);
    return -1;
  }

  /* read type */
  for (s = p; *p != '=' && *p != '\0'; p++);
  if (*p == '\0') {
    LOG_ERR("%s:%s: constant format error", start, s);
    return -1;
  }
  *p++ = '\0';
  if (strcmp(s, "number") == 0)
    type = NUM;
  else if (strcmp(s, "string") == 0)
    type = STR;
#ifdef USE_REGEXP
  else if (strcmp(s, "regexp") == 0)
    type = REX;
#endif /* REGEXP */

  if (type == NONE) {
    LOG_ERR("%s: unknown constant type", s);
    return -1;
  }

  *ptype = type;

  /* read opt */
#ifdef USE_REGEXP
  if (type == REX) {
    for (s = p; *p != '=' && *p != '\0'; p++);
    if (*p == '\0') {
      LOG_ERR("%s:%s: constant format error", start, s);
      return -1;
    }
    *p++ = '\0';

    if (type == REX && opt != NULL)
      *opt = atoi(s);
    else {
      LOG_ERR("invalid argument to read_const_sbc");
      return -1;
    }
  }
#endif /* USE_REGEXP */

  /* read constant */
  if (type == NUM && d != NULL) {
    *d = atof(p);
    return index;
  }
  else if (type == STR && str != NULL) {
    *str = p;
    return index;
  }
#ifdef USE_REGEXP
  else if (type == REX && str != NULL) {
    *str = p;
    return index;
  }
#endif /* USE_REGEXP */
  else {
    LOG_ERR("invalid argument to read_const_sbc");
    return -1;
  }
}

int load_jsvalue_sbc(Context *ctx, char *src, JSValue *ctop, int ninsns, int nconsts) {
  InsnOperandType type = NONE;
  double d;
  char *str;
  int index, opt;
  JSValue v0;

  index = load_const_sbc(src, nconsts, &type, &d, &str, &opt);
  if (index < 0 || type == NONE) return -1;
  if (type == STR)
    decode_escape_char(str);
#ifdef USE_REGEXP
  else if (type == REX)
    decode_escape_char(str);
#endif /* USE_REGEXP */

  v0 = ctop[index];
  if (v0 == JS_UNDEFINED) {
    if (type == NUM)
      ctop[index] = double_to_number(ctx, d);
    else if (type == STR)
      ctop[index] = cstr_to_string(ctx, str);
#ifdef USE_REGEXP
    else if (type == REX) {
      Shape *os = gshapes.g_shape_RegExp;
      int flag = opt;
      ctop[index] = new_regexp_object(ctx, DEBUG_NAME("load_regexp_sbc"), os, str, flag);
    }
#endif /* USE_REGEXP */
  }
  else {
    if (type == NUM && !is_number(v0)) {
      LOG_ERR("inconsistent constants at index %d", index);
      return -1;
    }
    if (type == NUM && d != number_to_double(v0)) {
      LOG_ERR("inconsistent number constants at index %d", index);
      return -1;
    }
    if (type == STR && cstr_to_string(NULL, str) != v0) {
      LOG_ERR("inconsistent string constants at index %d", index);
      return -1;
    }
    /*
     * else, it is necessary to check the consistency of v0 and str
     * but this check in not implemented yet.
     */
  }
  return index;
}

#if defined(USE_SBC) && defined(WITH_SOURCE_LOCATION)
void load_source_location(Instruction *insn) {
  static int last_line = 0;
  static int last_column = 0;
  char *tok = next_token();
  if (tok != NULL) {
    insn->line = last_line = atoi(next_token());
    insn->column = last_column = atoi(next_token());
  } else {
    insn->line = last_line;
    insn->column = last_column;
  }
}
#define LOAD_SOURCE_LOCATION(insn) load_source_location(insn)
#else /* USE_SBC && WITH_SOURCE_LOCATION */
#define LOAD_SOURCE_LOCATION(insn)
#endif /* USE_SBC && WITH_SOURCE_LOCATION */

int insn_load_sbc(Context *ctx, Instruction *insns, JSValue *ctop,
                  int findex, int ninsns, int nconsts, int pc, int ftbase) {
  char buf[LOADBUFLEN];
  char *tokp;
  Opcode oc;

  step_load_code(buf, LOADBUFLEN);
  tokp = first_token(buf);

#ifdef PROFILE
  {
    int nlen = strlen(tokp);
    /* tests whether the instruction name ends with "_log" */
    if (nlen > 4 && tokp[nlen - 4] == '_' && tokp[nlen - 3] == 'l' && 
        tokp[nlen - 2] == 'o' && tokp[nlen - 1] == 'g' ) {
      tokp[nlen - 4] = '\0';
      INSN_CACHE(findex, pc).logflag = TRUE;
    } else
      INSN_CACHE(findex, pc).logflag = forcelog_flag;
  }
#endif /* PROFILE */

  oc = find_insn(tokp);
  if (oc == NOT_OPCODE) {
    /* instruction is not found in the instruction info table */
#ifdef PROFILE
    LOG_ERR("Illegal instruction: %s%s", tokp,
            (INSN_CACHE(findex, pc).logflag == TRUE? "_log": ""));
#else
    LOG_ERR("Illegal instruction: %s", tokp);
#endif /* PROFILE */
    insns[pc].code = (Bytecode)(-1);
    return LOAD_FAIL;
  }
  switch (insn_info_table[oc].otype) {
  case SMALLPRIMITIVE:
    {
      Register dst;
      load_register(dst, atoi(next_token()), "SMALLPRIMITIVE DST");
      switch (oc) {
      case FIXNUM:
        {
          SmallPrimitive imm;
          load_small_primitive(imm, atoi(next_token()), "FIXNUM IMM");
          insns[pc].code = makecode_fixnum(dst, imm);
        }
        break;
      case SPECCONST:
        insns[pc].code =
          makecode_specconst(dst, specstr_to_jsvalue(next_token()));
        break;
      default:
        return LOAD_FAIL;
      }
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case BIGPRIMITIVE:
    {
      Register dst;
      char *src;
      int index;
      ConstantDisplacement disp;

      dst = atoi(next_token());   /* destination register */
      switch (oc) {
      case BIGPRIM:
        {
          src = next_token();
          index = load_jsvalue_sbc(ctx, src, ctop, ninsns, nconsts);
          if (index < 0) return LOAD_FAIL;
          load_constant_displacement(disp,
                                     calc_displacement(ninsns, pc, index),
                                     "BIGPRIM DISP");
          insns[pc].code = makecode_bigprim(dst, disp);
        }
        break;
      default:
        return LOAD_FAIL;
      }
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case THREEOP:
    {
      Register op0, op1, op2;
      load_op(ctx, insn_info_table[oc].op0, op0);
      load_op(ctx, insn_info_table[oc].op1, op1);
      load_op(ctx, insn_info_table[oc].op2, op2);
      insns[pc].code = makecode_three_operands(oc, op0, op1, op2);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case TWOOP:
    {
      Register op0, op1;
      load_register(op0, atoi(next_token()), "TWO OP0");
      load_register(op1, atoi(next_token()), "TWO OP1");
      insns[pc].code = makecode_two_operands(oc, op0, op1);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case ONEOP:
    {
      Register op;
      load_register(op, atoi(next_token()), "ONE OP");
      insns[pc].code = makecode_one_operand(oc, op);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case ZEROOP:
    {
      insns[pc].code = makecode_no_operand(oc);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case UNCONDJUMP:
    {
      InstructionDisplacement disp;
      load_instruction_displacement(disp, atoi(next_token()),
                                    "UNCONDJUMP DISP");
      insns[pc].code = makecode_jump(oc, disp);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case CONDJUMP:
    {
      InstructionDisplacement disp;
      Register src;
      load_register(src, atoi(next_token()), "CONDJUMP SRC");
      load_instruction_displacement(disp, atoi(next_token()), "CONDJUMP DISP");
      insns[pc].code = makecode_condjump(oc, src, disp);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case GETVAR:
    {
      Subscript link, offset;
      Register reg;
      load_subscript(link, atoi(next_token()), "GETVAR LINK");
      load_subscript(offset, atoi(next_token()), "GETVAR OFFSET");
      load_register(reg, atoi(next_token()), "GETVAR REG");
      insns[pc].code = makecode_getvar(oc, link, offset, reg);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case SETVAR:
    {
      Subscript link, offset;
      Register reg;
      load_subscript(link, atoi(next_token()), "SETVAR LINK");
      load_subscript(offset, atoi(next_token()), "SETVAR OFFSET");
      load_register(reg, atoi(next_token()), "SETVAR REG");
      insns[pc].code = makecode_setvar(oc, link, offset, reg);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case MAKECLOSUREOP:
    {
      Register dst;
      Subscript index;
      load_register(dst, atoi(next_token()), "MAKECLOSUREOP DST");
      load_subscript(index, atoi(next_token()), "MAKECLOSUREOP INDEX");
      insns[pc].code = makecode_makeclosure(oc, dst, index + ftbase);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  case CALLOP:
    {
      /* TODO: argc is not a Register */
      Register closure, argc;
      load_register(closure, atoi(next_token()), "CALLOP CLOSURE");
      load_register(argc, atoi(next_token()), "CALLOP ARGC");
      insns[pc].code = makecode_call(oc, closure, argc);
      LOAD_SOURCE_LOCATION(&insns[pc]);
      return LOAD_OK;
    }

  default:
    {
      LOG_EXIT("Illegal instruction: %s", tokp);
      return LOAD_FAIL;
    }
  }
}
#endif /* USE_SBC */

#ifdef USE_OBC
int insn_load_obc(Context *ctx, Instruction *insns, JSValue *ctop,
                  int findex, int ninsns, int nconsts, int pc, int ftbase)
{
  unsigned char buf[sizeof(Bytecode)];
  Opcode oc;
  Bytecode bc;
  int i;

  if (fread(buf, sizeof(unsigned char), sizeof(Bytecode), file_pointer)
      != sizeof(Bytecode))
    LOG_ERR("Error: cannot read %dth bytecode", pc);
  bc = convertToBc(buf);
  oc = get_opcode(bc);

  switch (insn_info_table[oc].otype) {
  case BIGPRIMITIVE:
    switch (oc) {
    case BIGPRIM:
      {
        BigPrimitiveIndex id = get_big_subscr(bc);
        ConstantDisplacement disp = calc_displacement(ninsns, pc, id);
        insns[pc].code = update_displacement(bc, disp);
      }
      return LOAD_OK;
    default:
      return LOAD_FAIL;
    }
    break;

  case MAKECLOSUREOP:
    if (ftbase > 0) {
      Subscript index = get_second_operand_subscr(bc) + ftbase;
      bc = makecode_makeclosure(oc, get_first_operand_reg(bc), index);
    }
    insns[pc].code = bc;
    return LOAD_OK;

  case THREEOP:
    for (i = 0; i < 3; i++) {
      InsnOperandType type = si_optype(oc, i);
      if (type == OPTYPE_ERROR) return LOAD_FAIL;
      if (type == STR || type == NUM ) {
        BigPrimitiveIndex index =
          ((i == 0) ? get_first_operand_subscr(bc) :
           (i == 1) ? get_second_operand_subscr(bc) :
           get_third_operand_subscr(bc));
        ConstantDisplacement disp = calc_displacement(ninsns, pc, index);
        bc = ((i == 0)? update_first_operand_disp(bc, disp):
              (i == 1)? update_second_operand_disp(bc, disp):
              update_third_operand_disp(bc, disp));
      }
    }
    /* fall through */
  default:
    insns[pc].code = bc;
    return LOAD_OK;
  }
}
#endif


void set_function_table(FunctionTable *ftable, int index, Instruction *insns,
                        JSValue* consts, int callentry, int sendentry, int nlocals,
                        int ninsns, int nconsts) {
  if (index >= FUNCTION_TABLE_LIMIT)
    LOG_EXIT("too many functions (consider increasing FUNCTION_TABLE_LIMIT)");

  ftable[index].ilabel_created = false;
  ftable[index].insns = insns;
  ftable[index].constants = consts;
  ftable[index].index = index;
  ftable[index].call_entry = callentry;
  ftable[index].send_entry = sendentry;
  ftable[index].n_locals = nlocals;
  ftable[index].n_insns = ninsns;
  ftable[index].n_constants = nconsts;
}

uint32_t decode_escape_char(char *str) {
  char *src, *dst;
  int dq;
  char c;

  src = dst = str;
  dq = 0;
  if ((c = *src++) == '\"') {
    dq = 1;
    c = *src++;
  }
  while (1) {
    if (dq == 1 && c == '\"') break;
    if (dq == 0 && c == '\0') break;
    if (c != '\\') {
      *dst++ = c;
      c = *src++;
      continue;
    }
    switch (c = *src++) {
    case '0': *dst++ = '\0'; break;
    case 'a': *dst++ = '\a'; break;
    case 'b': *dst++ = '\b'; break;
    case 'f': *dst++ = '\f'; break;
    case 'n': *dst++ = '\n'; break;
    case 'r': *dst++ = '\r'; break;
    case 't': *dst++ = '\t'; break;
    case 'v': *dst++ = '\v'; break;
    case 's': *dst++ = ' '; break;
    case '\\': *dst++ = '\\'; break;
    case '\'': *dst++ = '\''; break;
    case '\"': *dst++ = '\"'; break;
    case 'x':
      {
        int k = 0, i;
        for (i = 0; i <= 1; i++) {
          c = *src++;
          if (c == ' ') c = '0';
          k <<= 4;
          if ('0' <= c && c <= '9') k += c - '0';
          else if ('a' <= c && c <= 'f') k += c + 10 - 'a';
          else if ('A' <= c && c <= 'F') k += c + 10 - 'A';
        }
        *dst++ = (char)k;
      }
      break;
    default: *dst++ = c; break;
    }
    c = *src++;
  }
  *dst = '\0';
  return (uint32_t)(dst - str);
}

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
