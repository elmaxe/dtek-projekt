/* display.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

//Screen dimensions in pixels
#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 128
#define NUM_PAGES 4

void display_buffer();
void display_init();
void display_string(int line, char *s);
void display_textbuffer();
uint8_t spi_send_recv(uint8_t data);
void pixelbuffer_to_buffer();
void display_debug( volatile int * const addr );
