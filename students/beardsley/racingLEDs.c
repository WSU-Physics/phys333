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
  uint8_t bytea = (1 << 7);  // byte to light up LED A
  uint8_t byteb = (1 << 7);  // byte to light up LED B
  uint8_t state = 0;  // Start in state 0
  double ticks = 0;  // Counter to keep track of number of cycles
  int delaypertick = 50;  // ms per tick
  int timea = 15;  // Number of ticks per LED A update
  int timeb = 10;  // Number of ticks per LED B update
  double lasta = 0;  // Last tick that A was updated
  double lastb = 0;  // Last tick that B was updated
  _Bool updateA;  // Flag whether to update A
  _Bool updateB;  // Flag whether to update B

  // Set up LEDs
  DDRD = 0xff;  // All output

  while (1){
    // Main loop
    _delay_ms(delaypertick);
    ticks += 1;
    // CHALLENGE:
    // Make two bouncing LEDs
      // Different speeds
      // what happens when they collide 
        // cancel or stay bright?
        // go through or bounce?

    // Tackle as a state machine
    // state can be 0-3 or a two-bit binary number
    // LSB is state of B, MSB is state of A

    // First decide if either LED needs to be updated
    updateA = (ticks >= lasta + timea);
    if (updateA) lasta = ticks;
    updateB = (ticks >= lastb + timeb);
    if (updateB) lastb = ticks;

    switch (state){
      case 0:
        // A moving right, B moving right
        if (updateA){
          // Shift A to the right one bit
          bytea = (bytea >> 1);
          if (bytea == BV(0)){
            // update A state
            toggleBit(state, 1);
          }
        }
        if (updateB){
          // Shift B to the right one bit
          byteb = (byteb >> 1);
          if (byteb == BV(0)){
            // update B state
            toggleBit(state, 0);
          }
        }
        break;
      case 1:
        // A moving right, B moving left
        if (updateA){
          // Shift A to the right one bit
          bytea = (bytea >> 1);
          if (bytea == BV(0)){
            // update A state
            toggleBit(state, 1);
          }
        }
        if (updateB){
          // Shift B to the left one bit
          byteb = (byteb << 1);
          if (byteb == BV(7)){
            // update B state
            toggleBit(state, 0);
          }
        }
        break;
      case 2:
        // A moving left, B moving right
        if (updateA){
          // Shift A to the left one bit
          bytea = (bytea << 1);
          if (bytea == BV(7)){
            // update A state
            toggleBit(state, 1);
          }
        }
        if (updateB){
          // Shift B to the right one bit
          byteb = (byteb >> 1);
          if (byteb == BV(0)){
            // update B state
            toggleBit(state, 0);
          }
        }
        break;
      case 3:
        // A moving left, B moving left
        if (updateA){
          // Shift A to the left one bit
          bytea = (bytea << 1);
          if (bytea == BV(7)){
            // update A state
            toggleBit(state, 1);
          }
        }
        if (updateB){
          // Shift B to the left one bit
          byteb = (byteb << 1);
          if (byteb == BV(7)){
            // update B state
            toggleBit(state, 0);
          }
        }
        break;
    }
    // Update the actual LEDs
    PORTD = (bytea | byteb);
  }


  return (0);
}
