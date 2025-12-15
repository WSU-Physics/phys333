//Lab 4 

// ------- Preamble -------- //
#include <avr/io.h>                        // Defines pins, ports, etc //
#include <util/delay.h>                     // Functions to waste time //
#include <time.h> 
#define DEBOUNCE_TIME 1000                  // Debounce delay //
#define DELAY_TIME 300                      // Blink delay // 

// Button for left turn Debouncer 
uint8_t debounce(void) {
  if (bit_is_clear(PINB,PB0)) {
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB,PB0)){
      return(1);
    }
  }
  return(0);
}

uint8_t debounceR(void) {
  if (bit_is_clear(PINB,PB1)) {
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(PINB,PB1)){
      return(1);
    }
  }
  return(0);
}

     void shiftRight(){
      for (int i=4; i<8; i++) {
        PORTD = (1<<i);
        _delay_ms(DELAY_TIME);
      }
    }
     void shiftLeft() {
  for (int i = 3; i>=0; i--) {
    PORTD = (1<<i);
    _delay_ms(DELAY_TIME);
  }
  
}

//Part 1 - ToggleButton

int main(void) {

  // -------- Inits --------- //
  uint8_t buttonpressed;
  DDRB &= ~(1<<PB0);          // Button for left turn as input 
  PORTB |= (1<<PB0);
  DDRB &= ~(1<<PB1);          // Button for right turn as input 
  PORTB |= (1<<PB1);
  DDRD |= 0b11111111;         // PORTD as output for LEDs
  int buttonLeft = 0;             // Interger for button toggle 
  int buttonRight = 0;

time_t start,end;
double dif;

time (&start);
  


  // ------ Event loop ------ //
  while (1) {
    if (debounce()){
    if (bit_is_clear(PINB, PB0)) {
      if (buttonpressed==0) {
        buttonLeft = !buttonLeft;

    

        
        buttonpressed=1;
      }
    }
    }
  
      if (debounceR()){
    if (bit_is_clear(PINB, PB1)) {
      if (buttonpressed==0) {
        buttonRight = !buttonRight;

    

        
        buttonpressed=1;
      }
    }
    }

    else {
   buttonpressed=0;
    }
    if(buttonLeft) {
     // time (&end);
//dif = difftime (end,start);
//if (dif > 300) {

      shiftLeft();
      //time (&start);
//}
    }
    if (buttonRight) {
      shiftRight();
    }
  }

    return(0);
}