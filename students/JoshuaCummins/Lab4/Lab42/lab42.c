#include <avr/io.h>
#include <util/delay.h>

#define LP PORTD //define PORTD to make shorter

int main(void){
  DDRD = 0xFF; //Sets all D to outputs (matches toggle code)

  while (1){
    //Start Right and Left
    // For simplicity (for example with PD3) I bit shit high to PORTD PD3 bit (0b00001000) 
    // The LED off portion "inverse shifts" and/or turns the PD3 bit low. ~ is not command so process goes
    // 0b00000000 -> 0b00001000 -> 0b111101111 (and &) 0b00001000 -> 0b00000000 
    LP |= (1 << PD3) | (1 << PD4); //LEDs On
    _delay_ms(200);
    LP &= ~((1 << PD3) | (1 << PD4)) ; //LED Off
   
    LP |= (1 << PD2) | (1 << PD5);
    _delay_ms(200);
    LP &= ~((1 << PD2) | (1 << PD5)) ;

    LP |= (1 << PD1) | (1 << PD6);
    _delay_ms(200);
    LP &= ~((1 << PD1) | (1 << PD6)) ;

    LP |= (1 << PD0) | (1 << PD7);
    _delay_ms(200);
    LP &= ~((1 << PD0) | (1 << PD7)) ;
  }

  
}