#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 10

#define ButtonPort PORTD
#define ButtonPin PIND
#define Button PD3

#define LedDDR DDRB
#define LedPort PORTB
#define LedPin PB0




uint8_t debounce(void) {
  if (bit_is_clear(ButtonPin, Button)) { /* button is pressed now */
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(ButtonPin, Button)) { /* still pressed */
      return (1);
    }
  }
  return (0);
}


int main(void){
  uint8_t buttonWasPressed =0; /* state */
  uint8_t lastState = 0;
  uint8_t LedState = 0;
  
  
  ButtonPort |= (1<< Button);      // enable pullup resistor 
  LedDDR = 0xff;         // set PORTB  as output 

  //int _delay_ = 500;


  while(1){
    if(debounce()){        // if button is pressed 
     if(buttonWasPressed == 0){
       
        LedPort =  0b00000001;
        //_delay_ms(_delay_);
       

      buttonWasPressed = 1;
     }
    }
    if(buttonWasPressed = 1) {
      LedPort =  0b00000000;

    }
    
 
  }
   return(0);




}