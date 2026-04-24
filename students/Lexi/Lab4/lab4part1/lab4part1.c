
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON PB0 
#define LED PD0
#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB 
#define LED_DDR DDRD
#define LED_PORT PORTD 
#define DEBOUNCE_TIME 1000 

uint8_t debounce(void) {
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {
    _delay_us(DEBOUNCE_TIME); 
    if(bit_is_clear(BUTTON_PIN, BUTTON)) {
      return (1); 
    }
  }
  return (0); 
} 

int main(void) {
  uint8_t buttonPressed = 0; 
  uint8_t ledState = 0; 

  BUTTON_PORT |= (1 << BUTTON); 
  DDRD |= 0xFF; 
  PORTD = 0x00; 

  while(1) {
    if(debounce()) {
      if(buttonPressed == 0) {
        ledState ^= 1; 
        if(ledState) {
          LED_PORT |= (1 << LED); 
        } else {
          LED_PORT &= ~(1<< LED); 
        }
        buttonPressed = 1; 
      }
    } else {
      buttonPressed = 0; 
    }
  }
  return (0); 
}