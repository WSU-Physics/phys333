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
#include <avr/interrupt.h>
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

// TODO:
// x include the interrupt library
// x define ISR 
// x enable specific interrupts, define pins
// x enable sei
// x revisit main loop logic
// x promote state variable

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

ISR(PCINT0_vect){
  // handle the interrupt
  int result = buttonCheck(); // return 1 if R, 2 if L, 0 if neither
  // if Right button -> animate to the right? or turn off if already animating
  if (result == 1){
    // Right button pushed
    if (state == 1){
      // Already turning right, now turn off
      state = 0;
    } else {
      // Start turning right
      state = 1;
    }
  }
  // similar for left
  if (result == 2){
    // Left button pushed
    if (state == 2){
      // Already turning left, now turn off
      state = 0;
    } else {
      // Start turning left
      state = 2;
    }
  }
  // nothing if neither
}

void interrupt_init(void) {
  // using arduino 8 & 9 -> PB0, PB1 for BUTTONR and BUTTONL
  // enable specific interrupts, define pins
  PCICR |= (1 << PCIE0);
  PCMSK0 |= ((1 << PCINT0) | (1 << PCINT1));
  // enable global interrupt
  sei();
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_PORT |= ((1 << BUTTONR) | (1 << BUTTONL));     /* enable the pullup on the button */
  LED_DDR = 0xff;                      /* set up LED for output */
  int delay_time = 200;

  interrupt_init();


  // ------ Event loop ------ //
  while (1) {

    switch (state) {
      case 1:
        // Light LEDs to the right
        if (LED_PORT == 0){
          LED_PORT = (1 << 3);
        }
        else if (LED_PORT == 0x0f){
          LED_PORT = 0;
        } else{
          LED_PORT |= (LED_PORT >> 1);
        }

        break;
      case 2:
        // Light LEDs to the left
        if (LED_PORT == 0){
          LED_PORT = (1 << 4);
        }
        else if (LED_PORT == 0xf0){
          LED_PORT = 0;
        } else{
          LED_PORT |= (LED_PORT << 1);
        }
        
        break;
      default:
        // Off
        LED_PORT = 0;
    }
    _delay_ms(delay_time);


  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
