/* display.h

   Written 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];
/* Declare pixel display buffer*/
extern char pixelbuffer[128][32];
/* Declare display buffer*/
extern char buffer[4][128];

extern const char const bird[16][16];

void display_buffer();
void display_init();
void display_string(int line, char *s);
void display_textbuffer();
uint8_t spi_send_recv(uint8_t data);
void pixelbuffer_to_buffer();
void display_debug( volatile int * const addr );
