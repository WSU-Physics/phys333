#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 10

#define ButtonPort PORTB
#define ButtonPin PINB
#define LeftButton PB0
#define RightButton PB1

#define LedDDR DDRD
#define LedPort PORTD





uint8_t debounceLeft (void) {
  if (bit_is_clear(ButtonPin, LeftButton)) {    // button pressed 
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(ButtonPin, LeftButton)) { 
      return (1);
    }
  }
  return (0);
}

uint8_t debounceRight (void) {
  if (bit_is_clear(ButtonPin, RightButton)) { // button pressed 
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(ButtonPin, RightButton)) { 
      return (1);
    }
  }
  return (0);
}

int main(void){
  uint8_t buttonWasPressed =0; /* state */
  uint8_t lastState = 0;
  uint8_t count = 0;
  
  
  ButtonPort |= (1<< LeftButton);         // enable pullup resistor 
  ButtonPort |= (1<< RightButton);
  LedDDR = 0xff;                          //  PORTB  as output 

  int _delay_ = 100;


  while(1){
    if(debounceLeft()){                       // if button is pressed 
     if(buttonWasPressed == 0){
       while(1){
        LedPort = 0b00000001;           // LED on 
        _delay_ms(_delay_);
        LedPort = 0b00000011;
        _delay_ms(_delay_);
        LedPort = 0b00000111;
        _delay_ms(_delay_);
        LedPort = 0b00001111;
        _delay_ms(_delay_);

       
        buttonWasPressed = 1;
   
        }
         
       }
       while(1){
           if (buttonWasPressed = 1){
          LedPort = 0b00000000;

        }
        
     }  
 //
     if(debounceRight()){                       // if button is pressed 
     if(buttonWasPressed == 0){
       while(1){
        LedPort =0b00010000;           // LED on 
        _delay_ms(_delay_);
        LedPort = 0b0110000;
        _delay_ms(_delay_);
        LedPort = 0b01110000;
        _delay_ms(_delay_);
        LedPort = 0b11110000;
        _delay_ms(_delay_);
       
        buttonWasPressed = 1;

        }
        
       }
       while(1){
           if (buttonWasPressed = 1){
          LedPort = 0b00000000;

        }
        
     }  

     
    }

    }


  }

   return(0);

}