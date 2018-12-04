/* game_graphics.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#define SPRITE_MAX_SIZE 16

#include "display.h"

typedef enum Direction {
  UP, DOWN, RIGHT, LEFT
} Direction;

typedef struct Sprite {
  int x, y;
  int width, height;
  char (*graphic)[SPRITE_MAX_SIZE][SPRITE_MAX_SIZE];
} Sprite;

typedef struct Dino {
  //TODO: Dino needs two sprites for duck and stand; could be implemented by making Sprite.graphics a triple nested array
  Sprite sprite;
  int y_speed;
  int y_accel;
} Dino;

//Cacti, birds etc.
typedef struct Obstacle {
  Sprite sprite;
  int x_speed;
} Obstacle;

typedef struct Ground {
  int x, y;
  int width, height;
  int x_speed;
  char (*graphic)[SCREEN_WIDTH][4];
} Ground;


void add_graphic_to_pixelbuffer(Sprite sprite);
void move(Sprite *spr, Direction dir);
void move_ground(Ground *gr);
