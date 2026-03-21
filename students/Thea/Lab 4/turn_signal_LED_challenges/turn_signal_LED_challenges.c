// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

#define DELAYTIME 200 //ms
#define LEDPORT   PORTD

int main(void){
  // Declare variables
  uint8_t bita = 0x00;    /* pattern starts atb 0000 */
  uint8_t bitb = 0x00;

  uint8_t grow = 1;       /* 1 = fill and 0 = empty */
  uint8_t dir = 1;       /* 0 = right and 1 = left */

  // Set up LEDs
  DDRD = 0xff;  // All output

  while(1){
    if (dir == 0) {
      if (grow){
        bita = (bita << 1) | 0x01;
        if (bita == 0x0F) grow = 0;
      }
      else{
        bita = bita << 1;
        if (bita == 0x00) grow = 1;
      }
    PORTD = bita << 4;        
    }
    else{
      if (grow){
        bitb = (bitb >> 1) | 0x08;
        if (bitb == 0x0F) grow = 0;
      }
      else{
        bitb = bitb >> 1;
        if (bitb == 0x00) grow = 1;  
      }
    PORTD = bitb; 
    }
  _delay_ms(DELAYTIME);
  }
return (0);
}