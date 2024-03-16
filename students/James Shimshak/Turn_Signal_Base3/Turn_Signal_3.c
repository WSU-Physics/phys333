// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// Turn Left Definitions
#define LED_DDR_L               (DDRD)
#define LED_PORT_L              PORTD
#define DELAYTIME 85
#define LED_PIN_L               (PIND)

// Turn Right Definitions
#define LED_DDR_R               (DDRD)
#define LED_PORT_R              PORTD
#define DELAYTIME 85
#define LED_PIN_R               (PIND)

// Turn Left Button
#define LED_DDR_LB               (DDRD)
#define LED_PORT_LB              (PORTD)
#define DELAYTIME 85
#define LED_PIN_LB               (PIND)
#define BUTTON_LB                  PB2
#define LED0_LB                   PD7

#define BUTTON_PORT_LB             PORTB
#define BUTTON_PIN_LB              PINB
#define BUTTON_DDR_LB              DDRB

// Turn Right Button
#define LED_DDR_RB               (DDRD)
#define LED_PORT_RB              (PORTD)
#define DELAYTIME 85
#define LED_PIN_RB               (PIND)
#define BUTTON_RB                  PB4
#define LED0_RB                   PD0

#define BUTTON_PORT_RB             PORTB
#define BUTTON_PIN_RB              PINB
#define BUTTON_DDR_RB              DDRB


#include <util/delay.h>
#define DEBOUNCE_TIME  1000

// Left Button Debounce ----------------------------------------------
uint8_t debounce_L(void) {
  if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {      /* button is pressed now */
   
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

 // Right Button Debounce ----------------------------------------------------
  uint8_t debounce_R(void) {
  if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {      /* button is pressed now */
   
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}


int main(void){
  // Declare variables
  
  // Turn Left Button -------------------------------

  // -------- Inits --------- //
  uint8_t buttonWasPressed_L =0;                                 /* state */
  BUTTON_DDR_LB &= ~(1 << BUTTON_LB);      //set BUTTON as an input
  BUTTON_PORT_LB |= (1 << BUTTON_LB);     /* enable the pullup on the button */
  LED_DDR_LB = (1 << LED0_LB);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debounce_L()) {                        /* debounced button press */
      if (buttonWasPressed_L == 0) {     /* but wasn't last time through */
        LED_PORT_LB ^= (1 << LED0_LB);                        /* do whatever */
        buttonWasPressed_L = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed_L = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */


 //Turn Right Button------------------------------------------------------------
//
  // -------- Inits --------- //
  uint8_t buttonWasPressed_R=0;                                 /* state */
  BUTTON_DDR_RB &= ~(1 << BUTTON_RB);      //set BUTTON as an input
  BUTTON_PORT_RB |= (1 << BUTTON_RB);     /* enable the pullup on the button */
  LED_DDR_RB = (1 << LED0_RB);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debounce_R()) {                        /* debounced button press */
      if (buttonWasPressed_R == 0) {     /* but wasn't last time through */
        LED_PORT_RB ^= (1 << LED0_RB);                        /* do whatever */
        buttonWasPressed_R = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed_R = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */

  
  // Left LED Pattern --------------------------------------------
  uint8_t L = 0;
  // Set up LEDs
  LED_DDR_L = 0xff;  // All output

  while (buttonWasPressed_L == 1){
    // Main loop
    while(L < 8) {
      LED_PORT_L = (1 << L);
      _delay_ms(DELAYTIME);
      L = L + 1;
      while( L >= 8){
    
        L = 0;
        LED_PORT_L = (1 << L);
      }
    }
    
  }

    return(0);
  



  // Turn Right LED Pattern -----------------------------
  // Declare variables
  uint8_t r = 0;


  // Set up LEDs
  LED_DDR_R = 0xff;  // All output

  while ( buttonWasPressed_R == 1){
    // Main loop
    r = 8;
    while(r <= 8) {
      LED_PORT_R = (1 << r);
      _delay_ms(DELAYTIME);
      r = r - 1;
      while( r < 0){
        r = 8;
        LED_PORT_R = (1 << r);
      
      }
    }
    
  }

    return(0);
  // Set up LEDs
  LED_DDR_L = 0xff;  // All output

  while (1){
    // Main loop
    r = 8;
    while(r <= 8) {
      LED_PORT_R = (1 << r);
      _delay_ms(DELAYTIME);
      r = r - 1;
      while( r < 0){
        r = 8;
        LED_PORT_R = (1 << r);
      
      }
    }
    
  }

    return(0);
  




}

