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

//TODO Fix so that argument 1 is an "object" (cacti, bird etc)
//and not a sprite
//Dont think this function will be needed
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

void update_game_state() {
  //Move ground
  move_ground(&ground);
  //Move obstacles
  int i;
  for (i = 0; i < obstacles.num_obstacles; i++) {
    if (obstacles.obstacles[i].on_screen) {
      move_obstacle(&obstacles.obstacles[i]);
    }
  }
}

void init_obstacle(Obstacle *obs, int x_speed){
  obs->x_speed = x_speed;
  obs->on_screen = 1;
  obs->sprite.x = SCREEN_WIDTH - 1;
}

void init_cactus(Obstacle *obs, int x_speed) {
  init_obstacle(obs, x_speed);
  obs->sprite.graphic = &cactus_graphic;
  obs->sprite.y = SCREEN_HEIGHT - GROUND_HEIGHT - CACTUS_HEIGHT;
  obs->sprite.width = CACTUS_WIDTH;
  obs->sprite.height = CACTUS_HEIGHT;
}

void init_bird(Obstacle *obs, int x_speed) {
  init_obstacle(obs, x_speed);
  obs->sprite.graphic = &bird_graphic;
  obs->sprite.y = SCREEN_HEIGHT - GROUND_HEIGHT - BIRD_HEIGHT*2;
  obs->sprite.width = BIRD_WIDTH;
  obs->sprite.height = BIRD_HEIGHT;
}

void add_obstacle(ObstacleType type, int x_speed) {
  int i;
  for (i = 0; i < MAX_OBSTACLES; i++) {
    if (~obstacles.obstacles[i].on_screen) {
      switch(type) {
        case CACTUS:
          init_cactus(&obstacles.obstacles[i], x_speed);
          break;
        case BIRD:
          init_bird(&obstacles.obstacles[i], x_speed);
          break;
      }
      obstacles.num_obstacles++;
      break;
    }
  }
}

void remove_obstacles() {
  int i;
  for (i = 0; i < MAX_OBSTACLES; i++) {
    Obstacle *o = &obstacles.obstacles[i];
    if ((*o).on_screen) {
      if ((*o).sprite.x < 0 - (*o).sprite.width) {
        (*o).on_screen = 0;
      }
    }
  }
}

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
  ground.x_speed = -1;
  ground.graphic = &ground_graphic;
  //Set up obstacles
  add_obstacle(CACTUS, -1);
}
