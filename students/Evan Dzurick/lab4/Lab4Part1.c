// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define DEBOUNCE_TIME 1000 /* microseconds */
#define LED_PORT                PORTB
#define LED_PIN                 PINB
#define LED_DDR                 DDRB

#define LED0                    PB0
#define LED1                    PB1
#define LED2                    PB2
#define LED3                    PB3
#define LED4                    PB4
#define LED5                    PB5
#define LED6                    PB6
#define LED7                    PB7

#define BUTTON_PORT             PORTD
#define BUTTON_PIN              PIND
#define BUTTON_DDR              DDRD

#define BUTTON                  PD2


uint8_t debounce(void) {
 if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* button is pressed now */
 _delay_us(DEBOUNCE_TIME);
 if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* still pressed */
 return (1);
 }
 }
 return (0);
}
int main(void) {
 // -------- Inits --------- //
 uint8_t buttonWasPressed; /* state */
 BUTTON_PORT |= (1 << BUTTON); /* enable the pullup on the button */

 LED_DDR = (1 << LED0); /* set up LED for output */
 LED_DDR = (1 << LED2); /* set up LED for output */

 // ------ Event loop ------ //
 while (1) {
 if (debounce()) { /* debounced button press */
 if (buttonWasPressed == 0) { /* but wasn't last time through */

 LED_PORT ^= (1 << LED0); /* do whatever */
 LED_PORT ^= (1 << LED2); /* do whatever */

 buttonWasPressed = 1; /* update the state */
 }
 }
 else { /* button is not pressed now */
 buttonWasPressed = 0; /* update the state */
 }
 } /* End event loop */
 return (0); /* This line is never reached */
}
