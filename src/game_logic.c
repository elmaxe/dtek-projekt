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
#include "input.h"

int GAME_STATE = 0;
int DAY = 1;

int round(float f) {
  int floor = (int)f;
  if (f >= 0){
    if (f - (float)floor < 0.49)
      return floor;
    else
      return floor + 1;
  } else {
    if (f - (float)floor > -0.49)
      return floor;
    else
      return floor - 1;
  }
}

void jump_dino(Dino *dino) {
  if (round(dino->y_pos) == DINO_BASE_POS) {
    dino->y_speed = -3.0;
    dino->y_accel = 0.18;
  }
}

void move_dino(Dino *dino) {
  if (round(dino->y_pos) != DINO_BASE_POS) {
    dino->y_accel = 0.25;
  }
  if ((getbtns() & 0x4) >> 2){
    jump_dino(dino);
    if (round(dino->y_pos) != DINO_BASE_POS) {
      dino->y_accel = 0.18;
    }
  }
  dino->y_pos += dino->y_speed;
  dino->y_speed += dino->y_accel;
  dino->sprite.y = round(dino->y_pos);
  if (round(dino->y_pos) >= DINO_BASE_POS) {
    dino->y_speed = 0;
    dino->y_accel = 0;
    dino->y_pos = (float)DINO_BASE_POS;
    dino->sprite.y = DINO_BASE_POS;
  }
}

void move_obstacle(Obstacle *obs) {
  obs->sprite.x += obs->x_speed;
}

void move_ground(Ground *gr) {
  gr->x += gr->x_speed;
}

void init_dino(Dino *dino);

void init_obstacle(Obstacle *obs, int x_speed){
  obs->x_speed = x_speed;
  obs->on_screen = 1;
  obs->sprite.x = SCREEN_WIDTH - 1;
}

void init_cactus(Obstacle *obs, int x_speed) {
  init_obstacle(obs, x_speed);
  obs->sprite.graphic = &cactus_graphic;
  obs->sprite.y = SCREEN_HEIGHT - 1 - CACTUS_HEIGHT;
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

void update_game_state() {
  //Move ground
  move_ground(&ground);
  move_dino(&dino);
  //Move obstacles
  int i;
  for (i = 0; i < obstacles.num_obstacles; i++) {
    if (obstacles.obstacles[i].on_screen) {
      move_obstacle(&obstacles.obstacles[i]);
    }
  }
}

void game_init() {
  dino.sprite.x = 5;
  dino.sprite.y = DINO_BASE_POS;
  dino.sprite.width = DINO_WIDTH;
  dino.sprite.height = DINO_HEIGHT;
  dino.sprite.graphic = &dino_graphic;
  dino.y_speed = 0;
  dino.y_accel = 0;
  dino.y_pos = (float)DINO_BASE_POS;
  //Set up ground
  ground.x = 0;
  ground.y = SCREEN_HEIGHT - GROUND_HEIGHT;
  ground.width = SCREEN_WIDTH;
  ground.height = GROUND_HEIGHT;
  ground.x_speed = -1;
  ground.graphic = &ground_graphic;
  //Set up obstacles
  add_obstacle(CACTUS, -1);
}
