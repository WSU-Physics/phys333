// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

#define DEBOUNCE_TIME   1000 //us
#define DELAYTIME 200 //ms
#define LEDPORT   PORTD

// ------ Debounce Functions ------//
uint8_t debounceRight(void) {
  if (bit_is_clear(PINB, PB5)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB5)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}
uint8_t debounceLeft(void) {
  if (bit_is_clear(PINB, PB4)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB4)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void){
  // Declare variables
  uint8_t bita = 0x00;    /* pattern starts at 0000 */
  uint8_t bitb = 0x00;

  uint8_t rightWasPressed = 0;
  uint8_t leftWasPressed = 0;

  uint8_t grow = 1;       /* 1 = fill and 0 = empty */
  uint8_t dir = 0;       /* 0 = right and 1 = left */
  uint8_t run = 0;      /* signal OFF = 0 and ON = 1 */

  // Set up LEDs
  DDRD = 0xff;  // All output

  //set up buttons
  DDRB = 0x00;  //All Input
  PORTB = (1 << PB5) | (1 << PB4);


  while(1){
    //----Debounce Right----//
    if (debounceRight()) {
      if (rightWasPressed == 0) {
        toggleBit(run,0);             /* flip ON/OFF */
        dir = 0;                     /* RIGHT */
        bita = 0x00;                    /* reset */
        grow = 1;
        rightWasPressed = 1;
      }
    }
    else{
      rightWasPressed = 0;
    }
    //----Debounce Left----//
    if (debounceLeft()) {
      if (leftWasPressed == 0) {
        toggleBit(run,0);             /* flip ON/OFF */
        dir = 1;                     /* LEFT */
        bitb = 0x00;                   /* reset */
        grow = 1;
        leftWasPressed = 1;
      }
    }
    else{
      leftWasPressed = 0;
    }

// -------- LED pattern code -------- //
    if (run){
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
    }
    else {
      PORTD = 0x00;
    }
    _delay_ms(DELAYTIME);
    }
return (0);
}