/* input.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>
#include <pic32mx.h>
#include "input.h"

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
