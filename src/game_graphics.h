/* game_graphics.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING */

typedef struct Sprite {
  int x;
  int y;
  int width;
  int height;
  int num_graphics
  char graphics[][];
} Sprite;

typedef struct Dino {
  //TODO: Dino needs two sprites for duck and stand; could be implemented by making Sprite.graphics a triple nested array
  Sprite sprite;
  int y_speed;
  int y_accel;
} Dino;

typedef struct Bird {
  Sprite sprite;
  int x_speed;
} Bird;

typedef struct Cactus {
  Sprite sprite;
  int x_speed;
} Cactus;