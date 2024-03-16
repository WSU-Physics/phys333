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



// Turn Left LED Pattern ------------------------------------
int main(void){
  // Declare variables
  uint8_t i = 0;


  // Set up LEDs
  LED_DDR_L = 0xff;  // All output

  while (1){
    // Main loop
    while(i < 8) {
      LED_PORT_L = (1 << i);
      _delay_ms(DELAYTIME);
      i = i + 1;
      while( i >= 8){
    
        i = 0;
        LED_PORT_L = (1 << i);
      }
    }
    
  }

    return(0);
  }



  // Turn Right LED Pattern -----------------------------
  int main(void){
  // Declare variables
  uint8_t i = 0;
  // Set up LEDs
  LED_DDR_L = 0xff;  // All output

  while (1){
    // Main loop
    i = 8;
    while(i <= 8) {
      LED_PORT_R = (1 << i);
      _delay_ms(DELAYTIME);
      i = i - 1;
      while( i < 0){
        i = 8;
        LED_PORT_R = (1 << i);
      
      }
    }
    
  }

    return(0);
  }

  // Turn Right Button ----------------------------------------------------
  uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {      /* button is pressed now */
   
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_DDR_RB &= ~(1 << BUTTON_RB);      //set BUTTON as an input
  BUTTON_PORT_RB |= (1 << BUTTON_RB);     /* enable the pullup on the button */
  LED_DDR_RB = (1 << LED0_RB);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debounce()) {                        /* debounced button press */
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
        LED_PORT ^= (1 << LED0_RB);                        /* do whatever */
        buttonWasPressed = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}


// Turn Left Button -------------------------------
uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {      /* button is pressed now */
   
    _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void) {
  // -------- Inits --------- //
  uint8_t buttonWasPressed=0;                                 /* state */
  BUTTON_DDR_LB &= ~(1 << BUTTON_LB);      //set BUTTON as an input
  BUTTON_PORT_LB |= (1 << BUTTON_LB);     /* enable the pullup on the button */
  LED_DDR_LB = (1 << LED0_LB);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    if (debounce()) {                        /* debounced button press */
      if (buttonWasPressed == 0) {     /* but wasn't last time through */
        LED_PORT_LB ^= (1 << LED0_LB);                        /* do whatever */
        buttonWasPressed = 1;                      /* update the state */
      }
    }
    else {                                /* button is not pressed now */
      buttonWasPressed = 0;                        /* update the state */
    }

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}

