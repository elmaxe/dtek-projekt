/* game_graphics.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game_graphics.h"
#include "display.h"
#include "data.h"

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

//TODO Fix so that argument 1 is an "object" (cacti, bird etc)
//and not a sprite
void move(Sprite *spr, Direction dir) {
  switch(dir) {
    case RIGHT:
      spr->x = (spr->x + 1) % SCREEN_WIDTH;
      break;
    case LEFT:
      //TODO: Remove object when out of bounds.
      spr->x = (spr->x - 1);
      break;
    case UP:
      spr->y = (spr->y - 1) % SCREEN_HEIGHT;
      break;
    case DOWN:
      spr->y = (spr->y + 1) % SCREEN_HEIGHT;
      break;
    default:
      spr->x = (spr->x - 1);
  }
}

void accel_dino(Dino *dino) {
  dino->y_speed += dino->y_accel;
}

void move_dino(Dino *dino) {
  dino->sprite.y += dino->y_speed;
}

void move_obstacle(Obstacle *obs) {
  obs->sprite.x += obs->x_speed;
}

void move_ground(Ground *gr) {
  gr->x += gr->x_speed;
}
