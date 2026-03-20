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
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#include "USART.h"


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
  //initUSART();

  uint8_t leftButton;
  uint8_t rightButton;
  uint8_t tickCounterR = 0;
  uint8_t tickPrevL = 0;
  uint8_t tickR = 10;
  uint8_t tickPrevR = 0;
  _Bool leftTurnOn = 0;
  _Bool rightTurnOn = 0;
  uint8_t bitl = 7;
  uint8_t bitr = 0;
  DDRB = 0x00;  //setting register to input
  PORTB |= (1 << PB5);
  PORTB |= (1 << PB4);  //initialize pullup on input pin
  DDRD = 0xff;  //set up all LEDS for output
  

  while(1) {
    tickCounterR++;

    if(debounceLeft()) {   //debounce button press
      if(leftButton == 0) {  //but wasn't last time 
        leftTurnOn = !leftTurnOn;

        leftButton = 1; //update the state
        
      }  
      } else {
        leftButton = 0;
      }

    if(leftTurnOn) {
      
      PORTD ^= 0b11000000;
    } else {
      PORTD = 0;
    }

    if(debounceRight()) {
      if(rightButton == 0) {
        rightTurnOn = !rightTurnOn;

        rightButton = 1;
      }
    } else {
      rightButton = 0;
    }

    if(rightTurnOn) {
      PORTD = BV(0);  //test for seeing if button works
      // if( (tickCounterR - tickPrevR) > tickR) 
        if( (tickCounterR ) == 10){
          PORTD = BV(1);
          tickCounterR = 0;
        }   

      // } 
        

    } else {
      PORTD = 0;
    }
    
    }  

  
  return(0);
  
}