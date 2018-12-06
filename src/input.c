/* input.c

   Written 2018-12-06 by M. Wesslén and A. Elmarsson.

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

int is_pressed(Button btn) {
  switch (btn) {
    case BTN2:
      return getbtns() & 0x1;
    case BTN3:
      return (getbtns() & 0x2) >> 1;
    case BTN4:
      return (getbtns() & 0x4) >> 2;
  }
}

int is_pressed_and_released(Button btn) {
  if (is_pressed(btn)) {
    while (is_pressed(btn)) {}
    return 1;
  }
  return 0;
}
