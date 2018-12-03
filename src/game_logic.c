/* game_logic.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"

// Test code
void game_init() {
  sprite.x = 10;
  sprite.y = 0;
  sprite.width = 13;
  sprite.height = 9;
  sprite.graphic = &bird;
}

void move(struct Sprite *spr) {
  spr->x = (spr->x + 1);
}

/* TODO
  movesprite
  clear buffer after each frame
  krocklogik
  marklogik
*/
