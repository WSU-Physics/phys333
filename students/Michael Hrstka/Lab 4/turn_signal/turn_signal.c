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

  if(rightPressed && leftPressed){
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
  leftPressed = bit_is_clear(PINC, leftPin);
  rightPressed = bit_is_clear(PINC, rightPin);
  breakPressed = bit_is_clear(PINC, breakPin);
  // NOTE: Pass by ref -> fun(int& i); --> call with: fun(&i);

}

int main(void){
  // Set up LEDs
  DDRD = 0xff;  // All output
  DDRC = 0x00; // All inputs (cause I'm lazy);
  PORTC = 0xFF; // Pullup

  while(1) {

    _delay_ms(tickSpeed); // Blatently stolen from Dr. Beardsley

    checkBtns();

    flashSignal();
  }
  
  return (0);
}
