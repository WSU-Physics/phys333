// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>


//--Potentially useful macros--//
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

//------Define Variables -----//
#define DEBOUNCE_TIME   1000 //us
#define DELAYTIME 150 //ms
#define LEDPORT   PORTD

uint8_t debounce(void) {
  if (bit_is_clear(PINB, PB5)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB5)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed = 0;                 /* button state */
  DDRB = 0x00;                                 /* set all Port B pins as Input*/
  setBit(PORTB,PB5);                          /* enable the pullup on the button */                        
  //PORTB |= (1 << PB4);                     /* pullup on my Left Button*/
  DDRD = 0xff;                              /* set up LED for output */
  uint8_t bita;
  uint8_t bitb;

  // ------ Event loop ------ //
  while (1) {
    if (debounce()) {                        /* debounced button press */
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
        PORTD = 0b11111111;
        buttonWasPressed = 1;                      /* update the state */ 
        }
      }
    else {                                /* button is not pressed now */
      PORTD = 0b00000000;
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}