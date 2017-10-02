#include "graphics.h"
#include <stdio.h>

int main() {
   init_graphics();
   void* new_buf = new_offscreen_buffer();
   int y;
   int x;
   // All Pixels should have color
   for (y = 0; y < 480; y++){
     for (x = 0; x < 640; x++){
       draw_pixel(new_buf, x, y, RGB(31,63,31));
     }
   }
   blit(new_buf);
   // wait 3sec and then clear
    sleep_ms(3000);
    clear_screen(new_buf);
    blit(new_buf);

  // positive sloped line
  draw_line(new_buf, 0, 479, 639, 0,  RGB(31,63,31));
  draw_line(new_buf, 0, 479, 100, 0,  RGB(31,63,31));
  //negative sloped line
  draw_line(new_buf, 0, 0, 639, 479,  RGB(31,31,31));
  draw_line(new_buf, 0, 0, 100, 479,  RGB(31,31,31));
  // draws horizontal line
  draw_line(new_buf, 0, 240, 639, 240, RGB(31,31,0));
  //draws vertical line
  draw_line(new_buf,320, 0, 320, 479, RGB(0,31,31)); 
  blit(new_buf); 

  // hit any key to exit
  char ch = getkey();
  exit_graphics(); 
return 0;
}

