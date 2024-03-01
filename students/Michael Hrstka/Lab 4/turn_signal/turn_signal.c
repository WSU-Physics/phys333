#include <avr/sfr_defs.h>
// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define setLed(byte) PORTD = byte;

int ledLPos = 0;
int ledRPos = 0;
int bitOff = 0;
int tickSpeed = 100;
_Bool rightPressed = 0;
_Bool leftPressed = 0;
_Bool breakPressed = 0;
int leftPin = 0;
int rightPin = 2;
int breakPin = 1;

void flashRight() {
  setLed(1 << 3-ledRPos); // Set right
    
    ledLPos = 0;

    if(ledRPos < maxLed) {
      ledRPos++;
    } else {
      ledRPos = 0;
    }
}

void flashLeft() {
  setLed((1 << ledLPos) << 4); // Set left
    ledRPos = 0;
    if(ledLPos < maxLed) {
      ledLPos++;
    } else {
      ledLPos = 0;
    }
}

void flashSignal() {

  if(rightPressed){
    flashRight();
  } else if(leftPressed) {
    flashLeft();
  } else {
    ledRPos = 0;
    ledLPos = 0;
    setLed(0x00);
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
