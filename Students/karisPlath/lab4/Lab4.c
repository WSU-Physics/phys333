// inits
#include <avr/io.h>
#include <util/delay.h>
#define DEBOUNCE_TIME  5    
#define BUTTON_PIN PINB
#define LEFT PB0
#define RIGHT PB1

uint8_t rightTurn[] = {
  0b00010000,
  0b00110000,
  0b01110000,
  0b11110000,
  0b00000000
};

uint8_t leftTurn[] = {
  0b00001000,
  0b00001100,
  0b00001110,
  0b00001111,
  0b00000000
};

turnOnLED(uint8_t arr[5]){        // runs through the given array
	for (int i = 0; i < 5; i++) {
    PORTD = arr[i];
    _delay_ms(100);
  }
}

uint8_t debouncePress(button) {
  if (bit_is_clear(BUTTON_PIN, button)) {      /* button is pressed now */
    _delay_ms(DEBOUNCE_TIME);
    if (bit_is_clear(BUTTON_PIN, button)) {            /* still pressed */
      return (1);
    }
  }
  return 0;
}

int main(void){
  // init reg
  DDRD |= 0b11111111;
  DDRB |= 0b00000011;
  PORTB |= ((1 << RIGHT) | (1 << LEFT));
  int state = 0;

  while (1) {

    switch (state) {
      case 0:
        // LEDs off
        if(debouncePress(LEFT)){
          state = 1;
        }else if(debouncePress(RIGHT)){
          state = 2;
        }else{
          PORTD = 0;
        }
      break;

      case 1:
        // left turn
        if(debouncePress(LEFT)){
          state = 0;
        }else if(debouncePress(RIGHT)){
          state = 2;
        }else{
          turnOnLED(leftTurn);
        }
      break;

      case 2:
      // right turn
        if(debouncePress(RIGHT)){
          state = 0;
        }else if(debouncePress(LEFT)){
          state = 1;
        }else{
          turnOnLED(rightTurn);
        }
      break;
    }
  }
  return 0;
}