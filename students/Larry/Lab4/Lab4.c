#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 500
#define BUTTON_PIN PINC
#define BUTTON PC4
#define BUTTON_PORT PORTC
#define BUTTON2 PC5
//#define BUTTON



uint8_t debounce (void){
  if(bit_is_clear(BUTTON_PIN, BUTTON)){
    
    _delay_us(DEBOUNCE_TIME);
    
    if(bit_is_clear(BUTTON_PIN, BUTTON)){
      
      return(1);
      
    }
  }
  
  return(0);
}

int main(void) {
  uint8_t buttonWasPressed;
  uint8_t button2WasPressed;
  BUTTON_PORT |= (1<< BUTTON);
  BUTTON_PORT |= (1<< BUTTON2);
  

  DDRD = 0b11111111;
  //DDRD = 0b01111000;
  


  while(1){
    if(debounce()){
      if(buttonWasPressed ==0){      
    
    PORTD = 0b11111111;

    buttonWasPressed =1;
      }
      else{
        buttonWasPressed = 0;
        //PORTD = 0b00000000;
        
      }
    }

    if(debounce()){
      button2WasPressed = 0;
      if(button2WasPressed == 0){

        PORTD = 0b11110000;
        
        

        button2WasPressed = 1;
      }
      else{
        button2WasPressed = 0;
        //PORTD = 0b00000000;
      }
     
    }



    return(0);
  }
//return (0);

}
