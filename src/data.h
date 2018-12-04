#define CACTUS_HEIGHT 13
#define CACTUS_WIDTH 6
#define BIRD_HEIGHT 9
#define BIRD_WIDTH 13
#define DINO_HEIGHT 16
#define DINO_WIDTH 16
#define GROUND_HEIGHT 4
#define GROUND_WIDTH 128

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];
/* Declare pixel display buffer*/
extern char pixelbuffer[128][32];
/* Declare display buffer*/
extern char buffer[4][128];

extern char bird_graphic[16][16];
extern char dino_graphic[16][16];
extern char cactus_graphic[16][16];
extern char ground_graphic[128][4];
