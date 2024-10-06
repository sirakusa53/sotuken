#include "prefix.h"
#define EXTERN extern
#include "header.h"

#ifdef min
#undef min
#endif /* min */
#ifdef max
#undef max
#endif /* max */
#ifdef get_stack
#undef get_stack
#endif /* get_stack */
#ifdef SUCCESS
#undef SUCCESS
#endif /* SUCCESS */

#include "mbed.h"
#include "mbed_error.h"
#include "mbed_fault_handler.h"

#ifdef SET_CPUTIME_FLAG_TRUE
static inline Timer start_timer() { Timer t; t.start(); return t; }
#endif /* SET_CPUTIME_FLAG_TRUE */

int getrusage(int who, struct rusage *usage)
{
#ifdef SET_CPUTIME_FLAG_TRUE
  static Timer t = start_timer();
  const uint64_t time = t.elapsed_time().count();
#else /* SET_CPUTIME_FLAG_TRUE */
  const uint64_t time = 0;
#endif /* SET_CPUTIME_FLAG_TRUE */

  usage->ru_utime.tv_sec = time / 1000000;
  usage->ru_utime.tv_usec = time % 1000000;
  usage->ru_stime.tv_sec = 0;
  usage->ru_stime.tv_usec = 0;

  return 0;
}


/* Error handling for MBed */
/* cite: https://os.mbed.com/docs/mbed-os/v6.12/apis/error-handling.html */
static mbed_error_status_t err_status;
static bool reboot_error_happened = false;

// Application callback function for reporting error context during boot up.
void mbed_error_reboot_callback(mbed_error_ctx *error_context)
{
    reboot_error_happened = true;
    err_status = error_context->error_status;
    mbed_reset_reboot_error_info();
}

int check_last_execution_status()
{
  if (!reboot_error_happened)
    return 0;

  if (err_status >= 0)
    return 0;

  print_end_signal();
  return 1;
}
