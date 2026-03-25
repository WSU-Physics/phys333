
#include <avr/io.h>
#include <util/delay.h>

#define RIGHT_BUTTON PB0
#define LEFT_BUTTON PB1
#define HAZARD_BUTTON PB2
#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB
#define LED_DDR DDRD
#define LED_PORT PORTD
#define DEBOUNCE_TIME 1000

uint8_t debounce(uint8_t button) {
  if(bit_is_clear(BUTTON_PIN, button)) {
    _delay_us(DEBOUNCE_TIME); 
    if(bit_is_clear(BUTTON_PIN, button)) {
      return(1); 
    }
  } return(0); 
}

int main(void) {
  uint8_t rightPressed = 0; 
  uint8_t leftPressed = 0; 
  uint8_t hazardPressed = 0; 

  uint8_t rightOn = 0; 
  uint8_t leftOn = 0; 
  uint8_t hazardOn = 0; 

  BUTTON_PORT |= (1 << RIGHT_BUTTON) | (1 << LEFT_BUTTON) | (1 << HAZARD_BUTTON); 
  DDRD = 0xFF; 
  LED_PORT = 0x00; 

  uint8_t rightPattern[4] = { 
    0b00001000, 
    0b00001100, 
    0b00001110, 
    0b00001111
  }; 

  uint8_t leftPattern[4] = {
    0b00010000, 
    0b00110000, 
    0b01110000, 
    0b11110000
  }; 

  uint8_t step = 0; 

  while(1) {
    if(debounce(RIGHT_BUTTON)) {
      if(rightPressed == 0) {
        rightOn ^= 1; 
        leftOn = 0; 
        hazardOn = 0; 
        rightPressed = 1; 
        step = 0; 
      }
    } else {
      rightPressed = 0; 
    }

    if(debounce(LEFT_BUTTON)) {
      if(leftPressed == 0) {
        leftOn ^= 1; 
        rightOn = 0; 
        hazardOn = 0; 
        leftPressed = 1; 
        step = 0; 
      }
    } else {
      leftPressed = 0; 
    }

    if(debounce(HAZARD_BUTTON)) {
      if(hazardPressed == 0) {
        hazardOn ^= 1; 
        rightOn = 0; 
        leftOn = 0; 
        hazardPressed = 1; 
        step = 0; 
      } else {
        hazardPressed = 0; 
      }
    }
    if(hazardOn) {
      LED_PORT = rightPattern[step] | leftPattern[step]; 
      step = (step + 1) % 4; 
      _delay_ms(150); 

    } else if(rightOn) {
      LED_PORT = rightPattern[step]; 
      step = (step +1) % 4; 
      _delay_ms(150); 

    } else if (leftOn) {
      LED_PORT = leftPattern[step]; 
      step = (step + 1) % 4; 
      _delay_ms(150); 

    } else {
      LED_PORT = 0x00; 
    }
  } return(0); 
}