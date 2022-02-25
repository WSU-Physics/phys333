#include <avr/io.h>
#include <util/delay.h> 

#define BUTTON_PIN PIND  
#define BUTTON PD2 
#define LED0 PD7 
#define LED_DDR DDRD 
#define LED_PORT PORTD
#define BUTTON_PORT PORTD
#define DEBOUNCE_TIME 10


int main(void) {
  // ------ Inits ------- //
  uint8_t buttonWasPressed; 
  BUTTON_PORT |= (1 << BUTTON); 
  LED_DDR = (1 << LED0); 

  while(1) {
  if(bit_is_clear(BUTTON_PIN, BUTTON)) {
  if(buttonWasPressed == 0) {
  LED_PORT ^= (1 << LED0); 
  buttonWasPressed = 1; 
  }
  }
  else{
  buttonWasPressed = 0; 
  }
    
}

return(0); 

}


/**
 * 
//int main(void) {
// // -------- Inits --------- //
// uint8_t buttonWasPressed; /* state */
// BUTTON_PORT |= (1 << BUTTON); /* enable the pullup on the button */
// LED_DDR = (1 << LED0); /* set up LED for output */
// // ------ Event loop ------ //
// while (1) {
// if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* button is pressed now */
// if (buttonWasPressed == 0) { /* but wasn't last time through */
// LED_PORT ^= (1 << LED0); /* do whatever */
// buttonWasPressed = 1; /* update the state */
// }
// }
// else { /* button is not pressed now */
// buttonWasPressed = 0; /* update the state */
// }
// } /* End event loop */
// return (0); /* This line is never reached */
//}
