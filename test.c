#include <stdio.h>
#include <stdlib.h>

int main() {
  void* buf = malloc(3);
  char* buf_char = (char*) buf;
  void* buf2 = malloc(3);
  char* buf_char2 = (char*) buf2;
  
  buf_char[0] = 'a';
  buf_char[1] = 'b';
  buf_char[2] = 'c';
  char* temp = buf_char; //src casted to char*
  char* temp2 = buf_char2;
  //char* start = temp;
  int i;
  for (i = 0; i < 3; i++) {
    *temp2 = *temp; 
    printf("char: %c\n", *temp);
    temp++;
    temp2++;
  }  
   printf("%s\n", buf_char2);
  
  //temp = temp + 1; 
  //temp ='a';
  //temp = temp - 1;
  //temp++;
  //temp = (char)'a';
  //temp++;
  //temp = (char)'t';
  ///temp = temp - 2;
  //buf = temp;
  //printf("string: %c\n", (char*)buf); 
  /*char* temp2 = (char*) buf2; // temp2 represents the destination
  int i;
  for(i = 0; i < 3; i++) {
    temp2[i] = temp[i];
    printf("%c", temp2[i]);
  } 
  printf("\n");
  buf2 = temp2;
  printf("%s\n", (char*)buf2);*/
  return 0;
}
