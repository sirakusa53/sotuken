/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include "prefix.h"
#define EXTERN
#include "header.h"

/*
 *  phase
 */
int run_phase;         /* PHASE_INIT or PHASE_VMLOOP */

/*
 * flags
 */
int ftable_flag;       /* prints the function table */
int trace_flag;        /* prints every excuted instruction */
int lastprint_flag;    /* prints the result of the last expression */
int all_flag;          /* all flag values are true */
int cputime_flag;      /* prints the cpu time */
#ifndef USE_EMBEDDED_INSTRUCTION
int repl_flag;         /* for REPL */
#endif /* USE_EMBEDDED_INSTRUCTION */
#ifdef HC_PROF
int hcprint_flag;      /* prints all transitive hidden classes */
#endif /* HC_PROF */
#ifdef PROFILE
int profile_flag;      /* print the profile information */
char *poutput_name;    /* name of logging file */
int coverage_flag;     /* print the coverage */
int icount_flag;       /* print instruction count */
int forcelog_flag;     /* treat every instruction as ``_log'' one */
int countuniq_flag;    /* Only one profiling output for each instruction calls */
char *bpoutput_name;   /* name of logging file for builtin functions */
#endif
#ifdef ICC_PROF
char *iccprof_name;    /* name of instruction-call-count profile file */
#endif /* ICC_PROF */
#ifdef GC_PROF
int gcprof_flag;       /* print GC profile information */
#endif /* GC_PROF */
#ifdef IC_PROF
int icprof_flag;
#endif /* IC_PROF */
#ifdef AS_PROF
int asprof_flag;
#endif /* AS_PROF */
#ifdef DUMP_HCG
char *dump_hcg_file_name;
#endif /* DUMP_HCG */
#ifdef LOAD_HCG
char *load_hcg_file_name;
#endif /* LOAD_HCG */
#ifdef PRINT_BUILD_INFO
int build_info_flag;
#endif /* PRINT_BUILD_INFO */


/*
#define DEBUG_TESTTEST
*/

#if defined(USE_OBC) && defined(USE_SBC)
int obcsbc;
#endif

FILE *log_stream;
#ifdef PROFILE
FILE *prof_stream;
FILE *bprof_stream;
#endif
#ifdef ICC_PROF
FILE *iccprof_fp;
#endif /* ICC_PROF */

/*
 * parameter
 */
int regstack_limit = STACK_LIMIT; /* size of register stack in # of JSValues */
#ifdef USE_MBED
/* Decide heap size by __jsheap_start/end, but it is not constant, so initialize at int main(int, char*). */
int heap_limit = 0;
#else /* USE_MBED */
#ifdef JS_SPACE_BYTES
int heap_limit = JS_SPACE_BYTES; /* heap size in bytes */
#else /* JS_SPACE_BYTES */
int heap_limit = 1 * 1024 * 1024;
#endif /* JS_SPACE_BYTES */
#endif /* USE_MBED */
int gc_threshold = -1; /* set in process_options */

eJSUtilTimer *eJSTimer_Mutator = NULL;
eJSUtilTimer *eJSTimer_GC = NULL;

#ifdef CALC_CALL
static uint64_t callcount = 0;
#endif

#define pp(v) (print_value_verbose(cxt, (v)), putchar('\n'))

/*
 * processes command line options
 */
struct commandline_option {
  const char *str;
  int arg;
  int *flagvar;
  char **strvar;
};

