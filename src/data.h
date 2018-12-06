#define CACTUS_HEIGHT 11
#define CACTUS_WIDTH 6

#define BIRD_HEIGHT 9
#define BIRD_WIDTH 13

#define DINO_HEIGHT 16
#define DINO_WIDTH 16

#define GROUND_HEIGHT 4
#define GROUND_WIDTH 128

#define MOON_WIDTH 6
#define MOON_HEIGHT 6

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];
/* Declare pixel display buffer*/
extern uint8_t pixelbuffer[128][32];
/* Declare display buffer*/
extern uint8_t buffer[4][128];

extern uint8_t bird_graphic[16][16];
extern uint8_t bird_graphic_2[16][16];
extern uint8_t dino_graphic[16][16];
extern uint8_t dino_graphic_duck[16][16];
extern uint8_t cactus_graphic[16][16];
extern uint8_t ground_graphic[128][4];
extern uint8_t moon_graphic[16][16];
extern uint8_t menu_graphic[128][32];
