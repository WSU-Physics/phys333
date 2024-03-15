#include <avr/sfr_defs.h>
// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define clearRight()    PORTD &= 0b11110000;
#define setRight(bit)   PORTD |= (1 << 3-bit);
#define fullRight()     PORTD |= 0b00001111;
#define clearLeft()     PORTD &= 0b00001111;
#define setLeft(bit)    PORTD |= ((1 << bit)) << 4;
#define fullLeft()      PORTD |= 0b11110000;

int ledLPos = 0;
int ledRPos = 0;
int bitOff = 0;
int maxLed = 3;
int tickSpeed = 100;
_Bool rightPressed = 0;
_Bool leftPressed = 0;
_Bool breakPressed = 0;
int leftPin = 0;
int rightPin = 2;
int breakPin = 1;
int hazardTimer = 0;
_Bool hazardLit = 0;
int hazardMaxTime = 4;
_Bool rightDown = 0;
_Bool leftDown = 0;
_Bool breakDown = 0;
_Bool hazardPressed = 0;


void flashRight() {
  clearRight();
  setRight(ledRPos)

  if(ledRPos < maxLed) {
    ledRPos++;
  } else {
    ledRPos = 0;
  }
}

void flashLeft() {
  clearLeft();
  setLeft(ledLPos);

  if(ledLPos < maxLed) {
    ledLPos++;
  } else {
    ledLPos = 0;
  }
}

void flashSignal() {

  if(hazardPressed){
    if(hazardLit) {
      fullRight();
      fullLeft();
    } else {
      clearRight();
      clearLeft();
    }
    if(hazardTimer < hazardMaxTime) {
      hazardTimer++;
    } else {
      hazardTimer = 0;
      hazardLit = !hazardLit;
    }
  } else {
    if(rightPressed || ledRPos > 0){
      flashRight();
    } else {
      ledRPos = 0;

      if(breakPressed)
        fullRight()
      else
        clearRight();
    }
    if(leftPressed || ledLPos > 0) {
      flashLeft();
    } else {
      ledLPos = 0;

      if(breakPressed)
        fullLeft()
      else
        clearLeft();
    }
  }
}

void checkBtns(){
  _Bool leftClick = bit_is_clear(PINC, leftPin);
  _Bool rightClick = bit_is_clear(PINC, rightPin);
  _Bool breakClick = bit_is_clear(PINC, breakPin);

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
    if(leftDown && !leftClick){
      leftDown = 0;
    }
    if(rightDown && !rightClick){
      rightDown = 0;
    }
  }



}

int main(void){
  // Set up LEDs
  DDRD = 0xff;  // All output
  DDRC = 0x00; // All inputs (cause I'm lazy);
  PORTC = 0xFF; // Pullup

  int counter = 0;
  while(1) {

    _delay_ms(tickSpeed/4); // Blatently stolen from Dr. Beardsley
    checkBtns();
    counter++;
    if(counter >= 4){
      flashSignal();
      counter = 0;
    }
  }
  
  return (0);
}
