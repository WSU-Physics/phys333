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
  uint8_t L = 0;
  uint8_t R = 8;
  LED_DDR_L = 0xff;  // All output
  LED_DDR_R = 0xff;  // All output
  LED_DDR_RB = 0xff;
  LED_DDR_LB = 0xff;


  // -------- Inits --------- //
  uint8_t buttonWasPressed_L = 0;                                 /* state */
  BUTTON_DDR_LB &= ~(1 << BUTTON_LB);      //set BUTTON as an input
  BUTTON_PORT_LB |= (1 << BUTTON_LB);     /* enable the pullup on the button */
  //LED_DDR_LB = (1 << LED0_LB);                      /* set up LED for output */
  uint8_t buttonWasPressed_R = 0;                                 /* state */
  BUTTON_DDR_RB &= ~(1 << BUTTON_RB);      //set BUTTON as an input
  BUTTON_PORT_RB |= (1 << BUTTON_RB);     /* enable the pullup on the button */
  //LED_DDR_LB = (1 << LED0_LB);                      /* set up LED for output */

  // ------ Event loop ------ //
  while (1) {
    
  //Turn Left --------------------------------
    
    if (debounce_L()) {                        /* debounced button press */
    while(1){
      if (buttonWasPressed_L == 0) {     /* but wasn't last time through */
         
        while(L < 9) {
          LED_PORT_L = (1 << L);
          _delay_ms(DELAYTIME);
          L = L + 1;
        }
        while( L >= 9){   
          L = 0;
          
          LED_PORT_L = (1 << L);
        }
      }
                            /* update the state */  
      if(debounce_L()) {
        return 0;
        _delay_ms(DELAYTIME);
        return 1;
        break;
        
                                      /* button is not pressed now */
        
                            /* update the state */
      }
    }
    }
                                                    /* End event loop */
    
    

 //Turn Right Button------------------------------------------------------------



  // ------ Event loop ------ //
  
    if (debounce_R()) {                        /* debounced button press*/ 
    while(1) {
      if (buttonWasPressed_R == 0) {     /* but wasn't last time through*/
        R = 9;
        while(R > 0) {
          LED_PORT_R = (1 << R);
          _delay_ms(DELAYTIME);
          R = R - 1;
        }
        while( R <= 0){
          R = 9;
          
          LED_PORT_R = (1 << R);      
        }
      } 
      if (debounce_R()) {
        return 0;
        _delay_ms(DELAYTIME);  
        return 1;
        break;                            /* button is not pressed now */ 
         
                          /* update the state */ 
      }
    }                                                  /* End event loop */
  }
  }

  

}

