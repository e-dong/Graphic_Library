#include "graphics.h"
#include <stdio.h>
#include <time.h>

void init_graphics() {

}
void exit_graphics() {

}
char getkey() {
 return 'a';
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

