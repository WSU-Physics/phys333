#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 10
#define BUTTON_PIN PINB
#define LEFT_BUTTON PB0
#define RIGHT_BUTTON PB1
#define BUTTON_PORT PORTB
#define LED_DDR DDRD
#define LED_PORT PORTD

//Challenge 2: Really spelling out the code
uint8_t debounceLeft(void) {
  if (bit_is_clear(BUTTON_PIN, LEFT_BUTTON)) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, LEFT_BUTTON)) { /* still pressed */
      return (1);
    }
  }
  return (0);
}

uint8_t debounceRight(void) {
  if (bit_is_clear(BUTTON_PIN, RIGHT_BUTTON)) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, RIGHT_BUTTON)) { /* still pressed */
      return (1);
    }
  }
  return (0);
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed; /* state */
  BUTTON_PORT |= (1 << LEFT_BUTTON); /* enable the pullup on the button */
  BUTTON_PORT |= (1 << RIGHT_BUTTON); /* enable the pullup on the button */
  LED_DDR = 0xff; /* set up LED for output */
  int _delay_ = 150;
  // ------ Event loop ------ //
  while (1) {
    if (debounceLeft()) { /* debounced button press */
      if (buttonWasPressed == 0) { /* but wasn't last time through */
        while (buttonWasPressed != 1) {
          LED_PORT = 0b00010000;
          _delay_ms(_delay_);
          if (debounceLeft()) {
            buttonWasPressed = 1 ;
          }
          LED_PORT = 0b00110000;
          _delay_ms(_delay_);
          if (debounceLeft()) {
            buttonWasPressed = 1 ;
          }
          LED_PORT = 0b01110000;
          _delay_ms(_delay_);
          if (debounceLeft()) {
            buttonWasPressed = 1 ;
          }
          LED_PORT = 0b11110000;
          _delay_ms(_delay_);
          if (debounceLeft()) {
            buttonWasPressed = 1 ;
          }
          LED_PORT = 0;
          _delay_ms(_delay_);
          if (debounceLeft()) {
            buttonWasPressed = 1 ;
          }
        }
      }
    }
    else if (debounceRight()) { /* debounced button press */
      if (buttonWasPressed == 0) { /* but wasn't last time through */
        while (buttonWasPressed != 1) {
          LED_PORT = 0b00001000;
          _delay_ms(_delay_);
          if (debounceRight()) {
            buttonWasPressed = 1; /* update the state */
          }
          LED_PORT = 0b00001100;
          _delay_ms(_delay_);
          if (debounceRight()) {
            buttonWasPressed = 1; /* update the state */
          }
          LED_PORT = 0b00001110;
          _delay_ms(_delay_);
          if (debounceRight()) {
            buttonWasPressed = 1; /* update the state */
          }
          LED_PORT = 0b00001111;
          _delay_ms(_delay_);
          if (debounceRight()) {
            buttonWasPressed = 1; /* update the state */
          }
          LED_PORT = 0;
          _delay_ms(_delay_);
          if (debounceRight()) {
            buttonWasPressed = 1; /* update the state */
          }
        }
      }
    }
    else { /* button is not pressed now */
      buttonWasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */
}
