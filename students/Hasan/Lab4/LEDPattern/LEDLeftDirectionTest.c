//Left direction Test file 


//------- Preamble ---------- //

#include <avr/io.h> 
#include <util/delay.h> 

int main2(void){

  //-------- Inits -------- // 
  
  DDRB = 0xff; 


  // -------- Event loop ------- // 

  //Start count
  int count = 0; 

  
  while(1) {

    // If count is less than 3 
    if(count < 3){
      
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
}
