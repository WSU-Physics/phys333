
// ------- Preamble -------- //
#include <avr/io.h>
#include "pinDefines.h"

#include <util/delay.h>
#define DEBOUNCE_TIME  1000                            /* microseconds */
#define BUTTON PD2
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD
#define LED_DDR DDRB
uint8_t bita;
uint8_t bitb;
uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}
uint8_t leftTurn(void) {
  for(bita=4; bita < 8; bita++){
      PORTD |= (1<<bita); 
      _delay_ms(200);
    }
    PORTD = 0x00;
    _delay_ms(200);
}

uint8_t rightTurn(void) {
  for(bitb=3; bitb != 255; bitb--){
      PORTD |= (1<<bitb); 
      _delay_ms(200);
    }
    PORTD = 0x00;
    _delay_ms(200);
}


int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_PORT |= (1 << BUTTON);     /* enable the pullup on the button */
  // Declare variables
 

  // Set up LEDs
  DDRD = 0xff;  // All output

  // ------ Event loop ------ //
  while (1) {
    if (debounce()) {                        /* debounced button press */
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
        leftTurn();                       /* do whatever */
        buttonWasPressed = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}