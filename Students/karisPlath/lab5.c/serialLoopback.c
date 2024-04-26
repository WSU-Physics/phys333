// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

int main(void) {
  char serialCharacter;
  initUSART();

  // ------ Event loop ------ //
  while (1) {
    serialCharacter = receiveByte();
    if(serialCharacter == 'R'){
      printString("\n");
    }
    transmitByte(serialCharacter);
  }                                             
  return 0;
}