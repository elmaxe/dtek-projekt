/* game_graphics.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game_graphics.h"
#include "display.h"
#include "data.h"
#include "game_logic.h"

int scrolling_pixel_x_pos(int x_pos) {
  if (x_pos < 0) {
    return SCREEN_WIDTH + (x_pos % SCREEN_WIDTH); //Great bug if x_pos underflows.
  }
  return x_pos % SCREEN_WIDTH;
}

void add_graphic_to_pixelbuffer(Sprite sprite) {
  int x, y;
  for (x = 0; x < sprite.width; x++) {
    for (y = 0; y < sprite.height; y++) {
      pixelbuffer[sprite.x + x][sprite.y + y] |= (*sprite.graphic)[x][y];
    }
  }
}

void add_ground_to_pixelbuffer(Ground ground) {
  int x, y;
  for (x = 0; x < ground.width; x++) {
    for (y = 0; y < ground.height; y++) {
      pixelbuffer[scrolling_pixel_x_pos(ground.x + x)][ground.y + y] |= (*ground.graphic)[x][y];
    }
  }
}

//Update dino, ground, and the array of obstacles
void update_graphics() {
  //add_graphic_to_pixelbuffer(dino.sprite);
  add_ground_to_pixelbuffer(ground);
  int i;
  for (i = 0; i < obstacles.num_obstacles; i++) {
    add_graphic_to_pixelbuffer(obstacles.obstacles[i].sprite);
  }
  if (DAY) {
    invert_pixelbuffer();
  }
  pixelbuffer_to_buffer();
  clear_pixelbuffer();
  display_buffer();
}
