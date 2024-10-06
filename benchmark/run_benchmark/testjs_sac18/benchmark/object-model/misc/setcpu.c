#define _GNU_SOURCE
//#include <x86intrin.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

#define CPU 2

void set_thread_affinity(int n)
{
  cpu_set_t set;
  /*
  pthread_attr_t attr;
  */

  CPU_ZERO(&set);
  CPU_SET(n, &set);

  /*
  pthread_attr_init(&attr);
  pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &set);
  */
  sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);
}

void set_boost(int enable)
{
#define BOOST_PATH_ACPI "/sys/devices/system/cpu/cpufreq/boost"
#define BOOST_PATH_PSTATE "/sys/devices/system/cpu/intel_pstate/no_turbo"
  FILE* fp;

  fp = fopen(BOOST_PATH_ACPI, "w");
  if (fp == NULL) {
    if (errno != ENOENT && errno != EACCES) {
      printf("%d\n", errno);
      perror("fopen boost (ACPI)");
      exit(1);
    }
    fp = fopen(BOOST_PATH_PSTATE, "w");
    if (fp == NULL) {
      perror("fopen boost (PSTATE)");
      exit(1);
    }
    fprintf(fp, "%d", 1-enable);
    return;
  }
  fprintf(fp, "%d", enable);
  fclose(fp);
}

void set_freq_performance(int cpu_no, int enable)
{
#define FREQ_PATH "/sys/devices/system/cpu/cpufreq/policy%d/scaling_governor"
  char fname[100];
  FILE* fp;
  sprintf(fname, FREQ_PATH, cpu_no);
  fp = fopen(fname, "w");
  if (fp == NULL) {
    perror("fopen governor");
    exit(1);
  }
  fprintf(fp, enable ? "performance" : "ondemand");
  fclose(fp);
}

void print_usage()
{
  printf("setcpu [-c <cpu id>] cmd arg ...\n");
  printf("setcpu [-c <cpu id>] off\n");
  printf("  Setcpu executes given command on the specified CPU core(defalut: 2).\n");
  printf("  Also, it disables turbo boost and frequency scaling scaling.\n");
}

int main(int argc, char* argv[])
{
  int i;
  int cpu = CPU;

  if (argc == 1) {
    print_usage();
    return 1;
  }
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-c") == 0) {
      i += 1;
      cpu = atoi(argv[i]);
    } else if (strcmp(argv[i], "-h") == 0) {
      print_usage();
      return 0;
    } else
      break;
  }

  if (strcmp(argv[i], "off") == 0) {
    set_boost(1);
    set_freq_performance(cpu, 0);
    return 0;
  }

  set_boost(0);
  set_thread_affinity(cpu);
  set_freq_performance(cpu, 1);
  usleep(1000);
  execvp(argv[i], argv + i);
  return 1;
}
