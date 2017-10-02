#include <termios.h>
#include <sys/ioctl.h>

struct termios terminal_settings;

int main() {
  ioctl(1, TCGETS, &terminal_settings);
  terminal_settings.c_lflag |= (ECHO | ICANON); 
  ioctl(1, TCSETS, &terminal_settings);

  return 0;
}
