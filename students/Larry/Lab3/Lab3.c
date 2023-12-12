#include <avr/io.h>
#include <util/delay.h>


int main(void) {

 // DDRB = 0b00000001;
 // DDRB = 0b00000011;
  //DDRB = 0b00000111;
  //turns all portB and port D register as output registers
  DDRB = 0b11111111;
  DDRD = 0b11111111;
 
  
  

  while(1){
   
   //set all Port B and D to high
    PORTB = 0b11111111;
    PORTD = 0b11111111;;
    
   //delay
   
    _delay_ms(1000);
    //Sets all port B and D to LOW
    PORTB = 0b00000000;
    PORTD = 0b00000000;
    
    //delay
    _delay_ms(1000);
    
  }
return (0);

}