struct commandline_option  options_table[] = {
  { "-l",         0, &lastprint_flag, NULL          },
#ifdef DEBUG
  { "-f",         0, &ftable_flag,    NULL          },
#endif /* DEBUG */
  { "-t",         0, &trace_flag,     NULL          },
  { "-a",         0, &all_flag,       NULL          },
  { "-u",         0, &cputime_flag,   NULL          },
#ifndef USE_EMBEDDED_INSTRUCTION
  { "-R",         0, &repl_flag,      NULL          },
#endif /* USE_EMBEDDED_INSTRUCTION */
#ifdef HC_PROF
  { "--hc-prof",  0, &hcprint_flag,   NULL          },
#endif /* HC_PROF */
#ifdef PROFILE
  { "--profile",  0, &profile_flag,   NULL           },
  { "--poutput",  1, NULL,            &poutput_name  },
  { "--coverage", 0, &coverage_flag,  NULL           },
  { "--icount",   0, &icount_flag,    NULL           },
  { "--forcelog", 0, &forcelog_flag,  NULL           },
  { "--pcntuniq", 0, &countuniq_flag, NULL           },
  { "--bpoutput", 1, NULL,            &bpoutput_name },
#endif /* PROFILE */
#ifdef ICC_PROF
  { "--iccprof",  1, NULL,            &iccprof_name },
#endif /* ICC_PROF */
#ifdef GC_PROF
  { "--gc-prof",  0, &gcprof_flag,    NULL          },
#endif /* GC_PROF */
#ifdef IC_PROF
  { "--ic-prof",  0, &icprof_flag,    NULL          },
#endif /* IC_PROF */
#ifdef AS_PROF
  { "--as-prof",  0, &asprof_flag,    NULL          },
#endif /* AS_PROF */
  { "-m",         1, &heap_limit,     NULL          },
  { "--threshold",1, &gc_threshold,   NULL          },
  { "-s",         1, &regstack_limit, NULL          },
#ifdef DUMP_HCG
  { "--dump-hcg", 1, NULL,            &dump_hcg_file_name },
#endif /* DUMP_HCG */
#ifdef LOAD_HCG
  { "--load-hcg", 1, NULL,            &load_hcg_file_name },
#endif /* LOAD_HCG */
#ifdef PRINT_BUILD_INFO
  { "--buildinfo",0, &build_info_flag,NULL          },
#endif /* PRINT_BUILD_INFO */
  { (char *)NULL, 0, NULL,            NULL          }
};

int process_options(int ac, char *av[]) {
  int k;
  char *p;
  struct commandline_option *o;

  k = 1;
  p = av[1];
  while (k < ac) {
    if (p[0] == '-') {
      o = &options_table[0];
      while (o->str != (char *)NULL) {
        if (strcmp(p, o->str) == 0) {
          if (o->arg == 0) *(o->flagvar) = TRUE;
          else {
            k++;
            p = av[k];
            if (o->flagvar != NULL) *(o->flagvar) = atoi(p);
            else if (o->strvar != NULL) *(o->strvar) = p;
          }
          break;
        } else
          o++;
      }
      if (o->str == (char *)NULL)
        fprintf(stderr, "unknown option: %s\n", p);
      k++;
      p = av[k];
    } else
      break;
  }

  return k;
}

void clear_commandline_option() {
  size_t len = sizeof(options_table) / sizeof(options_table[0]);
  size_t i;

  for (i = 0; i < len; ++i) {
    struct commandline_option *option = &(options_table[i]);
    if (option->flagvar != NULL) {
      if (option->arg == 0)
        *(option->flagvar) = FALSE;
      else
        /* Nothing to do : use default value */ (void) 0;
    }
    if (option->strvar != NULL) {
      *(option->strvar) = NULL;
    }
  }
}

