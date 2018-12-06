/* game_logic.c

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"
#include "display.h"
#include "input.h"
#include "loop.h"
void *stdout;
void game_lose();

GameState game_state = START;
int DAY = 0;
unsigned int spawn_counter = 0;
unsigned int day_counter = 0;
unsigned int next_day;
//Score that updates in remove_obstacles
unsigned uint8_t score;
// Highscore array
unsigned uint8_t high_score[4];

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
    dino->y_speed = DINO_BASE_SPEED;
    dino->y_accel = DINO_JUMP_ACCEL;
  }
}

void dino_anim(Dino *dino, int state) {
  if (dino->frame_counter > DINO_RUN_ANIM_SPEED) {
    dino->frame_counter = 0;
    if (dino->frame == 0) {
      dino->frame = 1;
      if (state == 0) {
        dino->sprite.graphic = &dino_graphic_2;
        return;
      }
      dino->sprite.graphic = &dino_graphic_duck_2;
    } else {
      dino->frame = 0;
      if (state == 0) {
        dino->sprite.graphic = &dino_graphic;
        return;
      }
      dino->sprite.graphic = &dino_graphic_duck;
    }
  }
}

void move_dino(Dino *dino) {
  dino->frame_counter++;
  // If in jump and jump button not pressed, high down accel.
  if (round(dino->y_pos) != DINO_BASE_POS) {
    // If duck button pressed even higher down accel.
    if (is_pressed(BTN3)) {
      dino->y_accel = DINO_DUCK_ACCEL;
    } else {
      dino->y_accel = DINO_REG_ACCEL;
    }
  }
  // If jump button pressed, low down accel.
  if (is_pressed(BTN4)) {
    jump_dino(dino);
    if (round(dino->y_pos) != DINO_BASE_POS) {
      dino->y_accel = DINO_JUMP_ACCEL;
    }
  }
  // If duck button pressed point graphic to duck graphic
  if (is_pressed(BTN3)) {
    //dino->sprite.graphic = &dino_graphic_duck;
    dino_anim(dino, 1);
  } else {
    //dino->sprite.graphic = &dino_graphic;
    dino_anim(dino, 0);
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
  obs->frame_counter++;
  if (obs->frame_counter >= BIRD_SWITCH_FRAME && obs->type == BIRD) {
    obs->frame_counter = 0;
    switch(obs->frame) {
      case 0:
        obs->sprite.graphic = &bird_graphic_2;
        obs->frame = 1;
        break;
      case 1:
      obs->sprite.graphic = &bird_graphic;
      obs->frame = 0;
      break;
    }
  }
}

void move_ground(Ground *gr) {
  gr->x += gr->x_speed;
}

void init_dino(Dino *dino);

void init_obstacle(Obstacle *obs, int x_speed){
  obs->x_speed = x_speed;
  obs->on_screen = 1;
  obs->sprite.x = SCREEN_WIDTH - 1;
  obs->frame_counter = 0;
  obs->frame = 0;
}

void init_cactus(Obstacle *obs, int x_speed) {
  init_obstacle(obs, CACTUS_SPEED);
  obs->sprite.graphic = &cactus_graphic;
  obs->sprite.y = SCREEN_HEIGHT - 1 - CACTUS_HEIGHT;
  obs->sprite.width = CACTUS_WIDTH;
  obs->sprite.height = CACTUS_HEIGHT;
  obs->type = CACTUS;
}

void init_bird(Obstacle *obs, int x_speed) {
  init_obstacle(obs, BIRD_SPEED);
  int ran_height = 1;
  ran_height = (rand() % 3) + 1;
  obs->sprite.graphic = &bird_graphic;
  obs->sprite.y = SCREEN_HEIGHT - GROUND_HEIGHT - BIRD_HEIGHT*ran_height;
  obs->sprite.width = BIRD_WIDTH;
  obs->sprite.height = BIRD_HEIGHT;
  obs->type = BIRD;
}

void add_obstacle(ObstacleType type, int x_speed) {
  int i;
  for (i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles.obstacles[i].on_screen) {
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
    if (obstacles.obstacles[i].on_screen) {
      if (obstacles.obstacles[i].sprite.x + obstacles.obstacles[i].sprite.width < 0) {
        obstacles.obstacles[i].on_screen = 0;
        score++;
      }
    }
  }
}


void collision(Dino d, Obstacle o) {
  int x, y;
  int o_pixel_x_pos, o_pixel_y_pos;
  int d_pixel_x, d_pixel_y;
  for (x = 0; x < o.sprite.width; x++) {
    for (y = 0; y < o.sprite.height; y++) {
      if ((*o.sprite.graphic)[x][y]) {
        o_pixel_x_pos = o.sprite.x + x;
        o_pixel_y_pos = o.sprite.y + y;
        d_pixel_x = o_pixel_x_pos - d.sprite.x;
        d_pixel_y = o_pixel_y_pos - d.sprite.y;
        if (0 <= d_pixel_x && d_pixel_x < DINO_WIDTH && 0 <= d_pixel_y && d_pixel_y < DINO_HEIGHT) {
          if ((*d.sprite.graphic)[d_pixel_x][d_pixel_y]) {
            game_lose();
            return;
          }
        }
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
  for (i = 0; i < MAX_OBSTACLES; i++) {
    if (obstacles.obstacles[i].on_screen) {
      move_obstacle(&obstacles.obstacles[i]);
      collision(dino, obstacles.obstacles[i]);
    }
  }
  remove_obstacles();
  spawn_counter++;
  day_counter++;
  //Check if we should switch to day/night
  if (day_counter >= next_day) {
    next_day = rand() % DAY_NIGHT_CYCLE;
    day_counter = 0;
    if (DAY) {
      DAY = 0;
    } else {
      DAY = 1;
    }
  }
  //Spawn obstacles
  if (spawn_counter % SPAWN_COUNTER_TIME == 0) {
    int ran = rand() % 4;
    switch(ran) {
      case 0:
        add_obstacle(CACTUS, -1);
        break;
      case 1:
        add_obstacle(BIRD, -1);
        break;
    }
  }
}

void add_high_score() {
  unsigned uint8_t tmp;
  int i, j;
  for (i = 0; i < NUM_PAGES; i++) {
    if (score > high_score[i]) {
      for (j = NUM_PAGES - 1; j > i; j--) {
        high_score[j] = high_score[j - 1];
      }
      high_score[i] = score;
      return;
    }
  }
}

void game_init() {
  next_day = rand() % DAY_NIGHT_CYCLE;
  //Score that updates in remove_obstacles
  score = 0;
  //moon
  moon.sprite.x = 100;
  moon.sprite.y = 5;
  moon.sprite.width = MOON_WIDTH;
  moon.sprite.height = MOON_HEIGHT;
  moon.sprite.graphic = &moon_graphic;

  dino.sprite.x = 5;
  dino.sprite.y = DINO_BASE_POS;
  dino.sprite.width = DINO_WIDTH;
  dino.sprite.height = DINO_HEIGHT;
  dino.sprite.graphic = &dino_graphic;
  dino.y_speed = 0;
  dino.y_accel = 0;
  dino.y_pos = (float)DINO_BASE_POS;
  dino.frame = 0;
  dino.frame_counter = 0;
  //Set up ground
  ground.x = 0;
  ground.y = SCREEN_HEIGHT - GROUND_HEIGHT;
  ground.width = SCREEN_WIDTH;
  ground.height = GROUND_HEIGHT;
  ground.x_speed = GROUND_SPEED;
  ground.graphic = &ground_graphic;
}

void game_lose() {
  int i;
  for (i = 0; i < MAX_OBSTACLES; i++) {
    obstacles.obstacles[i].on_screen = 0;
  }
  add_high_score();
  game_init();
  game_state = GAMEOVER;
}
