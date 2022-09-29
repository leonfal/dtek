#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void)
{
  int swi = (PORTD >> 8) & 0xF;
  return swi;
}

int getbtns(void)
{
  int btn = (PORTD >> 5) & 0x7;
  return btn;
}
