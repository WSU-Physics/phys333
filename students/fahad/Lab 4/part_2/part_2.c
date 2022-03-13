#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 10
#define BUTTON_PIN PINB
#define LEFT_BUTTON PB0
#define RIGHT_BUTTON PB1
#define BUTTON_PORT PORTB
#define LED_DDR DDRD
#define LED_PORT PORTD

////Challenge 2: really spelling out the code
//uint8_t debounceLeft(void) {
//  if (bit_is_clear(BUTTON_PIN, LEFT_BUTTON)) { /* button is pressed now */
//    _delay_us(DEBOUNCE_TIME);
//    if (bit_is_clear(BUTTON_PIN, LEFT_BUTTON)) { /* still pressed */
//      return (1);
//    }
//  }
//  return (0);
//}
//
//uint8_t debounceRight(void) {
//  if (bit_is_clear(BUTTON_PIN, RIGHT_BUTTON)) { /* button is pressed now */
//    _delay_us(DEBOUNCE_TIME);
//    if (bit_is_clear(BUTTON_PIN, RIGHT_BUTTON)) { /* still pressed */
//      return (1);
//    }
//  }
//  return (0);
//}
//
//int main(void) {
//  // -------- Inits --------- //
//  uint8_t buttonWasPressed; /* state */
//  BUTTON_PORT |= (1 << LEFT_BUTTON); /* enable the pullup on the button */
//  BUTTON_PORT |= (1 << RIGHT_BUTTON); /* enable the pullup on the button */
//  LED_DDR = 0xff; /* set up LED for output */
//  int _delay_ = 150;
//  // ------ Event loop ------ //
//  while (1) {
//    if (debounceLeft()) { /* debounced button press */
//      if (buttonWasPressed == 0) { /* but wasn't last time through */
//        while (buttonWasPressed != 1) {
//          LED_PORT = 0b00010000;
//          _delay_ms(_delay_);
//          if (debounceLeft()) {
//            buttonWasPressed = 1 ;
//          }
//          LED_PORT = 0b00110000;
//          _delay_ms(_delay_);
//          if (debounceLeft()) {
//            buttonWasPressed = 1 ;
//          }
//          LED_PORT = 0b01110000;
//          _delay_ms(_delay_);
//          if (debounceLeft()) {
//            buttonWasPressed = 1 ;
//          }
//          LED_PORT = 0b11110000;
//          _delay_ms(_delay_);
//          if (debounceLeft()) {
//            buttonWasPressed = 1 ;
//          }
//          LED_PORT = 0;
//          _delay_ms(_delay_);
//          if (debounceLeft()) {
//            buttonWasPressed = 1 ;
//          }
//        }
//      }
//    }
//    else if (debounceRight()) { /* debounced button press */
//      if (buttonWasPressed == 0) { /* but wasn't last time through */
//        while (buttonWasPressed != 1) {
//          LED_PORT = 0b00001000;
//          _delay_ms(_delay_);
//          if (debounceRight()) {
//            buttonWasPressed = 1; /* update the state */
//          }
//          LED_PORT = 0b00001100;
//          _delay_ms(_delay_);
//          if (debounceRight()) {
//            buttonWasPressed = 1; /* update the state */
//          }
//          LED_PORT = 0b00001110;
//          _delay_ms(_delay_);
//          if (debounceRight()) {
//            buttonWasPressed = 1; /* update the state */
//          }
//          LED_PORT = 0b00001111;
//          _delay_ms(_delay_);
//          if (debounceRight()) {
//            buttonWasPressed = 1; /* update the state */
//          }
//          LED_PORT = 0;
//          _delay_ms(_delay_);
//          if (debounceRight()) {
//            buttonWasPressed = 1; /* update the state */
//          }
//        }
//      }
//    }
//    else { /* button is not pressed now */
//      buttonWasPressed = 0; /* update the state */
//    }
//  } /* End event loop */
//  return (0); /* This line is never reached */
//}

// challenge 3: make code as short as possible
uint8_t buttonWasPressed; /* state */ // global variable in order to use it in turn method

// debounce method consisting of left button and right button
uint8_t debounce(int button) {
  if (bit_is_clear(BUTTON_PIN, button)) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, button)) { /* still pressed */
      buttonWasPressed = 1;
      return (1);
    }
  }
  return (0);
}

// turn method to send bits to port and also check for left or right button click
void turn(uint8_t oneByte) {
  LED_PORT = oneByte;
  _delay_ms(150);

  if (debounce(LEFT_BUTTON) | debounce(RIGHT_BUTTON)) {
    buttonWasPressed = 0;
  }
}
int main(void) {
  // -------- Inits --------- //
  uint8_t turnBits[] = {0x10, 0x30, 0x70, 0xF0, 0, 0x8, 0xC, 0xE, 0xF, 0}; //declaring and creating an array with hex digits of the bits to turn LEDs on.
  BUTTON_PORT |= (1 << LEFT_BUTTON); /* enable the pullup on the button */
  BUTTON_PORT |= (1 << RIGHT_BUTTON); /* enable the pullup on the button */
  LED_DDR = 0xff; /* set up LED for output */
  // ------ Event loop ------ //
  while (1) {
    if (debounce(LEFT_BUTTON)) { /* debounced button press */
      while (buttonWasPressed != 0) {
        for (int i = 0; i < 5; i++) {
          turn(turnBits[i]);
        }
      }
    }
    else if (debounce(RIGHT_BUTTON)) { /* debounced button press */
      while (buttonWasPressed != 0) {
        for (int i = 5; i < 10; i++) {
          turn(turnBits[i]);
        }
      }
    }
    else { /* button is not pressed now */
      buttonWasPressed = 0; /* update the state */
    }
  } /* End event loop */
  return (0); /* This line is never reached */
}
