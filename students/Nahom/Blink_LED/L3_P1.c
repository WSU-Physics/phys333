
#include <avr/io.h> 
#include <util/delay.h> 


int main(void) {
  
  
  DDRD = 0xff; 

  int i;
  while (1) {

    for(i=0 ; i<=7; i= i+1){
      PORTD = (1 << i);
      _delay_ms(20);
    }

    for (i=7 ; i>=0; i= i-1){
      PORTD = (1 << i);
      _delay_ms(20);
    }
  }
   
}
