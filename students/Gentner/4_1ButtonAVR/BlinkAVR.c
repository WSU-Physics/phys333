// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

//Pin Defines
#define LED_PORT                PORTD
#define LED_PIN                 PIND
#define LED_DDR                 DDRD
#define LED0                    PD0 //R
#define LED1                    PD1 //G
#define LED2                    PD2 //B
#define LED3                    PD3 //W
#define LED4                    PD4 //W
#define LED5                    PD5 //B
#define LED6                    PD6 //G
#define LED7                    PD7 //R
//Buttons
#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB
#define BUTTON                  PB0

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

//debounce equation grabbed from AVR
#define DEBOUNCE_TIME 1000 //in ms
uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {      /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void) {

uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_PORT |= (1 << BUTTON);     /* enable the pullup on the button */
  LED_DDR = (1 << LED0);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debounce()) {                        /* debounced button press */
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
        LED_PORT ^= (1 << LED0);                        /* do whatever */
        buttonWasPressed = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */


  // -------- Inits --------- //
  DDRD |= 0b11111111;            /* Data Direction Register D:

  return 0;                            /* This line is never reached */
}