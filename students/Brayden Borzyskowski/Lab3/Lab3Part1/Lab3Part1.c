#include <avr/io.h>         // Defines pins, ports, etc
#include <util/delay.h>    // Functions to waste time

int main(void)
{
  //---Inits---//
  DDRD |= 0b11111111;   // data direction register B: writing a one to the bit enables the output


  //---Event Loop---//
  while (1)
  {
     PORTD = 0b00000001;   // Turn on first LED bit/pin in PORTB for pin 0
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b00000010;   // Turn on first LED bit/pin in PORTB for pin 1
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b00000100;   // Turn on first LED bit/pin in PORTB for pin 2
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b00001000;   // Turn on first LED bit/pin in PORTB for pin 3
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b00010000;   // Turn on first LED bit/pin in PORTB for pin 4
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b00100000;   // Turn on first LED bit/pin in PORTB for pin 5
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);


    PORTD = 0b01000000;   // Turn on first LED bit/pin in PORTB for pin 6
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);

    PORTD = 0b10000000;   // Turn on first LED bit/pin in PORTB for pin 0
    _delay_ms(1000);      // wait

    PORTD = 0b00000000;   // Turn off al B pins, including LED
    _delay_ms(1000);
  }
  return 0;               // this line is never reached
}