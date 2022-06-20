/*
   Left signal right signal patterns.
*/

#include <avr/io.h>               //fetch avr/io library
#include <util/delay.h>           //fetch util/delay library

#define signalDelay 100           //define signal delay time milliseconds

#define signalDDR  DDRD           //ddrd used for signals
#define signalPort PORTD          //portd used for signals
#define signalPin  PIND           //pind used for signals

uint8_t leftSignal(void) {        //left signal function
  uint8_t L;                      //variable for the function
  signalPort = 0x00;              //clearing the port
  _delay_ms(signalDelay);         //delay

  for (L = 3; L < 255; L--) {     //for loop
    signalPort |= (1 << L);       //pattern in which the LEDs light up
    _delay_ms(signalDelay);       //delay
  }
}

uint8_t rightSignal(void) {       //right signal function
  uint8_t R;                      //variable for function
  signalPort = 0x00;              //clear signal port
  _delay_ms(signalDelay);         //delay

  for (R = 4; R < 8; R++) {       //for loop
    signalPort |= (1 << R);       //right signal pattern
    _delay_ms(signalDelay);       //delay
  }
}

int main(void) {                  //main function
  signalDDR = 0xff;               //set LED pins as output

  while (1) {                     //while loop
    leftSignal();                 //call left signal function
    signalPort = 0x00;            //clear the port
    _delay_ms(4*signalDelay);     //delay
    rightSignal();                //call right signal function
    signalPort = 0x00;            //clear the port
    _delay_ms(4*signalDelay);     //delay
  }                               //repeat
}
