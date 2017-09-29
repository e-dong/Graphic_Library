#include "graphics.h"
#include <stdio.h>
int main() {
  printf("hello\n");
  // test rgb
  printf("RGB TEST: %d\n", RGB(1,1,1));
  // test int graphics
  
  // test exit graphics

  // test getKey()
  
  // test void sleep_ms(long ms)
  int i;
  for (i = 1; i <= 5; i++) {
    printf("Second: %d\n", i);
    sleep_ms(1000);
  }  
  
   // test clear_screen
  
  // test draw_pixel
  
  // test draw_line
  
  // test new_offscreen_buffer()
  
  // test blit()  
return 0;
}