#ifdef PRINT_BUILD_INFO
void print_build_info() {
  printf("==== Build Info ====\n");
  printf("Date : %s\n", __DATE__);
  printf("Time : %s\n", __TIME__);

#ifdef USE_EMBEDDED_INSTRUCTION
  printf("EMBEDDED_INSTRUCTION : true\n");
  printf("JS_SRC_PATH : %s\n", JS_SRC_PATH);
#else /* USE_EMBEDDED_INSTRUCTION */
  printf("EMBEDDED_INSTRUCTION : false\n");
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef USE_OBC
  printf("OBC support : true\n");
#else /* USE_OBC */
  printf("OBC support : false\n");
#endif /* USE_OBC */

#ifdef USE_SBC
  printf("SBC support : true\n");
#else /* USE_OBC */
  printf("SBC support : false\n");
#endif /* USE_OBC */

#ifdef MARKSWEEP
#ifdef FREELIST
  printf("Using freelist Mark-Sweep GC with :\n");
#ifdef GC_MS_HEADER32
  printf("  GC_MS_HEADER32\n");
#endif /* GC_MS_HEADER32 */
#endif /* FREELIST */
#ifdef BIBOP
  printf("Using BiBoP Mark-Sweep GC with :\n");
#ifdef BIBOP_CACHE_BMP_GRANULES
  printf("  BIBOP_CACHE_BMP_GRANULES\n");
#endif /* BIBOP_CACHE_BMP_GRANULES */
#ifdef BIBOP_SEGREGATE_1PAGE
  printf("  BIBOP_SEGREGATE_1PAGE\n");
#endif /* BIBOP_SEGREGATE_1PAGE */
#ifdef BIBOP_2WAY_ALLOC
  printf("  BIBOP_2WAY_ALLOC\n");
#endif /* BIBOP_2WAY_ALLOC */
#ifdef BIBOP_FREELIST
  printf("  BIBOP_FREELIST\n");
#endif /* BIBOP_FREELIST */
#ifdef FLONUM_SPACE
  printf("  FLONUM_SPACE\n");
#endif /* FLONUM_SPACE */
#ifdef VERIFY_BIBOP
  printf("  VERIFY_BIBOP\n");
#endif /* VERIFY_BIBOP */
#endif /* BIBOP */
#endif /* MARKSWEEP */

#ifdef JONKERS
  printf("Using jonkers compctor with :\n");
#ifdef GC_JONKERS_HEADER32
  printf("  GC_JONKERS_HEADER32\n");
#endif /* GC_JONKERS_HEADER32 */
#ifdef GC_JONKERS_USING_QUEUE
  printf("  GC_JONKERS_USING_QUEUE\n");
#endif /* GC_JONKERS_USING_QUEUE */
#ifdef GC_JONKERS_SEPARATE_META_SIZE
  printf("  GC_JONKERS_SEPARATE_META_SIZE = %u (0z%x)\n", GC_JONKERS_SEPARATE_META_SIZE, GC_JONKERS_SEPARATE_META_SIZE);
#endif /* GC_JONKERS_SEPARATE_META_SIZE */
#endif /* JONKERS */

#ifdef FUSUMA
  printf("Using fusuma compctor with :\n");
#ifdef GC_FUSUMA_HEADER32
  printf("  GC_FUSUMA_HEADER32\n");
#endif /* GC_FUSUMA_HEADER32 */
#ifdef GC_FUSUMA_BOUNDARY_TAG
  printf("  GC_FUSUMA_BOUNDARY_TAG\n");
#endif /* GC_FUSUMA_BOUNDARY_TAG */
#endif /* FUSUMA */

#ifdef LISP2
  printf("Using Lisp2 compctor with :\n");
#ifdef GC_LISP2_HEADER32
  printf("  GC_LISP2_HEADER32\n");
#endif /* GC_LISP2_HEADER32 */
#endif /* LISP2 */

#ifdef COPYGC
  printf("Using Semi-Space Copy GC with :\n");
#endif /* COPY */

#ifdef MARK_STACK
  printf("  MARK_STACK\n");
#endif /* MARK_STACK */

  printf("\n");

  printf("HeapSize     = %9d (0x%08x) [Byte]\n", heap_limit, heap_limit);
  printf("GC Threshold = %9d (0x%08x) [Byte]\n", gc_threshold, gc_threshold);

  printf("====================\n");
}
#endif /* PRINT_BUILD_INFO */

