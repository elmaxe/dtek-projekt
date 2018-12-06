#define DINO_BASE_POS 16
#define DINO_BASE_SPEED -3.0
#define DINO_JUMP_ACCEL 0.17
#define DINO_REG_ACCEL 0.25
#define DINO_DUCK_ACCEL 0.31
#define BIRD_SWITCH_FRAME 10

//Temporary code TODO: Remove
Dino dino;
Ground ground;
Obstacles obstacles;
Visual moon;

void game_init();
void update_game_state();
void jump_dino(Dino *dino);

extern int GAME_STATE;
extern int DAY;
extern int spawn_counter;
