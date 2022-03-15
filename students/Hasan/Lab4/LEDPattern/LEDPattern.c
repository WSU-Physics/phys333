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

  int on; 

  while(1){
    
    on = (count < 4) ? 1:0; 
    switch(state){
      case 'L':
        
        switch(on){
         
          case 1:
            while(on == 1){
            
              PORTB = (0b00000100 << count); 
              _delay_ms(1000); 
              count+=1;

              }
          }
          
          default:
            
              PORTB = 0b00000000; 
              _delay_ms(1000);
              count = 0;
           
            
        

      case 'R':
         on = (count < 4) ? 1:0;
         
         switch(on){
          
          case 1:         
            // Light up 3 LEDS in the right direction
            while(1){
              PORTD = (0b00100000 >> count); 
              _delay_ms(1000); 
              count+=1;
              on = (count < 4) ? 1:0;
              
            }
            
          default:
           
               PORTD = 0b00000000; 
              _delay_ms(1000);
              count = 0;
                
         }
      }
    }
    return (0); 
}
  
