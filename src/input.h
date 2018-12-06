/* input.h

   Written 2018-12-06 by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

typedef enum Button {
  BTN2, BTN3, BTN4
} Button;

int is_pressed(Button bnt);
int is_pressed_and_released(Button btn);
int getsw();
