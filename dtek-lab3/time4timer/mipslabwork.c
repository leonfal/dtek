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

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";
int timeoutcounter = 0;

// volatile pointer to point to adress where PORTE is.
volatile int *porte = (volatile int*)0xbf886110;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // volatile pointer to point to adress where TRISE is.
  volatile int *trise = (volatile int*)0xbf886100;
  // sets 8 lsb to 0 (output) using bitwise inverse.
  *trise &= ~0xff;
  // initialize the leds to off.
  *porte &= ~0xff;

  TRISD |= 0xfe0;

  // Stop timer and clear control register set prescaler at 1:1
  T2CON = 0x0;
  // clear timer register
  TMR2 = 0x0;
  // load period register
  PR2 = 0x7a12;
  // 80 mhz / 256 = 312 500
  // wants 10 times per second = 31250 = 0x7a12
  // because 312500/31250 = 10 it will display 10 times / second.
  // T2CONSET = 0x8070; // set prescaler to 1:256 and start timer
  // bit 15 = if timer is on, bit 4-6 if all is on, prescaler to 256.
  T2CONSET = 0x8070;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  // if flag is 1, reset event.
  // Timer 2 interrupt flag. Can be found at bit 8 in IFS0

  if((IFS(0) & 0x100))
  {
    // reset flag
    IFSCLR(0) = 0x100;
    timeoutcounter++;
    if ((timeoutcounter % 10) == 0)
    {
      time2string(textstring, mytime);
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      // increment the deferenced pointer by one bit each time tick is called.
      *porte += 0x1;
      display_image(96, icon);
    }
  }

  int btn = getbtns();
  if(btn != 0x0)
  {
    // sw = 4 bits, each bit representing each switch (0 = off, 1 = on) lsb corresponds to SW1.
    int sw = getsw();

    // if btn2 is pressed
    if((btn & 0x1) != 0x0){
      // empties the nibble representing the 3rd digit in clock. Check lab1 instructions for definition of the NBCD encoded clock.
      mytime &= 0xff0f;
      // shifts the switch bits to the correct nibble.
      // adds the bits mytime
      mytime = (sw << 4) | mytime;
    }
    // if btn3 is pressed
    if ((btn & 0x2) != 0x0)
    {
      // empties the nibble representing the 2nd digit in clock.
      mytime &= 0xf0ff;
      // shifts the switch bits to the correct nibble.
      // adds the bits to mytime
      mytime = (sw << 8) | mytime;
    }
    // if btn4 is pressed
    if ((btn & 0x4) != 0x0)
    {
      // empties the nibble representing the 1st digit in clock.
      mytime = mytime & 0x0fff;
      // shifts the switch bits to the correct nibble.
      // adds the bits mytime
      mytime = (sw << 12) | mytime;
    }

  }
  // delay(1000);

}
