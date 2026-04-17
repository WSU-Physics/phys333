#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

//Buttons
#define B0 PC4
#define B1 PC5

//LEDs
#define L0 PD0
#define L1 PD1

#define DEBOUNCE_TIME 1000

uint8_t debounce(uint8_t button){
  if (bit_is_clear(PINC, button))
  {
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(PINC, button))
    {
      return (1);
    }
  }
  return (0);
}

int main(void) {
  //Enable Pullup
  PORTC |= (1 << B0) | (1 << B1); 
  DDRC &= ~((1 << B0) | (1 << B1)); //inputs
  DDRD |= (1 << L0) | (1 << L1); //outputs
  uint8_t B0WP = 0; //state
  uint8_t B1WP = 0; //state

  while (1){
    if (debounce(B0)){
      if (B0WP == 0){
        PORTD ^= (1 << L0);
        B0WP = 1;
      }
    }
    else{
      B0WP = 0;
    }
    if (debounce(B1)){
      if (B1WP == 0){
        PORTD ^= (1 << L1);
        B1WP = 1;
      }
    }
    else{
      B1WP = 0;
    }
  }
  
}