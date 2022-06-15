/*
 *  The Button Test.
 */

 #include <avr/io.h>                                    //fetches the avr/io library
 #include <util/delay.h>                                //fetches the util/delay library

 #define debounceTime 1000                              //debounce time in microseconds

#define buttonPort PORTB                                //port b is used for the buttons
#define buttonPin PINB                                  //pin b is used for the buttons
#define leftButton PB0                                  //left button is pin 8 on arduino uno rev3
#define rightButton PB1                                 //right button is pin 9

#define signalDDR DDRD                                  //ddrd for the LEDs 
#define signalPort PORTD                                //portd for the LEDs
#define leftLED PD0                                     //left LED is on pin 0
#define rightLED PD7                                    //right LED is on pin 7

 uint8_t leftDebounce(void) {                           //debounce function for left button
  if ((buttonPin & (1 << leftButton)) == 0) {           //left button is pressed
    _delay_us(debounceTime);                            //delay
    if ((buttonPin & (1 << leftButton)) == 0) {         //left button still pressed
      return (1);
    }
  }
  return (0);
 }
 
 uint8_t rightDebounce(void) {                          //right button debounce function
  if ((buttonPin & (1 << rightButton)) == 0) {          //right button pressed
    _delay_us(debounceTime);                            //delay
    if ((buttonPin & (1 << rightButton)) == 0) {        //right button still pressed
      return (1);
    }
  }
  return (0);
 }

int main(void) {                                        //main function
  uint8_t leftButtonPressed;                            //integer for left button state
  uint8_t rightButtonPressed;                           //integer for right button state
  buttonPort |= (1 << leftButton)|(1 << rightButton);   //enable pullup on buttons
  signalDDR = 0xff;                                     //prepare LEDs for output

  while (1) {                                           //loop start
    if (leftDebounce()) {                               //if left button pressed
      if (leftButtonPressed == 0) {                     //but wasn't previously
        signalPort ^= (1 << leftLED);                   //turn on/off the left LED
        leftButtonPressed = 1;                          //update left button state
      }
    }
    else {                                              //left button not pressed now
      leftButtonPressed = 0;                            //update state
    }
    if (rightDebounce()) {                              //everything is similar, just for the right button & LED
      if (rightButtonPressed == 0) {
        signalPort ^= (1 << rightLED);
        rightButtonPressed = 1;
      }
    }
    else {
      rightButtonPressed = 0;
    }
  }
  return (0);
}
