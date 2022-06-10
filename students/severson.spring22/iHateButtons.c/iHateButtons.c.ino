/*
  has button been pressed?
  y: do the thing
  n: do nothing

  has button been pressed?
  y: stop doing the thing
  n: do nothing
*/

#include <avr/io.h>
#include <util/delay.h>

#define bounceDelay 1000

#define leftBtn    PB0
#define rightBtn   PB1
#define btnDDR     DDRB
#define btnPort    PORTB
#define btnPin     PINB

#define signalDDR  DDRD
#define signalPort PORTD

uint8_t leftDebounce(void) {
  if ((btnPin & (1 << leftBtn)) == 0) {
    _delay_us(bounceDelay);
    if ((btnPin & (1 << leftBtn)) == 0) {
      return (1);
    }
  }
  return (0);
}

uint8_t rightDebounce(void) {
  if ((btnPin & (1 << rightBtn)) == 0) {
    _delay_us(bounceDelay);
    if ((btnPin & (1 << rightBtn)) == 0) {
      return (1);
    }
  }
  return (0);
}

uint8_t leftTurn(void) {
  uint8_t L;
  for (L = 3; L < 255; L--) {
    signalPort = (1 << L);
    _delay_ms(127);
  }
}

uint8_t rightTurn(void) {
  uint8_t R;
  for (R = 4; R < 8; R++) {
    signalPort = (1 << R);
    _delay_ms(127);
  }
}

int main(void) {

  uint8_t leftSignal;
  uint8_t rightSignal;
  btnDDR = 0x00;
  btnPort = 0xff;
  signalDDR = 0xff;

  while (1) {
    if (leftDebounce()) {
      if (leftSignal == 0) {
        leftSignal = 1;
      }
    }
    else {
      leftSignal = 0;
    }
    while (leftSignal == 1) {
      leftTurn();
    }
  }
}
