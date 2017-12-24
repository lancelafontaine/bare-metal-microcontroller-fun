#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "serial.h"

int main(){

  //String of int
  char buffer [4]="422";
  //atoi converts ascii to int
  int i = atoi(buffer)- 420;

  //initialising uart for serial communication
  Serial.uart_init();
  while(i-->0){
    Serial.uart_print("Hello Soen ");
    Serial.uart_println(buffer);
  }
}
