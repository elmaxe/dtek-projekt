/* loop.c

   This file was based on another file written by F. Lundevall.

   Edited 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include <string.h>
#include "loop.h"
#include "display.h"
#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"
#include "input.h"
void *stdout;
char * itoaconv( int num );

int seed = 0;

/* Interrupt Service Routine */
void user_isr() {
  IFSCLR(0) = 0x100;
}

/* Lab-specific initialization goes here */
void init()
{
  // Init leds
  TRISE &= ~0xFF;
  PORTE &= ~0xFF;

  // Init sws and btns
  TRISDSET = 0x7F<<5;

  // Init timer
  T2CON = 0x0; // Clear control register
  T2CONSET = (0x7 << 4); // Set prescale
  TMR2 = 0x0; // Clear timer register
  PR2 = 0x135A; // Set period register
  IFSCLR(0) = 0x100; // Clear timeout event flag
  IECSET(0) = 0x100; // Enable timer interrupts
  IPCSET(2) = 0x1F; // Set priority
  T2CONSET = 0x8000; // Start timer
  enable_interrupt();

  game_init();
  return;
}

/* This function is called repetitively from the main program */
void loop() {
  if (game_state == START) {
    seed++;
    add_screen_graphic_to_pixelbuffer(menu_graphic);
    pixelbuffer_to_buffer();
    clear_pixelbuffer();
    display_buffer();
    if (is_pressed_and_released(BTN2)) {
      game_state = MENU;
      srand(seed);
    }
  } else if (game_state == GAME) {
    update_game_state();
    update_graphics();
    PORTE &= ~0xFF;
    PORTE |= score;
  } else if (game_state == GAMEOVER) {
    add_screen_graphic_to_pixelbuffer(gameover_graphic);
    pixelbuffer_to_buffer();
    clear_pixelbuffer();
    display_buffer();
    if (is_pressed_and_released(BTN2)){
      game_state = MENU;
    }
  } else if (game_state == MENU) {
    display_string(0, "     -MENU-     ");
    display_string(1, "Play        BTN4");
    display_string(2, "Highscore   BTN3");
    display_string(3, "Credits     BTN2");
    display_textbuffer();
    if (is_pressed_and_released(BTN4)) {
      game_state = GAME;
    } else if (is_pressed_and_released(BTN3)) {
      game_state = HIGHSCORE;
    } else if (is_pressed_and_released(BTN2)) {
      game_state = CREDITS;
    }
  } else if (game_state == HIGHSCORE) {
    char hs1[16] = "HS1          ";
    char hs2[16] = "HS2          ";
    char hs3[16] = "HS3          ";
    char hs4[16] = "HS4          ";
    strcat(hs1, itoaconv((int)high_score[0]));
    strcat(hs2, itoaconv((int)high_score[1]));
    strcat(hs3, itoaconv((int)high_score[2]));
    strcat(hs4, itoaconv((int)high_score[3]));
    display_string(0, hs1);
    display_string(1, hs2);
    display_string(2, hs3);
    display_string(3, hs4);
    display_textbuffer();
    if (is_pressed_and_released(BTN4) || is_pressed_and_released(BTN3) || is_pressed_and_released(BTN2)) {
      game_state = MENU;
    }
  } else if (game_state == CREDITS) {
    display_string(0, "Dino Run");
    display_string(1, "by M.Wesslen");
    display_string(2, "and A.Elmarsson");
    display_string(3, "Press any button");
    display_textbuffer();
    if (is_pressed_and_released(BTN4) || is_pressed_and_released(BTN3) || is_pressed_and_released(BTN2)) {
      game_state = MENU;
    }
  }
  quicksleep(150000);
}

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
  int i;
  for(i = cyc; i > 0; i--);
}

#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}
