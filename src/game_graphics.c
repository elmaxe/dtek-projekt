/* game_graphics.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game_graphics.h"
#include "display.h"

void add_graphic_to_pixelbuffer(Sprite sprite) {
  int x;
  int y;
  for (x = 0; x < sprite.width; x++) {
    for (y = 0; y < sprite.height; y++) {
      pixelbuffer[sprite.x + x][sprite.y + y] |= (*sprite.graphic)[x][y];
    }
  }
}
