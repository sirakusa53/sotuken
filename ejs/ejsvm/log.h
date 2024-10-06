/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef LOG_H_
#define LOG_H_

#ifdef USE_MBED
#define END_CHAR ((char) 0x04) /* End-Of-Transmission */

#define PRINT_END() print_end_signal()

#ifdef MBED_SILENT
#define PRINT_END_MSG(...) print_end_signal()
#else /* MBED_SILENT */
#define PRINT_END_MSG(...) do { printf( __VA_ARGS__ ); print_end_signal(); } while(0)
#endif /* MBED_SILENT */

#else /* USE_MBED */
#define PRINT_END() do { fflush(stdout) ; fflush(stderr);} while (0)
#define PRINT_END_MSG(...) do { PRINT_END(); } while(0)
#endif /* USE_MBED */

#if defined(COCCINELLE_CHECK)

#define LOG(...)
#define LOG_FUNC
#define LOG_ERR(...) return
#define LOG_EXIT(...) return
#define LOG_EXIT2(context, ...) return
#define LOG_ASSERT_NOT_REACHED() return
#define LOG_ASSERT_NOT_IMPLEMENTED() return

#define ASSERT_OBJECT(o)

#elif defined(DEBUG_PRINT)

#define LOG(...) fprintf(log_stream, __VA_ARGS__)
#define LOG_FUNC fprintf(log_stream, "%-16s: ", __func__)
#define LOG_ERR(...)                                    \
  do { LOG_FUNC; fprintf(log_stream, __VA_ARGS__);      \
    putc('\n', log_stream); }                           \
  while (0)

#ifdef DEBUG
#define LOG_EXIT(...)                           \
  do {                                          \
    LOG_FUNC;                                   \
    fprintf(log_stream, __VA_ARGS__);           \
    putc('\n', log_stream);                     \
    PRINT_END();                                \
    abort();                                    \
  } while (0)
#define LOG_EXIT2(context, ...)                 \
  do {                                          \
    LOG_FUNC;                                   \
    fprintf(log_stream, __VA_ARGS__);           \
    putc('\n', log_stream);                     \
    print_backtrace(context);                   \
    PRINT_END();                                \
    abort();                                    \
  } while (0)
#else /* DEBUG */
#define LOG_EXIT(...)                           \
  do {                                          \
    LOG_FUNC;                                   \
    fprintf(log_stream, __VA_ARGS__);           \
    putc('\n', log_stream);                     \
    PRINT_END();                                \
    exit(1);                                    \
  } while (0)
#define LOG_EXIT2(context, ...)                 \
  do {                                          \
    LOG_FUNC;                                   \
    fprintf(log_stream, __VA_ARGS__);           \
    putc('\n', log_stream);                     \
    print_backtrace(context);                   \
    PRINT_END();                                \
    abort();                                    \
  } while (0)
#endif /* DEBUG */

#define LOG_ASSERT_NOT_REACHED()          \
  do {                                    \
    LOG_EXIT("Unexpected code path");     \
  } while (0)
#define LOG_ASSERT_NOT_IMPLEMENTED()      \
  do {                                    \
    LOG_EXIT("Not implemented yet");      \
  } while (0)

#define ASSERT_OBJECT(o) do {                               \
    if (!is_object(o))                                      \
      LOG_EXIT("assertion failed. not an object.");         \
  } while (0)

#else

#define LOG(...) do { } while (0)
#define LOG_FUNC
#define LOG_ERR(...) do { PRINT_END_MSG( __VA_ARGS__ ); } while (0)
#define LOG_EXIT(...) do { PRINT_END_MSG( __VA_ARGS__ ); exit(1); } while (0)
#define LOG_EXIT2(context, ...) do { PRINT_END(); exit(1); } while(0)
#define LOG_ASSERT_NOT_REACHED() do { LOG_EXIT("Unexpected code path"); } while (0)
#define LOG_ASSERT_NOT_IMPLEMENTED() do { LOG_EXIT("Not implemented yet"); } while (0)

#define ASSERT_OBJECT(o) do { } while (0)

#endif /* DEBUG */

#endif /* LOG_H_ */

/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
