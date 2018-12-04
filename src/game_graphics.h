/* game_graphics.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

typedef struct Empty {
  char (*graphic)[16][16];
} Empty;

typedef struct Sprite {
  int x;
  int y;
  int width;
  int height;
  char (*graphic)[16][16];
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
  Sprite sprite;
  int x_speed;
} Ground;


void add_graphic_to_pixelbuffer(Sprite sprite);