void print_cputime(time_t sec, suseconds_t usec, time_t gc_sec, suseconds_t gc_usec, int gc_cnt) {
  const int l_total_msec = sec * 1000 + usec / 1000;
  const int l_total_usec = usec % 1000;
  const int l_gc_msec    = gc_sec * 1000 + gc_usec / 1000;
  const int l_gc_usec    = gc_usec % 1000;
  printf("total CPU time = %d.%03d msec, total GC time =  %d.%03d msec (#GC = %d)\n",
         l_total_msec, l_total_usec, l_gc_msec, l_gc_usec, gc_cnt);
}

#ifdef GC_PROF
void print_gc_prof()
{
  int i;
  uint64_t total_live_bytes = 0;
  uint64_t total_live_count = 0;
  uint64_t total_collect_bytes = 0;
  uint64_t total_collect_count = 0;

  for (i = 0; i <= NUM_DEFINED_CELL_TYPES; i++) {
    total_live_bytes += pertype_live_bytes[i];
    total_live_count += pertype_live_count[i];
    total_collect_bytes += pertype_collect_bytes[i];
    total_collect_count += pertype_collect_count[i];
  }

  printf("GC: %" PRId64 " %" PRId64 " ", total_alloc_bytes, total_alloc_count);
  printf("%" PRId64 " %" PRId64 " ",
         generation > 1 ? total_live_bytes / (generation - 1) : 0,
         generation > 1 ? total_live_count / (generation - 1) : 0);
  printf(" %" PRId64 " %" PRId64 " ", total_collect_bytes, total_collect_count);
  printf("%" PRId64 " %" PRId64 " ",
         generation > 1 ? total_collect_bytes / (generation - 1) : 0,
         generation > 1 ? total_collect_count / (generation - 1) : 0);
  for (i = 0; i <= NUM_DEFINED_CELL_TYPES; i++) {
    printf(" %" PRId64 " ", pertype_alloc_max[i]);
    printf(" %" PRId64 " ", pertype_alloc_bytes[i]);
    printf(" %" PRId64 " ", pertype_alloc_count[i]);
    printf(" %" PRId64 " ",
           generation > 1 ? pertype_live_bytes[i] / (generation - 1) : 0);
    printf(" %" PRId64 " ",
           generation > 1 ? pertype_live_count[i] / (generation - 1) : 0);
    printf(" %" PRId64 " ", pertype_collect_bytes[i]);
    printf(" %" PRId64 " ", pertype_collect_count[i]);
    printf(" %" PRId64 " ",
           generation > 1 ? pertype_collect_bytes[i] / (generation - 1) : 0);
    printf(" %" PRId64 " ",
           generation > 1 ? pertype_collect_count[i] / (generation - 1) : 0);
  }
  printf("\n");

  printf("total alloc bytes = %" PRId64 "\n", total_alloc_bytes);
  printf("total alloc count = %" PRId64 "\n", total_alloc_count);
  printf("total collect bytes = %" PRId64 "\n", total_collect_bytes);
  printf("total collect count = %" PRId64 "\n", total_collect_count);
  for (i = 0; i < 255; i++)
    if (pertype_alloc_count[i] > 0) {
      printf("  type %02x ", i);
      printf("a.max = %7" PRId64 " ", pertype_alloc_max[i]);
      printf("a.bytes = %7" PRId64 " ", pertype_alloc_bytes[i]);
      printf("a.count = %5" PRId64 " ", pertype_alloc_count[i]);
      printf("l.bytes = %7" PRId64 " ",
             generation > 1 ? pertype_live_bytes[i] / (generation - 1) : 0);
      printf("l.count = %4" PRId64 " ",
             generation > 1 ? pertype_live_count[i] / (generation - 1) : 0);
      printf("%s\n", CELLT_NAME(i));
    }
}
#endif /* GC_PROF */

