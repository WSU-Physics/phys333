#include <avr/io.h>
#include <util/delay.h> 

/--------- Button 1 -------- / 
#define BUTTON_PIN PIND  
#define BUTTON PD2 
#define LED0 PD7 
#define LED_DDR DDRD 
#define LED_PORT PORTD
#define BUTTON_PORT PORTD
#define DEBOUNCE_TIME 10

/-------- Button 2 --------- /

#define BUTTON_PIN2 PINB
#define Button PB
#define LED
#define LED_DDR_2 DDRB
#define LED_PORT_2 PORTB
#define BUTTON_PORT_2 PORTB
define DEBOUNCE_TIME 10


int main(void) {
  // ------ Inits ------- //

  //Button 1 
  uint8_t buttonWasPressed; 
  BUTTON_PORT |= (1 << BUTTON); 
  LED_DDR = (1 << LED0); 

  //Button 2 

  while(1) {

  //button 1 
  if(bit_is_clear(BUTTON_PIN, BUTTON)) {
  if(buttonWasPressed == 0) {
  LED_PORT ^= (1 << LED0); 
  buttonWasPressed = 1; 
    }
  }
  else{
  buttonWasPressed = 0; 
  }

  //button 2 
  
}

return(0); 

}
