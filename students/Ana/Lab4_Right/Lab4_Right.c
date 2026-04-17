// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit


int main(void){
  // Declare variables
  uint8_t bita = 0;
  uint8_t bitb = 7;

  // Set up LEDs
  DDRD = 0xff;  // All output

  while (1){
    // Main loop

    // CHALLENGE:
    while(bita > 4) {
      PORTD = 0b00000000;
      bita = bita - 1;
      
    }
    while(bita < 8) {
      PORTD = BV( (bita) );
      _delay_ms(175);
      bita = bita + 1;
     
    }
    /*
    while(bita < 4) {
      PORTD = 0b00000000;
      bita = bita + 1;
      
    }
    while(bita > 0) {
      PORTD = BV( (bita - 1) );
      _delay_ms(175);
      bita = bita - 1;
     
    }
    */
  }


  return (0);
}