#ifdef PROFILE
void print_coverage(FunctionTable *ft) {
  unsigned int loginsns = 0; /* number of logflag-set instructiones */
  unsigned int einsns = 0;   /* number of executed logflag-set instructions */
  size_t i; int j;

  size_t len = get_function_table_length(function_table);

  for (i = 0; i < len; i++) {
    int ninsns = ft[i].n_insns;
    for (j = 0; j < ninsns; j++) {
      if (INSN_CACHE(i, j).logflag == TRUE) {
        loginsns++;
        if (INSN_CACHE(i, j).count > 0) einsns++;
      }
    }
  }
  printf("coverage of logflag-set instructions = %d/%d", einsns, loginsns);
  if (loginsns > 0)
    printf(" = %7.3f%%", (double)einsns * 100 / (double)loginsns);
  putchar('\n');
}

void print_icount(FunctionTable *ft) {
  size_t i; int j, k;
  unsigned int *ic;
  size_t len = get_function_table_length(function_table);

  if ((ic = (unsigned int *)malloc(sizeof(unsigned int) * numinsts)) == NULL) {
    fprintf(stderr, "Allocating instruction count table failed\n");
    return;
  }
  for (k = 0; k < numinsts; k++) ic[k] = 0;

  for (i = 0; i < len; i++) {
    Instruction *insns = ft[i].insns;
    int ninsns = ft[i].n_insns;
    for (j = 0; j < ninsns; j++)
      if (INSN_CACHE(i, j).logflag == TRUE)
        ic[(int)(get_opcode(insns[j].code))] += INSN_CACHE(i, j).count;
  }

  printf("instruction count\n");
  for (k = 0; k < numinsts; k++)
    printf("%3d: %10d  %s\n", k, ic[k], insn_nemonic(k));

  free(ic);
}
#endif

#if defined(USE_OBC) && defined(USE_SBC)
/*
 * If the name ends with ".sbc", file_type returns FILE_SBC;
 * otherwise, returns FILE_OBC.
 */
int file_type(char *name) {
  int nlen = strlen(name);

  if (nlen >= 5 && name[nlen - 4] == '.' && name[nlen - 3] == 's' &&
      name[nlen - 2] == 'b' && name[nlen - 1] == 'c')
    return FILE_SBC;
  return FILE_OBC;
}
#endif

static void set_flags_state_build_option(void) {
#ifdef SET_LASTPRINT_FLAG_TRUE
  lastprint_flag = TRUE;
#endif /* SET_LASTPRINT_FLAG_TRUE */

#if defined(DEBUG) && defined(SET_FTABLE_FLAG_TRUE)
  ftable_flag = TRUE;
#endif /* defined(DEBUG) && defined(SET_FTABLE_FLAG_TRUE) */

#ifdef SET_TRACE_FLAG_TRUE
  trace_flag = TRUE;
#endif /* SET_TRACE_FLAG_TRUE */

#ifdef SET_CPUTIME_FLAG_TRUE
  cputime_flag = TRUE;
#endif /* SET_CPUTIME_FLAG_TRUE */

#if defined(GC_PROF) && defined(SET_GCPROF_FLAG_TRUE)
  gcprof_flag = TRUE;
#endif /* defined(GC_PROF) && defined(SET_GCPROF_FLAG_TRUE) */

#if defined(IC_PROF) && defined(SET_ICPROF_FLAG_TRUE)
  icprof_flag = TRUE;
#endif /* defined(IC_PROF) && defined(SET_ICPROF_FLAG_TRUE) */

#if defined(AS_PROF) && defined(SET_ASPROF_FLAG_TRUE)
  asprof_flag = TRUE;
#endif /* defined(AS_PROF) && defined(SET_ASPROF_FLAG_TRUE) */

#if defined(PRINT_BUILD_INFO) && defined(SET_BUILD_INFO_FLAG_TRUE)
  build_info_flag = TRUE;
#endif /* defined(PRINT_BUILD_INFO) && defined(SET_BUILD_INFO_FLAG_TRUE) */
}

