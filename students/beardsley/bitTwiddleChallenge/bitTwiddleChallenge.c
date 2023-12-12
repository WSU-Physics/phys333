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
  uint8_t bita;
  uint8_t bitb;

  // Set up LEDs
  DDRD = 0xff;  // All output

  while (1){
    // Main loop

    // CHALLENGE:
    // Make two bouncing LEDs
      // Different speeds
      // what happens when they collide 
        // cancel or stay bright?
        // go through or bounce?
    
  }


  return (0);
}
