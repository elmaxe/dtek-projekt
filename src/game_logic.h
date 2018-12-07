/* game_logic.h

   Written 2018-12-06 by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#define DINO_BASE_POS 16
#define DINO_BASE_SPEED -3.0
#define DINO_JUMP_ACCEL 0.17
#define DINO_REG_ACCEL 0.25
#define DINO_DUCK_ACCEL 0.5
#define BIRD_SWITCH_FRAME 10
#define DAY_NIGHT_CYCLE 1000
#define SPAWN_COUNTER_TIME 27
#define BIRD_SPEED -3
#define CACTUS_SPEED -2
#define GROUND_SPEED -2
#define DINO_RUN_ANIM_SPEED 3

//Temporary code TODO: Remove
Dino dino;
Ground ground;
Obstacles obstacles;
Visual moon;

void game_init();
void update_game_state();
void jump_dino(Dino *dino);

typedef enum GameState {
  START, MENU, GAME, GAMEOVER, HIGHSCORE, CREDITS
} GameState;

extern GameState game_state;
extern uint8_t score;
extern uint8_t high_score[4];
extern int DAY;