void set_related_flags_state() {
  if (all_flag == TRUE) {
    lastprint_flag = ftable_flag = trace_flag = TRUE;
#ifdef PROFILE
    coverage_flag = icount_flag = TRUE;
#endif
  }

#ifndef USE_EMBEDDED_INSTRUCTION
  if (repl_flag == TRUE)
    lastprint_flag = TRUE;
#endif /* USE_EMBEDDED_INSTRUCTION */

  /* If GC threshold is not given, use GC default */
  if (gc_threshold == -1)
    gc_threshold = DEFAULT_GC_THRESHOLD(heap_limit);
}

void init_stream(void) {
  log_stream = stderr;

#ifdef PROFILE
  if (poutput_name == NULL)
    prof_stream = stdout;
  else if ((prof_stream = fopen(poutput_name, "w")) == NULL) {
    fprintf(stderr, "Opening prof file %s failed. Instead stdout is used.\n",
            poutput_name);
    prof_stream = stdout;
  }
  if (bpoutput_name == NULL)
    bprof_stream = stdout;
  else if ((bprof_stream = fopen(bpoutput_name, "w")) == NULL) {
    fprintf(stderr, "Opening builtin functions prof file %s failed. Instead stdout is used.\n",
            bpoutput_name);
    bprof_stream = stdout;
  }
#endif
#ifdef ICC_PROF
  if(iccprof_name != NULL){
    if ((iccprof_fp = fopen(iccprof_name, "w")) == NULL)
      fprintf(stderr, "Opening prof file %s failed.\n", iccprof_name);
  }
#endif /* ICC_PROF */
}

void init_vm(Context *context) {
  init_string_table(STRING_TABLE_SIZE);

#ifdef USE_EMBEDDED_INSTRUCTION
  load_string_from_function_table(context, function_table);
#ifdef NEED_INSTRUCTION_CACHE
  {
    size_t size = get_function_table_length(function_table);
    init_instruction_cache_list(size);
  }
  {
    FunctionTable *p;
    for (p = function_table; p->insns != NULL; ++p)
      init_instruction_cache(p->index, p->n_insns);
  }
#endif /* NEED_INSTRUCTION_CACHE */
#else /* USE_EMBEDDED_INSTRUCTION */
  init_function_table_list(function_table, FUNCTION_TABLE_LIMIT);
#ifdef NEED_INSTRUCTION_CACHE
  init_instruction_cache_list(FUNCTION_TABLE_LIMIT);
#endif /* NEED_INSTRUCTION_CACHE */
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef LOAD_HCG
  if (load_hcg_file_name != NULL)
    load_hcg(context, load_hcg_file_name);
#endif /* LOAD_HCG */
  
  init_global_constants();
  init_meta_objects(context);
  init_global_objects(context);
  reset_context(context, function_table, 0);
  context->global = gconsts.g_global;
}

#ifndef USE_EMBEDDED_INSTRUCTION
int load_bc(FILE *fp, Context *context, FunctionTable *ftable) {
  int base_function = (int) get_function_table_length(ftable);
  int nf;

  init_code_loader(fp);
  nf = code_loader(context, ftable, base_function);
  end_code_loader();

  if (nf > 0)
    return base_function;
  else if (fp != stdin) {
    LOG_ERR("code_loader returns %d\n", nf);
    return -1;
  } else
    /* stdin is closed possibly by pressing ctrl-D */
    return -2;
}
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifndef USE_EMBEDDED_INSTRUCTION
FILE *open_bc_file(int k ,int argc, char **argv) {
  /* If input program is given from a file, fp is set to NULL. */
  FILE *fp = NULL;

#if defined(USE_OBC) && defined(USE_SBC)
  obcsbc = FILE_OBC;
#endif
  if (k >= argc)
    fp = stdin;   /* stdin always use OBC */
  else {
    if ((fp = fopen(argv[k], "r")) == NULL)
      LOG_EXIT("%s: No such file.\n", argv[k]);
#if defined(USE_OBC) && defined(USE_SBC)
    obcsbc = file_type(argv[k]);
#endif
  }

  return fp;
}
#endif /* USE_EMBEDDED_INSTRUCTION */

