#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRD = 0xff;

  while (1) {
    for (int i = 0; i < 8; i++) {
      PORTD = (1 << i);
      _delay_ms(100);
    }
  }

}
