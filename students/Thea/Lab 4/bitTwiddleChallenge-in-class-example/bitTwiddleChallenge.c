// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

#define DELAYTIME 150 //ms
#define LEDPORT   PORTD

int main(void){
  // Declare variables
  uint8_t bita;
  uint8_t bitb;

  // Set up LEDs
  DDRD = 0xff;  // All output

  while (1){
    // Main loop

    //for (bita = 0; bita < 7; bita++) {
      

    //}


    while (bita < 7) {
      LEDPORT = BV(bita);
      _delay_ms(DELAYTIME);
      bita = bita + 1;
      //BV(bitb);
      //setbit(DDRD, 6);
      //_delay_ms(DELAYTIME);
      //bitb = bitb - 1;
    }

    while (bita > 0){
      LEDPORT = BV(bita);
      _delay_ms(DELAYTIME);
      bita = bita - 1;
    }
  }


  return (0);
}
