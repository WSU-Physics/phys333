#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

int main(void) {
  char serialCharacter;

  DDRD |= 0b11111100;
  DDRB |= 0b11000000;
  initUSART();

  while (1) {

    serialCharacter = receiveByte();
    PORTD = serialCharacter << 2;
    PORTB = serialCharacter >> 6;
    if(serialCharacter == 'R') serialCharacter = '\n';
    transmitByte(serialCharacter);
  }
  return 0;
}
