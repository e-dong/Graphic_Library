/*
 * Test Driver for Double-Buffered Graphics Library
 */
#include "graphics.h"
#include <stdio.h>
int main() {
   init_graphics();
   printf("Hit \'s\' to start or \'q\' to quit\n");
   char ch = getkey();
   if (ch == 's') {
     void* new_buf = new_offscreen_buffer();
     printf("New Buffer created at address: %p\n", new_buf);
     sleep_ms(2000);
     clear_screen(new_buf);
     blit(new_buf);
     sleep_ms(1000);
     int y;
     int x;
     // All Pixels should have color
     for (y = 0; y < 480; y++){
       for (x = 0; x < 640; x++){
         draw_pixel(new_buf, x, y, RGB(31,63,31));
       }
     }
     blit(new_buf);
     
     sleep_ms(1000);
     clear_screen(new_buf);
     blit(new_buf); // Screen should appear to go blank
     sleep_ms(2000);
     // positive sloped line
     draw_line(new_buf, 0, 479, 639, 0,  RGB(31,63,31));
     draw_line(new_buf, 0, 479, 100, 0,  RGB(31,63,31));
     //negative sloped line
     draw_line(new_buf, 0, 0, 639, 479,  RGB(31,0,0));
     draw_line(new_buf, 0, 0, 100, 479,  RGB(31,0,0));
     // draws horizontal line
     draw_line(new_buf, 0, 240, 639, 240, RGB(31,31,0));
     //draws vertical line
     draw_line(new_buf,320, 0, 320, 479, RGB(31,31,0)); 
     blit(new_buf); 
 }
   exit_graphics();
   return 0;
}

