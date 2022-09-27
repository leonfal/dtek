#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void )
{
  volatile int *z = PORTD;
  *z = (*z & 0x00000f00) >> 8;

  return *z;
}

int getbtns(void)
{
  volatile int *z = PORTD;
  *z = (*z & 0x000000e0) >> 5;

  return *z;
}
