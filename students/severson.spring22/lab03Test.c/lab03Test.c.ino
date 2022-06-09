/*
 * A simple program to light up eight LEDs sequentially.
 */

#include <avr/io.h>                     //fetch avr/io.h library
#include <util/delay.h>                 //fetch util/delay.h library

int main(void) {                        //declare main function
  DDRD = 0xff;                          //enable all port D pins as output

  while (1) {                           //while true, run this program.
    for (uint8_t i = 0; i < 8; i++) {   //for loop, initially set i = 0. check if i < 8. if yes run program then update i to i+1. if no set i = 0.
      PORTD = (1 << i);                 //bit shifting portd
      _delay_ms(100);                   //delay for designated time
    }
  }
}
