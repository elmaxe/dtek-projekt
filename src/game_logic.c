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
  //Set up bird test
  bird.sprite.x = 127;
  bird.sprite.y = 0;
  bird.sprite.width = 13;
  bird.sprite.height = 9;
  bird.sprite.graphic = &bird_graphic;
  bird.x_speed = -1;
  //Set up ground
  ground.x = 0;
  ground.y = SCREEN_HEIGHT - 4;
  ground.width = SCREEN_WIDTH;
  ground.height = 4;
  ground.x_speed = -2;
  ground.graphic = &ground_graphic;
}
