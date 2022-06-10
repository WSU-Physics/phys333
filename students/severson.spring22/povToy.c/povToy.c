// -------- Preamble -------- //
/*
 Copy stuff from the book.
*/

 // -------- Includes -------- //

#include <avr/io.h>
#include <util/delay.h>

// -------- Globals -------- //

#define povDDR DDRD
#define povPort PORTD

// --------- Functions -------- //

void povDisplay(uint8_t povByte) {
  povPort = povByte;
  _delay_ms(2);
}

int main(void) {
  // -------- Inits -------- //

povDDR = 0xff;

  // -------- Event Loop -------- //
  while(1) {
     povDisplay(0b00001110);
     povDisplay(0b00011000);
     povDisplay(0b10111101);
     povDisplay(0b01110110);
     povDisplay(0b00111100);
     povDisplay(0b00111100);
     povDisplay(0b00111100);
     povDisplay(0b01110110);
     povDisplay(0b10111101);
     povDisplay(0b00001110);
     povDisplay(0b00011000);

     povPort = 0;
     _delay_ms(10);
  }
  return(0);

}
