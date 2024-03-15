// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT                PORTD
#define LED_DDR                 DDRD

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define BUTTON                  PB0
#define BUTTON2                 PB1

#define toggleBit(byte, bit)  (byte ^= (1 << (bit)))


leftBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON2)){
    return 1;
  }
  else {
    return 0;  
  }
}

rightBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON)){
    return 1;
  }
  else {
    return 0;  
  }
}

int main(void){    
  int offState = 0;      
  BUTTON_DDR &= ~(1 << BUTTON);       
  BUTTON_PORT |= (1 << BUTTON);       
  BUTTON_DDR &= ~(1 << BUTTON2);      
  BUTTON_PORT |= (1 << BUTTON2);      
  LED_DDR = 0xff;                     

  while (1){
    if (offState == 1) {
      while (rightBtn() == 1 || leftBtn() == 1){
        _delay_us(1);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        LED_PORT = 0b00000000;
      }
      offState = 0;
    }
    else if (rightBtn())  {
      while(rightBtn()==1){
        _delay_us(1);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        LED_PORT = 0b00010000;
        for(int led = 4; led >= 0; led--) {
          toggleBit(LED_PORT, led);
          for (int delay = 0; delay <= 100; delay++) {
            _delay_ms(1);
            if (leftBtn() == 1 | rightBtn() == 1){
              break;
            }
          }
        }
        for (int delay = 0; delay <= 200; delay++) {
          _delay_ms(1);
          if (leftBtn() == 1 | rightBtn() == 1){
            break;
          }
        }
      }
      if (rightBtn() == 1) {
        offState = 1;
      }
      if (leftBtn() == 1) {
        offState = 0;
      }  
    }
    else if (leftBtn())  {
      while(leftBtn() == 1){
        _delay_us(1);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        LED_PORT = 0b00001000;
        for(int led = 3; led <= 7; led++) {
          toggleBit(LED_PORT, led);
          for (int delay = 0; delay <= 100; delay++) {
            _delay_ms(1);
            if (leftBtn() == 1 | rightBtn() == 1){
              break;
            }
          }
        }
        for (int delay = 0; delay <= 200; delay++) {
          _delay_ms(1);
          if (leftBtn() == 1 | rightBtn() == 1){
            break;
          }
        }
      }
      if (rightBtn() == 1) {
        offState = 0;
      }
      if (leftBtn() == 1) {
        offState = 1;
      }
    }
  }
}
