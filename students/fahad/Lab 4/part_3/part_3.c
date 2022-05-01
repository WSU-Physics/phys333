/**
 * A program to control 2 sets of 4 LED to create turn signals
 * Sheikh Fahad 
 * Dr. Adam Beardsley
 * PHYS 333
 * 3/15/2022
 */
 
#include <avr/io.h>
#include <util/delay.h>

// defining macros
#define DEBOUNCE_TIME 10
#define BUTTON_PIN PINB
#define LEFT_BUTTON PB0
#define RIGHT_BUTTON PB1
#define BUTTON_PORT PORTB
#define LED_DDR DDRD
#define LED_PORT PORTD

uint8_t buttonWasPressed; /* state */ // global variable

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
