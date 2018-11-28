/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  // interrupt
  IFSCLR(0) = 0x100;
}

/* Lab-specific initialization goes here */
void labinit( void )
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
void labwork(void) {
  quicksleep(50);
}
