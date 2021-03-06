/* game_graphics.h

   Written 2018-12-06 by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#define SPRITE_MAX_SIZE 16
#define MAX_OBSTACLES 10

#include "display.h"

typedef enum Direction {
  UP, DOWN, RIGHT, LEFT
} Direction;

typedef struct Sprite {
  int x, y;
  int width, height;
  uint8_t (*graphic)[SPRITE_MAX_SIZE][SPRITE_MAX_SIZE];
} Sprite;

typedef struct Dino {
  //TODO: Dino needs two sprites for duck and stand; could be implemented by making Sprite.graphics a triple nested array
  Sprite sprite;
  float y_pos;
  float y_speed;
  float y_accel;
  int frame;
  int frame_counter;
} Dino;

typedef enum ObstacleType {
  BIRD, CACTUS
} ObstacleType;

//Cacti, birds etc.
typedef struct Obstacle {
  Sprite sprite;
  int x_speed;
  uint8_t on_screen;
  int frame_counter;
  ObstacleType type;
  int frame;
} Obstacle;

typedef struct Ground {
  int x, y;
  int width, height;
  int x_speed;
  uint8_t (*graphic)[SCREEN_WIDTH][4];
} Ground;

typedef struct Obstacles {
  Obstacle obstacles[MAX_OBSTACLES];
  int num_obstacles;
} Obstacles;

//Moon, clouds?
typedef struct Visual {
  Sprite sprite;
} Visual;


void update_graphics();
void add_graphic_to_pixelbuffer(Sprite sprite);
void add_screen_graphic_to_pixelbuffer(uint8_t array[SCREEN_WIDTH][SCREEN_HEIGHT]);
