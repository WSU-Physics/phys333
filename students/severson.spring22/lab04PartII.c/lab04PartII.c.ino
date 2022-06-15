/*
   Left turn right turn patterns.
*/

#include <avr/io.h>
#include <util/delay.h>

#define signalDelay 125

#define signalDDR  DDRD
#define signalPort PORTD
#define signalPin  PIND

uint8_t leftSignal(void) {
  uint8_t L;
  signalPort = 0x00;
  _delay_ms(signalDelay);

  for (L = 3; L < 255; L--) {
    signalPort |= (1 << L);
    _delay_ms(signalDelay);
  }
}

uint8_t rightSignal(void) {
  uint8_t R;
  signalPort = 0x00;
  _delay_ms(signalDelay);

  for (R = 4; R < 8; R++) {
    signalPort |= (1 << R);
    _delay_ms(signalDelay);
  }
}

int main(void) {
  DDRD = 0xff;

  while (1) {
    leftSignal();
    rightSignal();
  }
}
