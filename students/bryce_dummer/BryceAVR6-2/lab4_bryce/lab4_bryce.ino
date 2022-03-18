/*
   Demonstrates using state to detect button presses
*/

// ------- Preamble -------- //
#include <avr/io.h>
#define LED5 PD2
#define BUTTON PD7
#define BUTTON_PIN PIND
#define BUTTON_PORT PORTD
#define LED_DDR DDRD
#define LED_PORT PORTD


#include <util/delay.h>
#define DEBOUNCE_TIME  5   /* microseconds */

void POVDisplay(uint8_t oneByte) {
  PORTD = oneByte;
  _delay_ms(100);//speed
}

uint8_t debouncePress(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {      /* button is pressed now */
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_PORT |= (1 << BUTTON);     /* enable the pullup on the button */
  LED_DDR = (1 << LED5);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debouncePress()) {
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
            POVDisplay(0b00100000);
            POVDisplay(0b00010000);
            POVDisplay(0b00001000);
            POVDisplay(0b00000100);           
            PORTD = 0;
                       /* do whatever */
        buttonWasPressed = 1;                      /* update the state */
      }
    }
    else {   
            POVDisplay(0b00000100);
            POVDisplay(0b00001000);
            POVDisplay(0b00010000);
            POVDisplay(0b00100000); 
      /* button is not pressed now */
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
