/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef UTIL_H
#define UTIL_H

/* ====================== */
/* Timer functions        */
/* ====================== */

/*
 * eJS Util Timer
 * for measuring total vm run time and total gc time
 */
typedef struct {
  struct rusage ruLast;
  time_t sec;
  suseconds_t usec;
} eJSUtilTimer;

static inline void Init_eJS_Util_Timer(eJSUtilTimer *pTimer);
static inline void Start_eJS_Util_Timer(eJSUtilTimer *pTimer);
static inline void Pause_eJS_Util_Timer(eJSUtilTimer *pTimer);
static inline void Resume_eJS_Util_Timer(eJSUtilTimer *pTimer);
static inline void Stop_eJS_Util_Timer(eJSUtilTimer *pTimer);

#endif /* UTIL_H */


/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
