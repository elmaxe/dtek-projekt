/* loop.c

   This file was based on another file written by F. Lundevall.

   Edited 2018-11- by M. Wesslén and A. Elmarsson.

   For copyright and licensing, see file COPYING
*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "loop.h"
#include "display.h"
#include "game_graphics.h"
#include "game_logic.h"
#include "data.h"

/* Interrupt Service Routine */
void user_isr() {
  // interrupt
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
  PR2 = 0x7A12; // Set period register
  IFSCLR(0) = 0x100; // Clear timeout event flag
  IECSET(0) = 0x100; // Enable timer interrupts
  IPCSET(2) = 0x1F; // Set priority
  T2CONSET = 0x8000; // Start timer
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void loop() {
  if (getbtns() == 0x4) {
    add_graphic_to_pixelbuffer(sprite);
    pixelbuffer_to_buffer();
    display_buffer();
    move(&sprite);
  }
  if (getbtns() == 0x2) {
    //move(&sprite);
  }
  quicksleep(500);
}

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
  int i;
  for(i = cyc; i > 0; i--);
}
