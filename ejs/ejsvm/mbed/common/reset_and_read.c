// cite : http://linuxjf.osdn.jp/JFdocs/Serial-Programming-HOWTO-3.html

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#define END_CHAR ((char) 0x04) /* End-Of-Transmisson */
#define BAUDRATE B9600
#define BUFFER_SIZE (1024)

int open_tty_non_blocking(const char *path)
{
  /*
    Open the modem device for reading and writing.
    No tty control is done so that the connection will not be disconnected
    even if CTRL-C happens to occur due to noise.
  */
  return open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);
}

int set_tty_blocking(int tty)
{
  const int val = 0;
  const int ret = ioctl(tty, FIONBIO, &val);

  return ret != -1;
}

void init_termios(struct termios *ptio)
{
  if (ptio == NULL)
    return;

  bzero(ptio, sizeof(*ptio)); /* Clear the new port configuration structure */

  /*
    BAUDRATE: Baud rate setting.
  */
  cfsetospeed(ptio, BAUDRATE);
  cfsetispeed(ptio, BAUDRATE);

  /*
    CRTSCTS : Output hardware flow control (only when using a cable with all necessary wiring,
              see Chapter 7 of the Serial-HOWTO) (http://linuxjf.osdn.jp/JFdocs/Serial-HOWTO-7.html)
    CS8     : 8n1 (8 bits，non-parity，stop-bit 1)
    CLOCAL  : No local connection, no modem control
    CREAD   : Enable receiving characters.
  */
  ptio->c_cflag |= CRTSCTS | CS8 | CREAD | CLOCAL;

  /*
    IGNPAR  : Ignore parity error data
  */
  ptio->c_iflag = IGNPAR;

  /*
   Output in raw mode
  */
  ptio->c_oflag = 0;

  /*
    ICANON  : Enable canonical input
              Disables all echoes and does not signal the program.
  */
  ptio->c_lflag = ICANON;

 /*
   Initialize all control characters
 */
  ptio->c_cc[VINTR]    = 0;     /* Ctrl-c */
  ptio->c_cc[VQUIT]    = 0;     /* Ctrl-\ */
  ptio->c_cc[VERASE]   = 0;     /* del */
  ptio->c_cc[VKILL]    = 0;     /* @ */
  ptio->c_cc[VEOF]     = 4;     /* Ctrl-d */
  ptio->c_cc[VTIME]    = 0;     /* Do not use characters timer */
  ptio->c_cc[VMIN]     = 1;     /* Block reading until one character arrives */
#ifdef VSWTC
  ptio->c_cc[VSWTC]    = 0;     /* '\0' */
#endif /* VSWTC */
  ptio->c_cc[VSTART]   = 0;     /* Ctrl-q */
  ptio->c_cc[VSTOP]    = 0;     /* Ctrl-s */
  ptio->c_cc[VSUSP]    = 0;     /* Ctrl-z */
  ptio->c_cc[VEOL]     = 0;     /* '\0' */
#ifdef VDSUSP
  ptio->c_cc[VDSUSP]   = 0;     /* Ctrl-y */
#endif /* VDSUSP */
  ptio->c_cc[VREPRINT] = 0;     /* Ctrl-r */
  ptio->c_cc[VDISCARD] = 0;     /* Ctrl-u */
  ptio->c_cc[VWERASE]  = 0;     /* Ctrl-w */
  ptio->c_cc[VLNEXT]   = 0;     /* Ctrl-v */
  ptio->c_cc[VEOL2]    = 0;     /* '\0' */
#ifdef VSTATUS
  ptio->c_cc[VSTATUS]  = 0;     /* Ctrl-t */
#endif /* VSTATUS */


  return;
}

int send_break(int tty)
{
  return tcsendbreak(tty, 0);
}

void read_ejsvm_out(int tty, FILE* out)
{
  unsigned char buf[BUFFER_SIZE] = { 0 };

  do {
    const ssize_t read_byte = read(tty, buf, BUFFER_SIZE - 1);
    if (read_byte == 0)
      break;

    buf[read_byte] = 0;

    fprintf(out, "%s", buf);
    fflush(out);
  } while(1);

  return;
}

int main(int argc, const char ** argv) {
  if (argc != 2) {
    printf("usage: %s <path to tty>\n", argv[0]);
    return 1;
  }

  const char * const dev = argv[1];

  const int tty = open_tty_non_blocking(dev);
  if (tty < 0) {
    close(tty);

    printf("Error: Could not open %s.\n", dev);
    return 2;
  }

  if (!set_tty_blocking(tty)) {
    printf("Error: Could not change tty mode to blocking.\n");
    return 3;
  }

  struct termios oldtio, newtio;
  tcgetattr(tty, &oldtio); /* Save the current serial port settings */

  init_termios(&newtio);

 /*
   Clear the modem line and enable the port settings.
 */
  tcflush(tty, TCIFLUSH);
  tcsetattr(tty, TCSANOW, &newtio);

  const int break_ret = send_break(tty);

  if (break_ret == -1) {
    tcsetattr(tty, TCSANOW, &oldtio);
    close(tty);

    printf("Error: Could not send Break\n");
    return 4;
  }

  read_ejsvm_out(tty, stdout);

  tcsetattr(tty, TCSANOW, &oldtio);
  const int close_ret = close(tty);
  return close_ret;
}

