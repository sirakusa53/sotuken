/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#ifndef UTIL_INL_H
#define UTIL_INL_H

/* ====================== */
/* Timer functions        */
/* ====================== */

static inline void Init_eJS_Util_Timer(eJSUtilTimer *pTimer) {
  if (pTimer == NULL)
    return;

  pTimer->sec  = 0;
  pTimer->usec = 0;
}

static inline void Start_eJS_Util_Timer(eJSUtilTimer *pTimer) {
  if (pTimer == NULL)
    return;

  pTimer->sec  = 0;
  pTimer->usec = 0;

  getrusage(RUSAGE_SELF, &(pTimer->ruLast));
}

static inline void Pause_eJS_Util_Timer(eJSUtilTimer *pTimer) {
  struct rusage ruNow;
  time_t sec;
  suseconds_t usec;

  // To avoid overhead of null checking, call getrusage first.
  getrusage(RUSAGE_SELF, &ruNow);

  if (pTimer == NULL)
    return;

  calc_rusage_duration(&sec, &usec, &(pTimer->ruLast), &ruNow);
  sec  += pTimer->sec;
  usec += pTimer->usec;

  if (usec >= 1000000) {
    usec -= 1000000;
    ++sec;
  }

  pTimer->sec  = sec;
  pTimer->usec = usec;
}

static inline void Resume_eJS_Util_Timer(eJSUtilTimer *pTimer) {
  if (pTimer == NULL)
    return;

  getrusage(RUSAGE_SELF, &(pTimer->ruLast));
}

static inline void Stop_eJS_Util_Timer(eJSUtilTimer *pTimer) {
  Pause_eJS_Util_Timer(pTimer);
}

#endif /* UTIL_INL_H */


/* Local Variables:      */
/* mode: c               */
/* c-basic-offset: 2     */
/* indent-tabs-mode: nil */
/* End:                  */
