// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define BUTTON                  PB0
#define BUTTON2                 PB1
#define DELAY  5                            /* microseconds */

// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

int activeState = 0;

/*****************************************************************************************/
leftTurn()  {
  PORTD = 0b00001000;
  for(int i = 3; i <= 8; i++) {
    toggleBit(PORTD, i);
    for(int factorDelay = 0; factorDelay <= 99; factorDelay++) {
      _delay_ms(1);
      if (leftBtn() == 1 | rightBtn()==1){
        break;
      }
    }
  }
  for(int factorDelay = 0; factorDelay <= 99; factorDelay++) {
    _delay_ms(2);
    if (leftBtn() == 1 | rightBtn()==1){
      break;
    }
  }
}

/*****************************************************************************************/
rightTurn() {
  PORTD = 0b00010000;
  for(int i = 4; i >= 0; i--) {
    toggleBit(PORTD, i);
    for(int factorDelay = 0; factorDelay <= 99; factorDelay++) {
      _delay_ms(1);
      if (leftBtn() == 1 | rightBtn() == 1){
        break;
      }
    }
  }
  for(int factorDelay = 0; factorDelay <= 99; factorDelay++) {
    _delay_ms(2);
    if (leftBtn() == 1 | rightBtn() == 1){
      break;
    }
  }
}

/*****************************************************************************************/
leftBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON2)){
    return 1;
  }
  else {
    return 0;  
  }
}

/*****************************************************************************************/
rightBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON)){
    return 1;
  }
  else {
    return 0;  
  }
}

/*****************************************************************************************/
int main(void){
  uint8_t bita;                       //
  uint8_t bitb;                       //
  BUTTON_DDR &= ~(1 << BUTTON);       //
  BUTTON_PORT |= (1 << BUTTON);       //
  BUTTON_DDR &= ~(1 << BUTTON2);      //
  BUTTON_PORT |= (1 << BUTTON2);      //


  // Set up LEDs
  DDRD = 0xff;  // All output

  /****************************
  *This Loops the LED states  *
  ****************************/
  while (1){
    /**********************************
    * This Statement sets the LED     *
    * state to all pins off           *
    **********************************/
    if (activeState == 1) {
      while(rightBtn()==0 && leftBtn()==0 ){
        PORTD = 0b00000000;
      }
      activeState = 0;
    }
    /**********************************
    * This Statement sets the LED     *
    * state to the right turn method  *
    **********************************/
    else if (rightBtn())  {
      while(rightBtn()==1){
        _delay_us(DELAY);
      }

      while(rightBtn()==0 && leftBtn()==0 ){
        rightTurn();
        activeState = 1;
      }  
    }

    /**********************************
    * This Statement sets the LED     *
    * state to the left turn method   *
    **********************************/
    else if (leftBtn())  {
      while(leftBtn() == 1){
        _delay_us(DELAY);
      }

      while(rightBtn()==0 && leftBtn()==0 ){
        leftTurn();
        activeState = 1;
      }
    }
  }
}
