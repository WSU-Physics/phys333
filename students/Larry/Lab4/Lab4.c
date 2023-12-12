#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME 500
#define BUTTON_PIN PINC
#define BUTTON PC4
#define BUTTON_PORT PORTC
#define BUTTON2 PC5


//#define BUTTON

  uint8_t buttonWasPressed = 0;
  uint8_t button2WasPressed = 0;

uint8_t debounce (b){
  if(bit_is_clear(BUTTON_PIN, b)){
    
    _delay_us(DEBOUNCE_TIME);
    
    if(bit_is_clear(BUTTON_PIN, b)){
      
      return(1);
      
    }
  }
  
  return(0);
}
/*
uint8_t debounce2 (void){
  if(bit_is_clear(BUTTON_PIN, BUTTON2)){
    
    _delay_us(DEBOUNCE_TIME);
    
    if(bit_is_clear(BUTTON_PIN, BUTTON2)){
      
      return(1);
      
    }
  }
  
  return(0);
}
*/
uint8_t buttonPressed(void){
  if(debounce(BUTTON)){
    return(1);
    
  }
  if(debounce(BUTTON2)){
    return(2);
  }
  

  /*
  if(bit_is_clear(BUTTON_PIN2, BUTTON2 )){
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(BUTTON_PIN2, BUTTON2)){
      return(2);
    
    }
  }
  if(bit_is_clear(BUTTON_PIN, BUTTON )){
    _delay_us(DEBOUNCE_TIME);
    if(bit_is_clear(BUTTON_PIN, BUTTON)){
      return(1);
    }
    */
  

    return(0);
 
  
}

int main(void) {

  BUTTON_PORT |= ((1<< BUTTON) | (1<< BUTTON2));
  //BUTTON_PORT2 |= (1<< BUTTON2);
  //int b = buttonPressed(BUTTON2);
  //int b2 = buttonPressed(BUTTON);
  

  DDRD = 0b11111111;
  DDRC = 0b00000000;
  


  while(1){
    if(buttonPressed() == 1){
      if(buttonWasPressed == 0){ 
        if(PORTD == 0b00000000){
               
          PORTD = 0b11110000;
        }
        else{
          PORTD = 0b00000000;
        }

    buttonWasPressed = 1;
      }
      else{
        buttonWasPressed = 0;
        PORTD = 0b00000000;
        
      }
    }

   if(buttonPressed() == 2){
      //button2WasPressed = 0;
      if(button2WasPressed == 0){
        if(PORTD == 0b00000000){

        PORTD = 0b00001111;
        }
        else{
          PORTD = 0b00000000;
          
        }
        

        button2WasPressed = 1;
      }
      else{
        button2WasPressed = 0;
        PORTD = 0b00000000;
      }
     
    }



    return(0);
  }
return (0);

}
