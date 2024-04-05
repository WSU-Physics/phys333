/*
 * The following is my solution to Lab 4
 * where we created R and L turn signals.
 * It is now our task to rewrite this
 * to use interrupts.
 * You may choose to rewrite your own solution
 * if you prefer.
 */

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME  5                               /* microseconds */
#define LED_DDR DDRD
#define LED_PORT PORTD
#define BUTTON_DDR DDRB
#define BUTTON_PORT PORTB
#define BUTTON_PIN PINB
#define BUTTONR PB0
#define BUTTONL PB1

uint8_t buttonPressedR = 0;
uint8_t buttonPressedL = 0;
int state = 0;

uint8_t debouncePress(button) {
  if (bit_is_clear(BUTTON_PIN, button)) {      /* button is pressed now */
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, button)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

uint8_t buttonCheck(void) {
  // Check if button is pushed, return 1 if Right, 2 if Left, 0 otherwise
  if (debouncePress(BUTTONR)){
    if (buttonPressedR == 0){
      buttonPressedR = 1;
      return (1);
    }
  } else {
    buttonPressedR = 0;
  }

  if (debouncePress(BUTTONL)){
    if (buttonPressedL == 0){
      buttonPressedL = 1;
      return (2);
    }
  } else {
    buttonPressedL = 0;
  }

  return (0);
}

updateState(){
  int result = buttonCheck();
  
}

void initInterupt0(void) {
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  sei();
}

ISR(PCINT0_vect){
  updateState();
}


int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_PORT |= ((1 << BUTTONR) | (1 << BUTTONL));     /* enable the pullup on the button */
  LED_DDR = 0xff;                      /* set up LED for output */
  int tick = 0;
  int tick_ms = 10;
  int delay_ticks = 20;
  int last_change = 0;
  initInterupt0();


  // ------ Event loop ------ //
  while (1) {

    switch (state) {
      case 1:
        // Light LEDs to the right
        if (tick - last_change >= delay_ticks){
          if (LED_PORT == 0){
            LED_PORT = (1 << 3);
          }
          else if (LED_PORT == 0x0f){
            LED_PORT = 0;
          } else{
            LED_PORT |= (LED_PORT >> 1);
          }
          last_change = tick;
        }
        
        if (buttonCheck() == 1){
          state = 0;
        }
        break;
      case 2:
        // Light LEDs to the left
        if (tick - last_change >= delay_ticks){
          if (LED_PORT == 0){
            LED_PORT = (1 << 4);
          }
          else if (LED_PORT == 0xf0){
            LED_PORT = 0;
          } else{
            LED_PORT |= (LED_PORT << 1);
          }
          last_change = tick;
        }
        
        if (buttonCheck() == 2){
          state = 0;
        }
        break;
      default:
        // Off
        LED_PORT = 0;
        state = buttonCheck();
    }
    _delay_ms(tick_ms);
    tick++;


  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
