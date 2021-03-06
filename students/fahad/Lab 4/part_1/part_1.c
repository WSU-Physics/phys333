#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 10
#define BUTTON_PIN PINB
#define BUTTON PB0
#define BUTTON_PORT PORTB
#define LED_DDR DDRD
#define LED0 PD6
#define LED_PORT PORTD


uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* still pressed */
      return (1);
    }
  }
  return (0);
}
int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed; /* state */
  BUTTON_PORT |= (1 << BUTTON); /* enable the pullup on the button */
  LED_DDR = (1 << LED0); /* set up LED for output */
  // ------ Event loop ------ //
  while (1) {
    if (debounce()) { /* debounced button press */
      if (buttonWasPressed == 0) { /* but wasn't last time through */
        LED_PORT ^= (1 << LED0); /* do whatever */
        buttonWasPressed = 1; /* update the state */
      }
    }
    else { /* button is not pressed now */
      buttonWasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */
}
