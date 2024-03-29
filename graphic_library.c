/*
 * Double- Buffered Graphics Library
 * Author: Eric Dong
 * Creation Date:  9/29/2017
 * Last Modification Date: 10/1/2017
 */

#include "graphics.h"
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <termios.h>

struct fb_var_screeninfo variable;
struct fb_fix_screeninfo fixed;
struct termios terminal_settings;
size_t length;
unsigned short* memory_map_address;
int fb_fd;
const char* CLEAR = "\033[2J";

void init_graphics() {
  // Open the framebuffer file
  const char* path = "/dev/fb0"; 
  int fb_fd = open(path, O_RDWR); 
  ioctl(fb_fd, FBIOGET_VSCREENINFO, &variable);
  variable.bits_per_pixel = 16;
  variable.yres_virtual = 480;
  variable.xres_virtual = 640;
  ioctl(fb_fd, FBIOGET_VSCREENINFO, &variable);
  ioctl(fb_fd, FBIOGET_FSCREENINFO, &fixed);
  length = variable.yres_virtual * fixed.line_length;
  // Map the  file to address space
  memory_map_address = (unsigned short*) mmap(0, length,
  PROT_READ|PROT_WRITE, MAP_SHARED, fb_fd, 0);
  write(1,CLEAR,8);
  //clear_screen((void*) memory_map_address);
  // Disable Echo and  set  input to non-canonical mode
  ioctl(1, TCGETS, &terminal_settings);
  terminal_settings.c_lflag &= ~(ICANON|ECHO);
  ioctl(1, TCSETS, &terminal_settings);
}

void exit_graphics() {
  // unmap the file
  int retval = munmap((void *)memory_map_address, length);
  retval = ioctl(1, TCGETS, &terminal_settings);
  // set input back to canonical mode and turn echo back on
  terminal_settings.c_lflag |= (ICANON|ECHO);
  retval = ioctl(1, TCSETS, &terminal_settings);
  // close the frame buffer file
  retval = close(fb_fd);
}

char getkey() {
 // First use select system call to check if there is a key press
 // if there s a key press then read()
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
    // error calling select
  } else if (return_value) {
   // Data is ready  to be read
    read(0, &buf, count);
  } else {
    // user has not entered a key within 99 sec
    exit_graphics();
  }
 return buf;
}

void sleep_ms(long ms) {
  struct timespec t, t2;
  long sec = ms/1000;
  long numNano = (ms % 1000) * 1000000;

  t.tv_sec = sec;
  t.tv_nsec = numNano;
  int val = nanosleep(&t, &t2);
}

void clear_screen(void *img) {
   unsigned short* temp = (unsigned short*) img;
   int i ;
   // set all the bytes to zero
   for (i = 0; i <  length/2; i++) {
     *temp =  0;
     temp++;
   }
}
// draws a pixel given the x and y coordinate
// Note* image is stored in row-major order
void draw_pixel(void *img, int x, int y, color_t color) {
  unsigned short *fb = (unsigned short *) img;
  // find the y coordinate location in the mmapped file
  // y should be between (0 - 479)
  unsigned long y_pixel = y * 640;
  // the x coordinate should be between (0 - 639)
  unsigned long x_pixel = x;
  // compute the offset to point to correct pixel in memory
  unsigned short *ptr = (fb + y_pixel + x_pixel);
  *ptr = color;
}

// online source for Bresenham's Algorithm of Line Generation
//www.slideshare.net/saikrishnatanguturu/computer-graphics-ver10
//Assumptions: lines draw from left to right, top to bottom
void draw_line(void *img, int x1, int y1, int x2,int y2, color_t c) {
  int delta_x;
  int delta_y;
  int decision; // decides what pixel draw that is closest to the line
  int curr_x = x1;
  int curr_y = y1;
  // Get the deltas for x and y
  delta_x = x2 - x1;
  delta_y = y1 - y2;
  // check deltas
   if (delta_y == 0) {   // slope is zero, draw horizontal line
     int i;
     for(i = curr_x; i <= x2; i++) {
       draw_pixel(img, curr_x, curr_y, c);
       curr_x++;
     }
   } else if (delta_x == 0) { // slope inf, draw vertical line
     int i;
     for(i = curr_y; i <= y2; i++) {
       draw_pixel(img, curr_x, curr_y, c);
       curr_y ++;
     }
   } else if(delta_y > 0) { // handle positive slope
     float gradient = delta_y / delta_x;
     if(gradient <= 1) {
       decision = (2 * delta_y) - delta_x;
       while(curr_x <= x2 && curr_y >= y2) {
        // draw the pixel
          draw_pixel(img, curr_x, curr_y, c);
          if(decision < 0) {
          // no changes to curr_y
          // Calculate next decision
          decision = decision + (2 * delta_y);
          } else {
            curr_y --;
          // calculate next decision
            decision = decision + 2*(delta_y - delta_x);
          }
          curr_x ++;
        }  
     } else { // else gradient is > 1
       decision =  (2*delta_x) - delta_y;
       while(curr_x <= x2 && curr_y >= y2) {
         draw_pixel(img, curr_x, curr_y, c);
         if (decision < 0) {
         // no changes to curr_x
         // compute next decision
           decision = decision + 2*delta_x;
         } else {//decision >=0 otherwise
           curr_x ++;
           // compute next decision
           decision = decision + 2*(delta_x - delta_y); 
         }
         curr_y--;
       }
     }
   } else if (delta_y < 0) { // handle negative slope 
     delta_y = y2 - y1;
     float gradient = delta_y / delta_x;
     if(gradient <= 1) {
       decision = (2 * delta_y) - delta_x;
       while(curr_x <= x2 && curr_y <= y2) {
        // draw the pixel
          draw_pixel(img, curr_x, curr_y, c);
          if(decision < 0) {
          // no changes to curr_y 
          // Calculate next decision
          decision = decision + (2 * delta_y);
          } else {
            curr_y ++;
          // calculate next decision
            decision = decision + 2*(delta_y - delta_x);
          }
          curr_x ++;
        }
     } else { // else gradient is >1
       decision =  (2*delta_x) - delta_y;
       while(curr_x <= x2 && curr_y <= y2) {
         draw_pixel(img, curr_x, curr_y, c);
         if (decision < 0) {
           // no changes to curr_x
           // compute next decision
           decision = decision + 2*delta_x;
         } else {//decision >=0 otherwise
           curr_x ++;
           // compute next decision
           decision = decision + 2*(delta_x - delta_y);
         }
         curr_y++;
       }
     }
   }
}
// creates and returns a new buffer
void* new_offscreen_buffer() {
   void* offscreen_buffer_address = mmap(NULL, length, PROT_READ | 
   PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   return offscreen_buffer_address; 
}
// copies the buffer given by the parameter to the framebuffer mapped to 
// memory
void blit(void *src) {
   unsigned short* temp = (unsigned short*) src;
   unsigned short* fb = memory_map_address;
  int i = 0;
  for(i = 0; i < length/2; i++){
    *fb = (*temp);
    fb = fb + 1;
    temp = temp + 1;
  }
}
