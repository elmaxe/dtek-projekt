/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_buffer();
void display_init();
void display_string(int line, char *s);
void display_textbuffer();
uint8_t spi_send_recv(uint8_t data);

void pixelbuffer_to_buffer();

/* Declare lab-related functions from mipslabfunc.c */
void loop();
void quicksleep(int cyc);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_buffer; display_buffer overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];
/* Declare pixel display buffer*/
extern char pixelbuffer[128][32];
/* Declare display buffer*/
extern char buffer[4][128];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns();
int getsw();
void enable_interrupt();
