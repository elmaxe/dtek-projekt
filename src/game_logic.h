#define DINO_BASE_POS 16
#define DINO_BASE_SPEED -3.0
#define DINO_ACCEL_LOW 0.18
#define DINO_ACCEL_HIGH 0.25

//Temporary code TODO: Remove
Dino dino;
Obstacle bird;
Ground ground;
Obstacles obstacles;
Visual moon;

void game_init();
void update_game_state();
void jump_dino(Dino *dino);

extern int GAME_STATE;
extern int DAY;
