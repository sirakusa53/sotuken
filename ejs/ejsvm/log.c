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

#ifdef USE_MBED
void print_end_signal()
{
  printf("%c%c", END_CHAR, END_CHAR);
  fflush(stdout);
}
#endif /* USE_MBED */
