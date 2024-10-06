/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DEFAULT_PROMPT           "eJSi> "
#define DEFAULT_EJSVM            "./ejsvm"
#define DEFAULT_EJSVM_SPEC       "./ejsvm.spec"
#define DEFAULT_EJSC_RUNTIME_NODE     "node"
#define DEFAULT_EJSC_RUNTIME_JAVA     "java"
#define DEFAULT_EJSC_RUNTIME_ARG_NODE "../ejsc/js/ejsc.js"
#define DEFAULT_EJSC_RUNTIME_ARG_JAVA "-jar"
#define DEFAULT_EJSC_JAR        "./ejsc.jar"
#define DEFAULT_TMPDIR          "/tmp"

char *prompt, *ejsvm, *ejsc_runtime, *ejsc_runtime_arg, *ejsc_jar, *ejsvm_spec, *tmpdir;
int help, verbose, legacy;

#define BUFLEN 1024

char frontend_buf[BUFLEN + 1];
char ejsc_command[BUFLEN + 1];
unsigned char output_buf[BUFLEN + 1];

#define N_TMPJS    128

char tmpjs_filename[N_TMPJS];
char tmpjson_filename[N_TMPJS];
char tmpobc_filename[N_TMPJS];

#define R (0)
#define W (1)

#define TRUE   1
#define FALSE  0

int pipe_p2c[2];
int pipe_c2p[2];

struct commandline_option {
  char *short_key;
  char *long_key;
  int arg;
  int *flagvar;
  char **strvar;
  char *info;
};

struct commandline_option options_table[] = {
  { "-h", "--help",     0, &help,           NULL,
    "Print this message." },
  { "-p", "--prompt",   1, NULL,            &prompt,
    "Set prompt string (Default : \"" DEFAULT_PROMPT "\")." },
  { "-v", "--ejsvm",    1, NULL,            &ejsvm,
    "Set ejsvm path (Default : \"" DEFAULT_EJSVM "\")." },
  { "-r", "--runtime",  1, NULL,            &ejsc_runtime,
    "Select ejsc backend (\"" DEFAULT_EJSC_RUNTIME_NODE "\" or \"" DEFAULT_EJSC_RUNTIME_JAVA "\";"
    " Default : \"" DEFAULT_EJSC_RUNTIME_NODE "\")." },
  { "-a", "--runtime-arg", 1, NULL,         &ejsc_runtime_arg,
    "Set ejsc backend argument (Default : "
    DEFAULT_EJSC_RUNTIME_ARG_NODE " (if \"" DEFAULT_EJSC_RUNTIME_NODE "\" selected) / "
    DEFAULT_EJSC_RUNTIME_ARG_JAVA " (if \"" DEFAULT_EJSC_RUNTIME_JAVA "\" selected))" },
  { "-c", "--ejsc",     1, NULL,            &ejsc_jar,
    "Set ejsc path (Default : \"" DEFAULT_EJSC_JAR "\")." },
  { "-s", "--spec",     1, NULL,            &ejsvm_spec,
    "Set ejsvm.spec path (Default : \"" DEFAULT_EJSVM_SPEC "\")" },
  { "-t", "--tmpdir",   1, NULL,            &tmpdir,
    "Set temporary directory path (Default : \"" DEFAULT_TMPDIR "\")" },
  { NULL, "--verbose",  0, &verbose,        NULL,
    "Print more info." },
  { NULL, "--legacy",   0, &legacy,         NULL,
    "Use legacy ejsc parser (Same as "
    "\"--runtime " DEFAULT_EJSC_RUNTIME_JAVA
    " --runtime-arg " DEFAULT_EJSC_RUNTIME_ARG_JAVA "\")." },
  { NULL, NULL,         1, NULL,            NULL,              NULL }
};

