//Left direction Test file 


//------- Preamble ---------- //

#include <avr/io.h> 
#include <util/delay.h> 

int main3(void){

  //-------- Inits -------- // 
  
  DDRB = 0xff; 


  // -------- Event loop ------- // 
  
  int count = 0; 
  while(1) {
    if(count < 3){
      
    // Light up 3 LEDS in the right direction 
    
    PORTB = (0b00000100 >> count); 
    _delay_ms(1000); 
    count+=1;
    
    }

    else{
      //Reset counter and start over  
    PORTB = 0b00000000; 
    _delay_ms(1000);
    count = 0; 

     
   
    }
  }
}
