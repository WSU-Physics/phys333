//------- Preamble ---------- //

#include <avr/io.h> 
#include <util/delay.h> 


int main(void){

  //-------- Inits -------- // 
  
  DDRB = 0xff;

  DDRD = 0xff; 


  // -------- Event loop ------- // 
  
  int count = 0;

  char state = 'L'; 

  //Serial.begin(9600); 
 
  while(1) {

      // if count is less than 6 light up LEDS
      if(state == 'L') {
        if(count < 4){
          
        //Test each of the lED's
        
        PORTB = (0b00000100 << count); 
        _delay_ms(1000); 
        count+=1;
        
        }
        else{
          PORTB = 0b00000000; 
          _delay_ms(1000);
          count = 0; 
        }
  }
    else if(state == 'R'){
      if(count < 4){
      
      // Light up 3 LEDS in the right direction 
      PORTD = (0b00100000 >> count); 
      _delay_ms(1000); 
      count+=1;

      
    
      }
      else{
        PORTD = 0b00000000; 
        _delay_ms(1000);
        count = 0; ; 
      }
      
    }

    else{
      state = 'L';  
    }
    
  
    
  }

  return (0); 
}
