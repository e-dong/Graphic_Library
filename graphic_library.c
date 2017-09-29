#include "graphics.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

void init_graphics() {

}
void exit_graphics() {

}
char getkey() {
 // First use select to check if there is a key press
 // if there s a key press then read()
 /*int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);*/
  fd_set rfds;
  struct timeval tv;
  int return_value;

  char buf;
  size_t count = 1;

  // Watch stdin (fd 0) to see input
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  tv.tv_sec = 99; // timeout after 99 sec
  tv.tv_usec = 0;

  return_value = select(1, &rfds, NULL, NULL, &tv);
  if(return_value == -1) {
    printf("error calling select\n");
  } else if (return_value) {
    printf("Data is ready now\n");
    read(0, &buf, count);   
  } else {
    printf("data timed out\n");
  } 
 return buf; 
}
void sleep_ms(long ms) {
  struct timespec t, t2; 
  long sec = ms/1000;
  long numNano = (ms % 1000) * 1000000;
  //printf("sec: %lu, nano: %lu\n", sec, numNano);
  t.tv_sec = sec;
  t.tv_nsec = numNano;
  
  int val = nanosleep(&t, &t2);
  //printf("%d\n", val);
}
void clear_screen(void *img) {
  
}
void draw_pixel(void *img, int x, int y, color_t color) {

}
void draw_line(void *img, int x1, int y1, int x2,int y2, color_t c) {

}
void *new_offscreen_buffer() {

}
void blit(void *src) {

}

