// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

int ledLPos = 0;
int ledRPos = 0;
int signalActive = 0; // This should eventually be just 3 states: OFF, RIGHT and LEFT (BREAK will still be seperate)
_Bool isRight = 0; // 0: Left, 1: Right

void flashSignal() {
  if(isRight){
    // PORTD = 0b00000000; // Right side off?
    PORTD = (1 << 3-ledRPos); // Set right
    
    ledLPos = 0;
    ledRPos = ledRPos < 3 ? ledRPos + 1 : 0;
  } else {
    // PORTD = 0b00000000; // Left side off
    PORTD = (1 << ledLPos) << 4; // Set left
    ledRPos = 0;
    ledLPos = ledLPos < 3 ? ledLPos + 1 : 0;
  }
}

int main(void){
  // Declare variables
  uint8_t bita; // Do I need these?
  uint8_t bitb;

  // Set up LEDs
  DDRD = 0xff;  // All output
  int stateCnt = 0;

  while(1) {
    if(stateCnt > 15){
      stateCnt = 0;
      isRight = !isRight;
    } else {
      stateCnt++;
    }

    flashSignal();
    _delay_ms(100);
  }
  
  return (0);
}
