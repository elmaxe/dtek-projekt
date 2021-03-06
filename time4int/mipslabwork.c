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

volatile unsigned int* myTRISE = (int*)0xbf886100;
volatile unsigned int* myPORTE = (int*)0xbf886110;

int mytime = 0x5957;
int prime = 1234567;

unsigned char tickcount = 0;
unsigned int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Declare helper function */
void ledcount(void);
void update_time(void);

/* Interrupt Service Routine */
void user_isr( void ) {
  timeoutcount++;
  if (timeoutcount >= 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    ledcount();
    timeoutcount = 0;
  }
  IFSCLR(0) = 0x100;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // Init leds
  *myTRISE &= ~0xFF;
  *myPORTE &= ~0xFF;

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
void labwork( void ) {
  update_time();
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}

void ledcount(void){
  tickcount++;
  *myPORTE &= ~0xFF;
  *myPORTE |= tickcount;
}

void update_time(void){
  int btns = getbtns();
  if (btns > 0){
    int btn2 = btns & 0x1;
    int btn3 = (btns >> 1) & 0x1;
    int btn4 = (btns >> 2) & 0x1;
    int sw = getsw();
    if (btn2){
      mytime &= ~0xF0;
      mytime |= (sw << 4);
    }
    if (btn3){
      mytime &= ~0xF00;
      mytime |= (sw << 8);
    }
    if (btn4){
      mytime &= ~0xF000;
      mytime |= (sw << 12);
    }
  }
}
