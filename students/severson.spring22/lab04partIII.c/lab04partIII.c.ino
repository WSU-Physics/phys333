/*
   Use two buttons, one for left turn, one for right turn.
   When toggled they should activate a signal for the proper direction.
   The signal should activate 4 LEDs in sequence for each direction.
   Use only vanilla C.
*/

#include <avr/io.h>
#include <util/delay.h>

#define signalDelay 100                                 //define signal delay time milliseconds
#define debounceTime 10000                              //debounce time in microseconds

#define buttonPort PORTB                                //port b is used for the buttons
#define buttonPin PINB                                  //pin b is used for the buttons
#define leftButton PB0                                  //left button is pin 8 on arduino uno rev3
#define rightButton PB1                                 //right button is pin 9

#define signalDDR  DDRD                                 //ddrd used for signals
#define signalPort PORTD                                //portd used for signals
#define signalPin  PIND                                 //pind used for signals

uint8_t leftButtonPressed;                              //integer for left button state
uint8_t rightButtonPressed;                             //integer for right button state

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
  for (l = 3; l < 255; l--) {                           //for loop
    signalPort |= (1 << l);                             //pattern in which the LEDs light up
    _delay_ms(signalDelay);                             //delay
    if (leftTurn()) {                                   //call debounce function for left button
      if (leftButtonPressed == 1) {                     //if state has changed
        leftButtonPressed = 0;                          //update state
      }
      else {                                            //if state has not changed
        leftButtonPressed = 1;                          //state remains the same
      }
    }
  }
  signalPort = 0x00;                                    //turning all LEDs off before signal runs again
}

uint8_t rightSignal(void) {                             //right signal function
  uint8_t r;                                            //variable for function
  for (r = 4; r < 8; r++) {                             //for loop
    signalPort |= (1 << r);                             //right signal pattern
    _delay_ms(signalDelay);                             //delay
    if (rightTurn()) {                                  //debounce function for right button
      if (rightButtonPressed == 1) {                    //if state has changed
        rightButtonPressed = 0;                         //update state
      }
      else {                                            //if state has not changed
        rightButtonPressed = 1;                         //state remains the same
      }
    }
  }
  signalPort = 0x00;                                    //turn all LEDs off before loop runs again
}




int main(void) {                                        //main function
  buttonPort |= (1 << leftButton) | (1 << rightButton); //enable pullup on buttons
  signalDDR = 0xff;                                     //prepare LEDs for output
  signalPort = 0x00;

  while (1) {                                           //loop start
    if (leftTurn()) {                                   //if left button pressed
      if (leftButtonPressed == 0) {                     //but wasn't previously
        leftButtonPressed = 1;                          //update left button state
        while (leftButtonPressed == 1) {                //while in this state
          leftSignal();                                 //call left signal function
          _delay_ms(5 * signalDelay);                   //delay
        }
      }
    }
    else {                                              //left button not pressed now
      leftButtonPressed = 0;                            //state retains previous value
    }

    if (rightTurn()) {                                   //everything is similar, just for the right button & LEDs
      if (rightButtonPressed == 0) {
        rightButtonPressed = 1;
        while (rightButtonPressed == 1) {
          rightSignal();
          _delay_ms(5 * signalDelay);
        }
      }
      else {
        rightButtonPressed = 0;
      }
    }
  }
  return (0);
}