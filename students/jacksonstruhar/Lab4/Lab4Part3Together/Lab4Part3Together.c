#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 1000

uint8_t debounceLeft(void) {
  if (bit_is_clear(PINB, PB5)) {
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB5)) {
      return 1;
    }
  }
  return 0;
}

uint8_t debounceRight(void) {
  if (bit_is_clear(PINB, PB4)) {
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINB, PB4)) {
      return 1;
    }
  }
  return 0;
}

int main(void) {

  uint8_t buttonWasPressedLeft = 0;
  uint8_t buttonWasPressedRight = 0;

  uint8_t turnLeft = 0;
  uint8_t turnRight = 0;

  uint8_t step = 1;   

  PORTB |= (1 << PB5); //enable pullup
  PORTB |= (1 << PB4);

  DDRD = 0xff;

  while (1) {

    if (debounceLeft()) { //left turn
      if (buttonWasPressedLeft == 0) {
        turnLeft ^= 1;     // toggle
        turnRight = 0;     // turn off other side
        buttonWasPressedLeft = 1;
      }
    } else {
      buttonWasPressedLeft = 0;
    }

    if (debounceRight()) { //right side
      if (buttonWasPressedRight == 0) {
        turnRight ^= 1;
        turnLeft = 0;
        buttonWasPressedRight = 1;
      }
    } else {
      buttonWasPressedRight = 0;
    }

    if (turnLeft) {
      PORTD = ((1 << step) - 1) << (4 - step);  //left 
    }
    else if (turnRight) {
      PORTD = ((1 << step) - 1) << 4;           //right
    }
    else {
      PORTD = 0b00000000;
    }

    step++;
    if (step > 4) step = 1;

    _delay_ms(150); 
  }

  return 0;
}
