#include "graphics.h"
#include <stdio.h>
int main() {
  // test sizeof
  char* buf[5];
  
  //buf[0] = 'c';
  int size = sizeof(buf) / sizeof(*buf);
  printf("size: %d\n", size);
  // test rgb
  printf("RGB TEST: %d\n", RGB(1,1,1));
  // test int graphics
  
  // test exit graphics

  // test getKey()
  char ch = getkey();
  printf("you have entered: %c\n", ch); 
  // test void sleep_ms(long ms)
  int i;
  for (i = 0; i < 5; i++) {
    sleep_ms(1000);
    printf("sec: %d\n", i);
  }  
  
   // test clear_screen
  
  // test draw_pixel
  
  // test draw_line
  
  // test new_offscreen_buffer()
  
  // test blit()  
return 0;
}