void print_prof_result(Context *context) {
#ifdef HC_PROF
  if (hcprint_flag == TRUE)
    hcprof_print_all_hidden_class();
#endif /* HC_PROF */
#ifdef IC_PROF
  if (icprof_flag) {
    extern void print_ic_prof(Context *ctx);
    print_ic_prof(context);
  }
#endif /* IC_PROF */
#ifdef AS_PROF
  if (asprof_flag) {
    extern void print_as_prof(Context *ctx);
    print_as_prof(context);
  }
#endif /* AS_PROF */
#ifdef DUMP_HCG
  if (dump_hcg_file_name != NULL) {
    extern void dump_hidden_classes(char *, Context*);
    dump_hidden_classes(dump_hcg_file_name, context);
  }
#endif /* DUMP_HCG */
#ifdef PROFILE
  if (coverage_flag == TRUE)
    print_coverage(function_table);
  if (icount_flag == TRUE)
    print_icount(function_table);
  if (prof_stream != NULL)
    fclose(prof_stream);
  if (bprof_stream != NULL)
    fclose(bprof_stream);
#endif /* PROFILE */
#ifdef ICC_PROF
  if(iccprof_fp != NULL){
    write_icc_profile(iccprof_fp);
    fclose(iccprof_fp);
  }
#endif /* ICC_PROF */
}

#ifdef USE_PAPI
void log_papi_values(long long *values, int eventsize);
  if (eventsize > 0) {
    int i;
    for (i = 0; i < eventsize; i++)
      LOG("%" PRId64 "\n", values[i]);

    LOG("%15.15e\n", ((double)values[1]) / (double)values[0]);
    LOG("L1 Hit Rate:%lf\n",
        ((double)values[0])/((double)values[0] + values[1]));
    LOG("L2 Hit Rate:%lf\n",
        ((double)values[2])/((double)values[2] + values[3]));
    LOG("L3 Hit Rate:%lf\n",
        ((double)values[4])/((double)values[4] + values[5]));
  }
}
#endif /* USE_PAPI */

/*
 * main function
 */
