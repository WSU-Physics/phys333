/*
  Adapted from Debouncing code on pg 117 of Make: AVR Programming
  by Williams
  Excluded #include "pinDefines.h" library that can be found on git
  There was a weird error with it and I am using PORTB for buttons rather than PORTD like he is
  Buttons are using PB4 (arduino pin 12) and PB5 (arduino pin 13)
*/

#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 1000 //micros


uint8_t debounceLeft(void) {
  if (bit_is_clear(PINB, PB4)) {   //button pressed
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB, PB4)) { //button still pressed
      return(1);
    }
  }
  return(0);
}
uint8_t debounceRight(void) { 
  if (bit_is_clear(PINB, PB5)) {   //button pressed
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB, PB5)) { //button still pressed
      return(1);
    }
  }
  return(0);

}


int main (void) {
  uint8_t leftButton;
  uint8_t rightButton;
  DDRB = 0x00;  //setting register to input
  PORTB |= (1 << PB5);
  PORTB |= (1 << PB4);  //initialize pullup on input pin
  DDRD = 0xff;  //set up all LEDS for output
  

  while(1) {
    if(debounceLeft()) {   //debounce button press
      if(leftButton == 0) {  //but wasn't last time 
        //do whatever 
        PORTD ^= 0b11110000;
        leftButton = 1; //update the state
      }  
      } else {
        leftButton = 0;
      }
    if(debounceRight()) {
      if(rightButton == 0) {
        PORTD ^= 0b00001111;
        rightButton = 1;
      }
    } else {
      rightButton = 0;
    }
    }  

  
  return(0);
  
}