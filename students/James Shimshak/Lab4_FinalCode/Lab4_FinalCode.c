#include <avr/io.h>
#include <util/delay.h>
#define LED_DDR_L               (DDRD)
#define LED_PORT_L              PORTD
#define DELAYTIME 85
#define LED_DDR_R               (DDRD)
#define LED_PORT_R              PORTD
#define LED_PORT_LB              (PORTD)
#define BUTTON_LB                  PB2
#define LED0_LB                   PD7
#define BUTTON_PORT_LB             PORTB
#define BUTTON_PIN_LB              PINB
#define BUTTON_DDR_LB              DDRB
#define LED_PORT_RB              (PORTD)
#define BUTTON_RB                  PB4
#define LED0_RB                   PD0
#define BUTTON_PORT_RB             PORTB
#define BUTTON_PIN_RB              PINB
#define BUTTON_DDR_RB              DDRB
#include <util/delay.h>


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
  uint8_t I = 0;
  LED_DDR_L = 0xff;  // All output
  LED_DDR_R = 0xff;  // All output

  // -------- Inits --------- //
  uint8_t buttonWasPressed_L = 0;                                 /* state */
  BUTTON_DDR_LB &= ~(1 << BUTTON_LB);      //set BUTTON as an input
  BUTTON_PORT_LB |= (1 << BUTTON_LB);     /* enable the pullup on the button */
  uint8_t buttonWasPressed_R = 0;                                 /* state */
  BUTTON_DDR_RB &= ~(1 << BUTTON_RB);      //set BUTTON as an input
  BUTTON_PORT_RB |= (1 << BUTTON_RB);     /* enable the pullup on the button */


  // ------ Event loop ------ //
  while (1) {
    
  //Turn Left --------------------------------
    
    if (debounce_L()) {                        /* debounced button press */
    while(1){
      if (buttonWasPressed_L == 0) {     /* but wasn't last time through */
         
        while(I < 9) {
          LED_PORT_L = (1 << I);
          _delay_ms(DELAYTIME);
          I = I + 1;
        }
        while( I >= 9){   
          I = 0;
          
          LED_PORT_L = (1 << I);
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
        I = 9;
        while(I > 0) {
          LED_PORT_R = (1 << I);
          _delay_ms(DELAYTIME);
          I = I - 1;
        }
        while( I <= 0){
          I = 9;
          
          LED_PORT_R = (1 << I);      
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

