#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 5

#define BUTTON_PORT PORTC
#define BUTTON_PIN PINC

#define LEFT_BUTTON PC0
#define RIGHT_BUTTON PC1

#define LEFT_LED_DDR DDRB
#define LEFT_LED_PORT PORTB

#define RIGHT_LED_DDR DDRD
#define RIGHT_LED_PORT PORTD

// debounce left and right
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
  LEFT_LED_DDR = 0xff; /* set up LED for output */
  RIGHT_LED_DDR = 0xff; /* set up LED for output */
  int _delay_ = 500;

  // ------ Event loop ------ //



  while (1) {
    if (debounceLeft()) { /* debounced button press */
      if (buttonWasPressed == 0) { /* but wasn't last time through */
       while(2){
        LEFT_LED_PORT = 0b00000001;
        _delay_ms(100);
        LEFT_LED_PORT = 0b00000011;
        _delay_ms(100);
        LEFT_LED_PORT = 0b00000111;
        _delay_ms(100);
        LEFT_LED_PORT = 0b00001111;
        _delay_ms(100);
        LEFT_LED_PORT = 0b00011111;
        _delay_ms(100);
        LEFT_LED_PORT = 0b00111111;
        _delay_ms(100);
        
        LEFT_LED_PORT = 0;
        _delay_ms(100);
       }
        buttonWasPressed = 1; /* update the state */
      }
    }


    else if (debounceRight()) { /* debounced button press */
      if (buttonWasPressed == 0) { /* but wasn't last time through */

        RIGHT_LED_PORT = 0b00000100;
        _delay_ms(100);
        RIGHT_LED_PORT = 0b00001000;
        _delay_ms(100);
        RIGHT_LED_PORT = 0b00010000;
        _delay_ms(100);
        RIGHT_LED_PORT = 0b00100000;
        _delay_ms(100);
        RIGHT_LED_PORT = 0b01000000;
        _delay_ms(100);
        RIGHT_LED_PORT = 0b10000000;
        _delay_ms(100);
        
        RIGHT_LED_PORT = 0;
        _delay_ms(100);
        if (debounceRight()) {
          buttonWasPressed = 1; /* update the state */
        }

      }
    }
    else { /* button is not pressed now */
      buttonWasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */
}
