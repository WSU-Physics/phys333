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
#define LP PORTD //define PORTD to make shorter


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
  DDRD = 0xFF; //outputs
  uint8_t B0WP = 0; //state
  uint8_t B1WP = 0; //state
  uint8_t LFT =0;
  uint8_t RGT = 0;

  while (1){
    if (debounce(B0)) {
      if (B0WP == 0) {
        LFT ^= 1;
        B0WP = 1;
      }
    } 
    else {
      B0WP = 0;
    }
        
   if (debounce(B1)) {
    if (B1WP == 0) {
      RGT ^= 1;
      B1WP = 1;
      }
    } 
    else {
      B1WP = 0;
    }

        
  if (LFT == 1) {
    LP |= (1 << PD3);
    _delay_ms(200);
    LP &= ~(1 << PD3);

    LP |= (1 << PD2);
    _delay_ms(200);
    LP &= ~(1 << PD2);

    LP |= (1 << PD1);
    _delay_ms(200);
    LP &= ~(1 << PD1);

    LP |= (1 << PD0);
    _delay_ms(200);
    LP &= ~(1 << PD0);
        }

       
  if (RGT == 1) {
    LP |= (1 << PD4);
    _delay_ms(200);
    LP &= ~(1 << PD4);

    LP |= (1 << PD5);
    _delay_ms(200);
    LP &= ~(1 << PD5);

    LP |= (1 << PD6);
    _delay_ms(200);
    LP &= ~(1 << PD6);

    LP |= (1 << PD7);
    _delay_ms(200);
    LP &= ~(1 << PD7);
    }
  }
}