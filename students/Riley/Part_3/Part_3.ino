// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define LED0 PD3
#define LED1 PD4
#define LED2 PD5
#define LED3 PD6
#define BUTTONR PD2
#define BUTTONL PB1
#define LED_DDR DDRD
#define LED_DDR2 DDRB
#define BUTTON_PORTL PORTB
#define BUTTON_PINL PINB
#define BUTTON_PORTR PORTD
#define BUTTON_PINR PIND
#define LED_PORTR PORTD
#define LED_PORTL PORTB
#define DELAYTIME 1000
#define DEBOUNCE_TIME 1000

int debounce(void) {
 if (bit_is_clear(BUTTON_PINR, BUTTONR)) { /* button is pressed now */
  _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PINR, BUTTONR)) { /* still pressed */
 return (1);
  }
 }
 
 if (bit_is_clear(BUTTON_PINL, BUTTONL)) { /* button is pressed now */
  _delay_us(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PINL, BUTTONL)) { /* still pressed */
 return (2);
  }
 }
 return (0);
}
int main(void) {
 Serial.begin(9600);
 int i;
 int RbuttonWasPressed; 
 int LbuttonWasPressed;/* state */
 LED_DDR = 0b01111100;
 LED_DDR2 = 0b00011111;
 BUTTON_PORTR |= (1 << BUTTONR); /* enable the pullup on the button */
 BUTTON_PORTL |= (1 << BUTTONL); /* enable the pullup on the button */


 while (1) {
 if (debounce()== 1) { /* debounced button press */
 if (RbuttonWasPressed == 0) { /* but wasn't last time through */
     for (i = 7; i >2; i--) {
      LED_PORTR = (1 << i);                    /* turn on the i'th pin */
      _delay_ms(DELAYTIME);                                   /* wait */
    }
  }
 }
 else{
  RbuttonWasPressed = 0;
 }
 if (debounce()== 2) {
  if (LbuttonWasPressed == 0){
     for (i = 2; i < 6; i++) {
      LED_PORTL = (1 << i);                    /* turn on the i'th pin */
      _delay_ms(DELAYTIME);  
     }
  }
 }


 else {
 LbuttonWasPressed = 0;
  }

 } /* End event loop */
   return (0);
}
