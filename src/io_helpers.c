#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
  unsigned int input = PORTD;
  input >>= 8;
  input &= 0xF;
  return input;
}

int getbtns(void){
  unsigned int input = PORTD;
  input >>= 5;
  input &= 0x7;
  return input;
}
