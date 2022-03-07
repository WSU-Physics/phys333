//------- Preamble ---------- //

#include <avr/io.h> 
#include <util/delay.h> 
#include "USART.h" 

int main(void){

  //-------- Inits -------- // 
  
  DDRB = 0xff;
  char Direction; 
  char placeHolder;
  initUSART(); 
  printString("Hello World!\r\n"); 


  // -------- Event loop ------- // 
  
  int count = 0;
 
  while(1) {
    
    Direction = receiveByte();
    transmitByte(Direction); 

    if(Direction == 'L'){
      placeHolder = 'L';
    }
    else if(Direction == 'R'){
      placeHolder = 'R';
    }

    else{
      printString("Invalid"); 
    }
  
    while(placeHolder == 'L'){  
      if(count < 6){
        
      //Test each of the lED's
      
      PORTB = (0b00001000 << count); 
      _delay_ms(1000); 
      count+=1;
      
      }
      else{
        PORTB = 0b00000000; 
        _delay_ms(1000);
        count = 0; 
      }
    }

    while(placeHolder == 'R'){
      if(count < 3){
      
      // Light up 3 LEDS in the right direction 
    
      PORTB = (0b00000100 >> count); 
      _delay_ms(1000); 
      count+=1;
    
      }
      else{
        PORTB = 0b00000000; 
        _delay_ms(1000);
        count = 0; ; 
      }
    }
  
    
  }

  return (0); 
}
