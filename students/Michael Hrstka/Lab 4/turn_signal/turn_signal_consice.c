#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <util/delay.h>

int ledLPos = 0;
int ledRPos = 0;
_Bool rightPressed = 0;
_Bool leftPressed = 0;
_Bool breakPressed = 0;
int hazardTimer = 0;
_Bool hazardLit = 0;
_Bool rightDown = 0;
_Bool leftDown = 0;
_Bool breakDown = 0;
_Bool hazardPressed = 0;

void flashSignal() {

  if(hazardPressed){
    hazardLit ? (PORTD |= 0xFF) : (PORTD &= 0);
    if(hazardTimer < 4) {
      hazardTimer++;
    } else {
      hazardTimer = 0;
      hazardLit = !hazardLit;
    }
  } else {
    if(rightPressed || ledRPos > 0){
      PORTD &= 0b11110000;
      PORTD |= (1 << 3-ledRPos);
      ledRPos = ledRPos < 3 ? ledRPos + 1 : 0;
    } else {
      ledRPos = 0;

      breakPressed ? (PORTD |= 0b00001111) : (PORTD &= 0b11110000);
    }
    if(leftPressed || ledLPos > 0) {
      PORTD &= 0b00001111;
      PORTD |= ((1 << ledLPos)) << 4;
      ledLPos = ledLPos < 3 ? ledLPos + 1 : 0;
    } else {
      ledLPos = 0;
      breakPressed ? (PORTD |= 0b11110000) : (PORTD &= 0b00001111);
    }
  }
}

void checkBtns(){
  _Bool leftClick = bit_is_clear(PINC, 0);
  _Bool rightClick = bit_is_clear(PINC, 2);
  _Bool breakClick = bit_is_clear(PINC, 1);

  if((!leftDown || !rightDown) && leftClick && rightClick){
    hazardPressed = !hazardPressed;
    leftDown = 1;
    rightDown = 1;
    breakDown = 0;
  } else if (!hazardPressed) {
    if(leftDown && !leftClick){
      leftDown = 0;
    } else if (!leftDown && leftClick){
      leftPressed = !leftPressed;
      leftDown = 1;
      rightPressed = 0;
    }

    if(rightDown && !rightClick){
      rightDown = 0;
    } else if (!rightDown && rightClick){
      rightPressed = !rightPressed;
      rightDown = 1;
      leftPressed = 0;
    }
    if(breakDown && !breakClick){
      breakDown = 0;
    } else if (!breakDown && breakClick){
      breakPressed = !breakPressed;
      breakDown = 1;
    }
  } else {
    leftDown && !leftClick && (leftDown = 0);
    rightDown && !rightClick && (rightDown = 0);
  }
}

int main(void){
  // Set up LEDs
  DDRD = 0xff;  // All output
  DDRC = 0x00; // All inputs (cause I'm lazy);
  PORTC = 0xFF; // Pullup

  int counter = 0;
  while(1) {

    _delay_ms(100/4); // Blatently stolen from Dr. Beardsley
    checkBtns();
    counter++;
    if(counter >= 4){
      flashSignal();
      counter = 0;
    }
  }
  return (0);
}
