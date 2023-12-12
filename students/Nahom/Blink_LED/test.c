#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 10

#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB
#define BUTTON1 PB0
#define BUTTON2 PB1

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED0 PD6
#define LED1 PD7

 plat= Serial.begin(9600);


uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON1 )) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON1)) { /* still pressed */
      return (1);
    }
  }
  return (0);

  if (bit_is_clear(BUTTON_PIN, BUTTON2 )) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, BUTTON2)) { /* still pressed */
      return (1);
    }
  }
  return (0);
}
                  /*
uint8_t debounce(void) {
  if(BUTTON_PIN & (1 << BUTTON1)  ==0){
    _delay_us(DEBOUNCE_TIME);
    if(BUTTON_PIN & (1 << BUTTON1)  ==0){
      return (1);
    }
  }
  return (0);
}
*/
int main(void) {
  // -------- Inits --------- //
  uint8_t button_1_WasPressed; /* state */
  uint8_t button_2_WasPressed; /* state */  
  
  BUTTON_PORT |= (1 << BUTTON1); /* enable the pullup on the button */
  LED_DDR = (1 << LED0); /* set up LED for output */
  // ------ Event loop ------ //
  while (1) {
    if (debounce()) { /* debounced button press */
      if (button_1_WasPressed == 0) { /* but wasn't last time through */
        LED_PORT ^= (1 << LED0); /* do whatever */
        
        button_1_WasPressed = 1; /* update the state */
      }
    }
    else { /* button is not pressed now */
      button_1_WasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */



  BUTTON_PORT |= (1 << BUTTON2); /* enable the pullup on the button */
  LED_DDR = (1 << LED1); /* set up LED for output */
  // ------ Event loop ------ //
  while (1) {
    if (debounce()) { /* debounced button press */
      if (button_2_WasPressed == 0) { /* but wasn't last time through */
        LED_PORT ^= (1 << LED1); /* do whatever */
        button_2_WasPressed = 1; /* update the state */
      }
    }
    else { /* button is not pressed now */
      button_2_WasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */
}
