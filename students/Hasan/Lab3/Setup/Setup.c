#include <avr/io.h>
#include <util/delay.h> 

int main(void) {

  //--------- Inits ------------ // 

  DDRD = 0xff;  //get register ready to output - Use D registers

  int count = 0; 
  
// Simple while loop that performs a bit shift until if statement resets counter. 
while (1){
   PORTD = (1 << count); 
   _delay_us(500000);  
   count++;
   if(count == 8){
    count = 0;
     }  
   }
 }