int ejs_main_func(int argc, char *argv[]) {
  eJSUtilTimer timerMutator, timerGC;
  int k, iter;
  Context *context = NULL;

#ifdef CALC_TIME
  long long s, e;
#endif

#ifdef USE_PAPI

#ifdef CALC_MSP
  int events[] = {PAPI_BR_MSP};
#elif defined CALC_ICM
  int events[] = {PAPI_L1_ICM, PAPI_L2_ICM};
#elif defined CALC_TCM
  int events[] = {PAPI_L1_TCM, PAPI_L2_TCM};
#else
  int events[] = {};
#endif

  int eventsize = sizeof(events)/sizeof(int);
  long long *values = malloc(sizeof(long long) * eventsize);
#endif /* USE_PAPI */

  clear_commandline_option();
  set_flags_state_build_option();

#ifdef USE_MBED
  if (check_last_execution_status())
    return 0;

  k = 0;

  heap_limit = (int) ((uintptr_t) &__jsheap_end - (uintptr_t) &__jsheap_start);
  gc_threshold = DEFAULT_GC_THRESHOLD(heap_limit);
#else /* USE_MBED */
  k = process_options(argc, argv);
#endif /* USE_MBED */

  set_related_flags_state();

  /* set number of iterations */
#ifdef USE_EMBEDDED_INSTRUCTION
  iter = k + 1;
#else /* USE_EMBEDDED_INSTRUCTION */
  iter = (repl_flag == TRUE)? 0x7fffffff: argc;
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef CALC_CALL
  callcount = 0;
#endif

  init_stream();

  if (cputime_flag == TRUE) {
    eJSTimer_Mutator = &timerMutator;
    eJSTimer_GC    = &timerGC;
  }

  run_phase = PHASE_INIT;

#ifdef PRINT_BUILD_INFO
  if (build_info_flag)
    print_build_info();
#endif /* PRINT_BUILD_INFO */

#ifdef USE_BOEHMGC
  GC_INIT();
#endif
  init_memory(heap_limit, gc_threshold);

  init_context(regstack_limit, &context);

  init_vm(context);

#ifndef NO_SRAND
  srand((unsigned)time(NULL));
#endif /* NO_SRAND */

  for (; k < iter; k++) {
    int base_function = 0;

#ifndef USE_EMBEDDED_INSTRUCTION
    FILE *fp = open_bc_file(k, argc, argv);
    base_function = load_bc(fp, context, function_table);
    if (base_function == -1)
      continue;
    else if (base_function < -1)
      break;
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef LOAD_HCG
    if (run_phase == PHASE_INIT && load_hcg_file_name != NULL)
      install_pretransition_hidden_class();
#endif /* LOAD_HCG */

    /* obtains the time before execution */
#ifdef USE_PAPI
    if (eventsize > 0) {
      int papi_result = PAPI_start_counters(events, eventsize);
      if (papi_result != 0)
        LOG_EXIT("papi failed:%d\n", papi_result);
    }
#endif /* USE_PAPI */

#ifdef CALC_TIME
    s = PAPI_get_real_usec();
#endif

    Init_eJS_Util_Timer(eJSTimer_Mutator);
    Init_eJS_Util_Timer(eJSTimer_GC);

    /* enters the VM loop */
    run_phase = PHASE_VMLOOP;
    Start_eJS_Util_Timer(eJSTimer_Mutator);

    reset_context(context, function_table, base_function);
    enable_gc(context);
    vmrun_threaded(context, 0);

    Stop_eJS_Util_Timer(eJSTimer_Mutator);

    /* obtains the time after execution */
#ifdef CALC_TIME
    e = PAPI_get_real_usec();
#endif

#ifdef USE_PAPI
    if (eventsize > 0)
      PAPI_stop_counters(values, eventsize);
#endif

#ifndef USE_PAPI
#ifndef CALC_TIME
#ifndef CALC_CALL

    if (lastprint_flag == TRUE)
      debug_print(context, 0);

#endif /* CALC_CALL */
#endif /* CALC_TIME */
#endif /* USE_PAPI */

#ifdef USE_PAPI
    log_papi_values(values, eventsize);
#endif /* USE_PAPI */

#ifdef CALC_TIME
    LOG("%" PRId64 "\n", e - s);
#endif

#ifdef CALC_CALL
    LOG("%" PRId64 "\n", callcount);
#endif

#ifdef FLONUM_PROF
    {
      extern void double_hash_flush(void);
      double_hash_flush();
    }
#endif /* FLONUM_PROF */

    if (cputime_flag == TRUE) {
      time_t          sec = eJSTimer_Mutator->sec + eJSTimer_GC->sec;
      suseconds_t    usec = eJSTimer_Mutator->usec + eJSTimer_GC->usec;

      if (usec >= 1000000) {
        usec -= 1000000;
        ++sec;
      }

      time_t       gc_sec = eJSTimer_GC->sec;
      suseconds_t gc_usec = eJSTimer_GC->usec;
      print_cputime(sec, usec, gc_sec, gc_usec, generation - 1);
    }

#ifdef GC_PROF
    if (gcprof_flag == TRUE)
      print_gc_prof();
#endif /* GC_PROF */

#ifndef USE_EMBEDDED_INSTRUCTION
    if (repl_flag == TRUE) {
      printf("\xff");
      fflush(stdout);
    }
#endif /* USE_EMBEDDED_INSTRUCTION */
  }

  print_prof_result(context);

  PRINT_END();

  return 0;
}

/*
 * default entry point
 */
#ifndef NO_NEED_ENTRY_POINT
int main(int argc, char *argv[]) {
  return ejs_main_func(argc, argv);
}
#endif /* NO_NEED_ENTRY_POINT */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
