/* game_logic.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"
#include "display.h"
// Test code
void game_init() {
  sprite.x = 10;
  sprite.y = 0;
  sprite.width = 13;
  sprite.height = 9;
  sprite.graphic = &bird;
}

//dirs:
//0 is left, 1 is right
//2 is up, 3 is down
void move(struct Sprite *spr, int dir) {
  if (dir == 0) {
    spr->x = (spr->x + 1);
  } else if (dir == 1) {
    spr->x = (spr->x - 1);
  } else if (dir == 2) {
    spr->y = (spr->y - 1) % SCREEN_HEIGHT;
  } else if (dir == 3) {
    spr->y = (spr->y + 1) % SCREEN_HEIGHT;
  }

}

/* TODO
  movesprite
  clear buffer after each frame
  krocklogik
  marklogik
*/
