#define DINO_BASE_POS 16

//Temporary code TODO: Remove
Dino dino;
Obstacle bird;
Ground ground;
Obstacles obstacles;

void game_init();
void update_game_state();
void jump_dino(Dino *dino);

extern int GAME_STATE;
extern int DAY;
