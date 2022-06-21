/*
   Use two buttons, one for left turn, one for right turn.
   When toggled they should activate a signal for the proper direction.
   The signal should activate 4 LEDs in sequence for each direction.
   Use only vanilla C.
*/

#include <avr/io.h>
#include <util/delay.h>

#define signalDelay 100                                 //define signal delay time milliseconds
#define debounceTime 1000                               //debounce time in microseconds

#define buttonPort PORTB                                //port b is used for the buttons
#define buttonPin PINB                                  //pin b is used for the buttons
#define leftButton PB0                                  //left button is pin 8 on arduino uno rev3
#define rightButton PB1                                 //right button is pin 9

#define signalDDR  DDRD                                 //ddrd used for signals
#define signalPort PORTD                                //portd used for signals
#define signalPin  PIND                                 //pind used for signals

uint8_t leftButtonPressed;                              //integer for left button state
uint8_t rightButtonPressed;                             //integer for right button state



uint8_t rightSignal(void) {                             //right signal function
  uint8_t r;                                            //variable for function
  for (r = 4; r < 8; r++) {                             //for loop
    signalPort |= (1 << r);                             //right signal pattern
    _delay_ms(signalDelay);                             //delay
    signalPort = 0x00;
  }
}

uint8_t leftTurn(void) {                                //debounce function for left button
  if ((buttonPin & (1 << leftButton)) == 0) {           //left button is pressed
    _delay_us(debounceTime);                            //delay
    if ((buttonPin & (1 << leftButton)) == 0) {         //left button still pressed
      return (1);
    }
  }
  return (0);
}

uint8_t rightTurn(void) {                               //right button debounce function
  if ((buttonPin & (1 << rightButton)) == 0) {          //right button pressed
    _delay_us(debounceTime);                            //delay
    if ((buttonPin & (1 << rightButton)) == 0) {        //right button still pressed
      return (1);
    }
  }
  return (0);
}

uint8_t leftSignal(void) {                              //left signal function
  uint8_t l;                                            //variable for the function
  if(leftTurn()) {
  if (leftButtonPressed == 1) {
    for (l = 3; l < 255; l--) {                           //for loop
    signalPort |= (1 << l);                             //pattern in which the LEDs light up
    _delay_ms(signalDelay);                             //delay
    signalPort = 0x00;
  }
    leftButtonPressed = 0;
  }
  else {
    leftButtonPressed = 1;
  }
}
}

int main(void) {                                        //main function
  buttonPort |= (1 << leftButton) | (1 << rightButton); //enable pullup on buttons
  signalDDR = 0xff;                                     //prepare LEDs for output

  while (1) {                                           //loop start
    if (leftTurn()) {                                   //if left button pressed
      if (leftButtonPressed == 0) {                     //but wasn't previously
        leftSignal();
        leftButtonPressed = 1;                          //update left button state
      }
    }
    else {                                              //left button not pressed now
      leftButtonPressed = 0;                            //update state
    }
  }

  if (rightTurn()) {                                   //everything is similar, just for the right button & LEDs
    if (rightButtonPressed == 0) {
      rightSignal();
      rightButtonPressed = 1;
    }
  }
  else {
    rightButtonPressed = 0;
  }

  return (0);
}
