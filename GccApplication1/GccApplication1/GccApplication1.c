/*
 * GccApplication1.c
 *
 * Created: 23/04/2014 20:32:44
 *  Author: john
 */ 


#include <avr/io.h>

#include <util/delay.h>                     /* Functions to waste time */


int main(void) {

  // -------- Inits --------- //
  DDRB |= 0b0000001;            /* Data Direction Register B:
                                   writing a one to the bit
                                   enables output. */

  // ------ Event loop ------ //
  
  while (1) {

    PORTB = 0b00000001;          /* Turn on first LED bit/pin in PORTB */
    _delay_ms(100);                                           /* wait */

    PORTB = 0b00000000;          /* Turn off all B pins, including LED */
    _delay_ms(100);                                           /* wait */

  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}