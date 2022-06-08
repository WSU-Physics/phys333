/*
 * Light up eight LEDs in sequence.
 */

 #include <avr/io.h>  //fetch the avr/io.h library
 #include <util/delay.h>  //fetch the util/delay.h library

 int main(void) { //setup 
  DDRD = 0xff;  //enable all port d pins as output
  
  while (1) { // begin man loop
    PORTD = 0b00000001; //enable PD0 (pin 0)
    _delay_ms(1000);    //delay one second
    PORTD = 0b00000010; //enable PD1 (pin 1)
    _delay_ms(1000);    //delay one second
    PORTD = 0b00000100; //enable PD2 (pin 2)
    _delay_ms(1000);    //delay one second
    PORTD = 0b00001000; //enable PD3 (pin 3)
    _delay_ms(1000);    //delay one second
    PORTD = 0b00010000; //enable PD4 (pin 4)
    _delay_ms(1000);    //delay one second
    PORTD = 0b00100000; //enable PD5 (pin 5)
    _delay_ms(1000);    //delay one second
    PORTD = 0b01000000; //enable PD6 (pin 6)
    _delay_ms(1000);    //delay one second
    PORTD = 0b10000000; //enable PD7 (pin 7)
    _delay_ms(1000);    //delay one second
  }
  return (0);
 }
