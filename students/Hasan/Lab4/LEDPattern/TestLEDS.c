/*
 * Test script: Should like up a bank of LEDS connected to PB0-PB5 (Digital pins 8-13)
 */


//------- Preamble ---------- //

#include <avr/io.h> 
#include <util/delay.h> 

int main4(void){

  //-------- Inits -------- // 
  
  DDRB = 0xff; 


  // -------- Event loop ------- // 
  
  int count = 0; 
  while(1) {

    if(count < 6){
      
    //Test each of the lED's
    
    PORTB = (0b00000001 << count); 
    _delay_ms(1000); 
    count+=1;
    
    }

    else{
    PORTB = 0b00000000; 
    _delay_ms(1000);
    count = 0; 

     
   
  }
  }
  
  return (0); 
}
