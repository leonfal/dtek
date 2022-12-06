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
int timeoutcount = 0;
int prime = 1234567;

// volatile pointer to point to adress where PORTE is.
volatile int *porte = (volatile int*)0xbf886110;

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & (1 << 7))
  {
    *porte += 0x1;
    IFSCLR(0) = (1 << 7);
  }
  // if flag is 1, reset event.
  // Timer 2 interrupt flag. Can be found at bit 8 in IFS0
  if((IFS(0) & 0x100) != 0)
  {
    // reset flag
    IFSCLR(0) = 0x100;
    timeoutcount++;
    if ((timeoutcount % 10) == 0)
    {
      time2string(textstring, mytime);
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
    }
  }

  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // IPC: A three bit field in the IPC register contains the interrupt priority

  // IEC: A one bit field in the IEC register contains the interrupt enable flag. Interrupts for the related source are only acknowledged when the related bit in the IEC register is set one.
  // Set flag in IEC register
  IECSET(0) = (1 << 8);
  // Set a non zero priority
  IPCSET(2) = (1 << 2);
  // volatile pointer to point to adress where TRISE is.
  volatile int *trise = (volatile int*)0xbf886100;
  // sets 8 lsb to 0 (output) using bitwise inverse.
  *trise &= ~0xff;
  // initialize the leds to off.
  *porte = 0x0;

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
  // Enable interrupts for timer t2
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();

}
