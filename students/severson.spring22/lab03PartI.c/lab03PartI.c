/*
 * Light up eight LEDs in sequence.
 */

 #include <avr/io.h>      //fetch the avr/io.h library
 #include <util/delay.h>  //fetch the util/delay.h library

 int main(void) {         //setup 
  DDRD = 0xff;            //enable all port d pins as output
  
  while (1) {             // begin main loop
    PORTD = 0b00000001;   //turn all portd pins off except pin 0
    _delay_ms(100);       //delay
    PORTD = 0b00000010;   //turn all portd pins off except pin 1
    _delay_ms(100);       //delay
    PORTD = 0b00000100;   //turn all portd pins off except pin 2
    _delay_ms(100);       //delay 
    PORTD = 0b00001000;   //turn all portd pins off except pin 3
    _delay_ms(100);       //delay
    PORTD = 0b00010000;   //turn all portd pins off except pin 4
    _delay_ms(100);       //delay 
    PORTD = 0b00100000;   //turn all portd pins off except pin 5
    _delay_ms(100);       //delay 
    PORTD = 0b01000000;   //turn all portd pins off except pin 6
    _delay_ms(100);       //delay 
    PORTD = 0b10000000;   //turn all portd pins off except pin 7
    _delay_ms(100);       //delay 
  }
  return (0);
 }
