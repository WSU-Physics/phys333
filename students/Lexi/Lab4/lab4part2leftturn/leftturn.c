
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRD |= 0xFF; 
  PORTD = 0x00; 

  uint8_t pattern[5] = {
    0b00000000,
    0b00010000, 
    0b00110000, 
    0b01110000, 
    0b11110000
  }; 

  while(1) {
    for(uint8_t i = 0; i < 5; i++) {
      PORTD = pattern[i]; 
      _delay_ms(150); 
    }
  }
  return(0); 
}