

/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/


//-I (Include path) set up in project properties for C++. This will find headers
// -L (Librabry Path) set up in project properties for linker.

#define F_CPU 16000000UL

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

int main(void) {
  char serialCharacter;

  // -------- Inits --------- //
  LED_DDR = 0xff;                            /* set up LEDs for output */
  initUSART();
  printString("Hello World!\r\n");                          /* to test */

  // ------ Event loop ------ //
  while (1) {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    LED_PORT = serialCharacter;
                           /* display ascii/numeric value of character */

  }                                                  /* End event loop */
  return (0);
}
