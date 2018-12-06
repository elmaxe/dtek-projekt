/* input.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

typedef enum Button {
  BTN2, BTN3, BTN4
} Button;

int is_pressed();
int getsw();