int process_options(int ac, char *av[]) {
  int k;
  char *p;
  struct commandline_option *o;

  prompt = DEFAULT_PROMPT;
  ejsvm = DEFAULT_EJSVM;
  ejsc_runtime = DEFAULT_EJSC_RUNTIME_NODE;
  ejsc_runtime_arg = DEFAULT_EJSC_RUNTIME_ARG_NODE;
  ejsc_jar = DEFAULT_EJSC_JAR;
  ejsvm_spec = DEFAULT_EJSVM_SPEC;
  tmpdir = DEFAULT_TMPDIR;
  verbose = FALSE;
  legacy = FALSE;

  k = 1;
  p = av[1];
  while (k < ac) {
    if (p[0] == '-') {
      if (strcmp(p, "--") == 0) {
        ++k;
        break;
      }
      o = &options_table[0];
      while (o->short_key != NULL || o->long_key != NULL) {
        if ((o->short_key != NULL && strcmp(p, o->short_key) == 0)
            || (o->long_key != NULL && strcmp(p, o->long_key) == 0)) {
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
      if (o->short_key == NULL && o->long_key == NULL)
        fprintf(stderr, "unknown option: %s\n", p);
      k++;
      p = av[k];
    } else
      break;
  }

  if (legacy) {
    ejsc_runtime = DEFAULT_EJSC_RUNTIME_JAVA;
    ejsc_runtime_arg = DEFAULT_EJSC_RUNTIME_ARG_JAVA;
  }

  return k;
}

void print_options() {
  struct commandline_option *o;
  o = &options_table[0];
  while (o->short_key != NULL || o->long_key != NULL) {
    if (o->info != NULL) {
      if (o->short_key == NULL)
        printf("%s; %s\n", o->long_key, o->info);
      else if (o->long_key == NULL)
        printf("%s; %s\n", o->short_key, o->info);
      else
        printf("%s, %s; %s\n", o->short_key, o->long_key, o->info);
    }
    o++;
  }
}

int write_js(char buf[], int len) {
  int fd;

  if ((fd = open(tmpjs_filename, O_WRONLY | O_CREAT, 0644)) < 0) {
      fprintf(stderr, "opening js file %s faild\n", tmpjs_filename);
      return -1;
  }

  write(fd, "it = (", 6);
  write(fd, buf, len);     /* len is the length of buf without '\0' */
  write(fd, ")\n", 2);       /* write ')', and '\n' */

  close(fd);
  return 0;
}

void close_pipe(int p[2]) {
  close(p[R]);
  close(p[W]);
}

int emptyp(char *b) {
  char c;
  while ((c = *b++) != '\0') {
    if (' ' < c && c < 0x7f)
      return FALSE;
  }
  return TRUE;
}

void remove_tmpfiles(void) {
  unlink(tmpjs_filename);
  unlink(tmpjson_filename);
  unlink(tmpobc_filename);
}

int do_frontend(int pid) {
  int i, len, n, fn;
  int fd;
  char buf[BUFLEN];
  unsigned char tmp[2];

  snprintf(tmpjs_filename, N_TMPJS, "%s/tmp%d.js", tmpdir, pid);
  snprintf(tmpjson_filename, N_TMPJS, "%s/tmp%d.json", tmpdir, pid);
  snprintf(tmpobc_filename, N_TMPJS, "%s/tmp%d.obc", tmpdir, pid);
  if (verbose == TRUE) {
    printf("tmpjs_filename = %s\n", tmpjs_filename);
    printf("tmpobc_filename = %s\n", tmpobc_filename);
  }
  remove_tmpfiles();

  fn = 0;
  for (i = 0; ; i++) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, BUFLEN, stdin) == NULL)
      return 0;
    if (emptyp(buf) == TRUE)
      continue;
    len = strlen(buf);
    buf[--len] = '\0';    /* write '\0' to override a newline character */

    if (len == 0)
      continue;

    if (strcmp(buf, "exit") == 0)
      return 0;

    if (write_js(buf, len) < 0) {
      fprintf(stderr, "creating JS file failed\n");
      return -1;
    }

    if (strcmp(ejsc_runtime, "node") == 0)
      snprintf(ejsc_command, BUFLEN,
               "%s %s -fn %d -O --spec %s --out-obc %s",
               ejsc_runtime, ejsc_runtime_arg, fn, ejsvm_spec, tmpjs_filename);
    else
      snprintf(ejsc_command, BUFLEN,
               "%s %s %s -fn %d -O --spec %s --out-obc %s",
               ejsc_runtime, ejsc_runtime_arg, ejsc_jar, fn, ejsvm_spec, tmpjs_filename);
    if (verbose == TRUE)
      printf("ejsc_command = %s\n", ejsc_command);
    system(ejsc_command);

    if ((fd = open(tmpobc_filename, O_RDONLY)) < 0) {
      fprintf(stderr, "cannot open %s\n", tmpobc_filename);
      return -1;
    }

    if (read(fd, tmp, 2) != 2) {
      fprintf(stderr, "reading obc file failed\n");
      continue;
    }

    /* check the magic number */
    if (tmp[0] != 0xec) {
      fprintf(stderr, "unexpected magic number 0x%x of obc file\n", tmp[0]);
      continue;
    }
    /* tmp[1] is a hash value, which is not checked here */

    /* writes magic number and hash value */
    write(pipe_p2c[W], tmp, 2);

    if (read(fd, tmp, 2) != 2) {
      fprintf(stderr, "reading obc file failed\n");
      continue;
    }
    /* tmp[0] and tmp[1] are number of functions */
    write(pipe_p2c[W], tmp, 2);
    fn += tmp[0] * 256 + tmp[1];

    while ((n = read(fd, output_buf, BUFLEN)) > 0)
      write(pipe_p2c[W], output_buf, n);

    close(fd);
    remove_tmpfiles();

    printf("it = ");
    while ((n = read(pipe_c2p[R], output_buf, BUFLEN)) > 0) {
      if (output_buf[n - 1] == 0xff) {
        output_buf[n - 1] = '\0';
        printf("%s", output_buf);
        break;
      } else {
        output_buf[n] = '\0';
        printf("%s", output_buf);
      }
    }
    if (n > 0) continue;

    /*
     * The read system call returned 0 or negative value.
     * Possibly the pipe has been closed.
     */
    break;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  int pid;
  int k, i;
  char **av;

  k = process_options(argc, argv);

  if (help) {
    print_options();
    return 0;
  }

  if (pipe(pipe_c2p) < 0) {
    fprintf(stderr, "creating pipe_c2p failed\n");
    return 1;
  }
  if (pipe(pipe_p2c) < 0) {
    fprintf(stderr, "creating pipe_p2c failed\n");
    close_pipe(pipe_c2p);
    return 1;
  }
    
  av = malloc(sizeof(char *) * (argc - k + 3));
                                  /* +3 is for ejsvm, -R, and NULL */
  av[0] = ejsvm;
  av[1] = "-R";          /* -R option is always necessary */
  for (i = 2; k < argc; i++, k++)
    av[i] = argv[k];
  av[i] = NULL;

  if (verbose == TRUE) {
    i = 0;
    while (av[i] != NULL) {
      printf("%d: %s\n", i, av[i]);
      i++;
    }
  }

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork failed\n");
    close_pipe(pipe_c2p);
    close_pipe(pipe_p2c);
    return 1;
  }
  if (pid == 0) {
    /* child: exec ejsvm */
    dup2(pipe_p2c[R], 0);
    dup2(pipe_c2p[W], 1);
    close_pipe(pipe_c2p);
    close_pipe(pipe_p2c);
    if (execv(ejsvm, av) < 0)
      fprintf(stderr, "exec %s failed in child process\n", ejsvm);
    return 1;
  }
    
  /* parent: frontend */
  close(pipe_p2c[R]);
  close(pipe_c2p[W]);
  do_frontend(pid);
  close(pipe_p2c[W]);
  close(pipe_c2p[R]);
  return 0;
}

