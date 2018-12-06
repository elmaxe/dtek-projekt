/* loop.c

   This file was based on another file written by F. Lundevall.

   Edited 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "loop.h"
#include "display.h"
#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"
#include "input.h"
void *stdout;

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
    if (is_pressed(BTN2)) {
      game_state = GAME;
      srand(seed);
    }
    /*
    display_string(0, "Dino Run");
    display_string(1, "by M.Wesslen");
    display_string(2, "and A.Elmarsson");
    display_string(3, "Press any button");
    display_textbuffer();*/
  } else if (game_state == GAME) {
    update_game_state();
    update_graphics();
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
