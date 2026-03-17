

#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 10  //micros


uint8_t debounce(void) {
  if (bit_is_clear(PINB, PB4)) {   //button pressed
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB, PB4)) { //button still pressed
      return(1);
    }
  }
  return(0);
  /*
  if (bit_is_clear(PINB, PB5)) {   //button pressed
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB, PB5)) { //button still pressed
      return(1);
    }
  }
  return(0);
  */
}


int main (void) {
  DDRB = 0x00;  //setting register to input
  //PORTB |= (1 << PB5);
  PORTB |= (1 << PB4);  //initialize pullup on input pin
  DDRD = 0xff;  //set up all LEDS for output
  uint8_t buttonWasPressed;

  while(1) {
    if(debounce()) {   //debounce button press
      if(buttonWasPressed == 0) {  //but wasn't last time 
        //do whatever 
        PORTD ^= 0b11110000;
        buttonWasPressed = 1; //update the state
      } else {
        buttonWasPressed = 0;
      }
    }
    
  }
  
  return(0);
}