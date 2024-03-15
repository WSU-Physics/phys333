// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
// ---------------
//   Pin Defines
// ---------------

#define LED_PORT                PORTD
#define LED_DDR                 DDRD

#define LED0                    PD0
#define LED1                    PD1
#define LED2                    PD2
#define LED3                    PD3
#define LED4                    PD4
#define LED5                    PD5
#define LED6                    PD6
#define LED7                    PD7

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define BUTTON                  PB0
#define BUTTON2                 PB1
#define DEBOUNCE_TIME  5                            /* microseconds */


chkBtn(int state) {
  if(bit_is_clear(BUTTON_PIN, BUTTON) == 1){
    state = 1;
  }
  else {
    state = 0;  
  }
  return state;
}

int main(void) {
  // -------- Inits --------- //
  BUTTON_PORT |= (1 << BUTTON);     /* enable the pullup on the button */
  LED_DDR = (1 << LED7);                      /* set up LED for output */
  LED_DDR = (1 << LED0);                      /* set up LED for output */
  int buttonstate = 0;

  // ------ Event loop ------ //
  while (1) {
    
    int State = chkBtn(buttonstate);
    if (State == 0) {
      LED_PORT = (1 << LED7);
      LED_PORT &= ~(1 << LED0);

    }
    
    else {
      LED_PORT |= 0b00000000;
    }
  }
  return 0;
}