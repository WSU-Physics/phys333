// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT                PORTD
#define LED_DDR                 DDRD

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define BUTTON                  PB0
#define BUTTON2                 PB1

#define BV(bit)               (1 << (bit))       // Mask with single bit set
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

int offState = 0;  //This variable goes between 0 and 1 and controls when all lights turn off
int delay;         //This is used in my for loops and is used as the integer increaded to our maximum time
int led;           //This variable is used to determine which LED 0-7 is turned on
int time;          //This variable is used with the method variableDelay() and is our value for waited time in milliseconds
/***********************************************************************************************

This method activates the state for my leds to shift from pin 3 to 7 first it initializes

the third pin and changes its state which turns it off because I have it initiallly set to

on this is unnoticable and it alowed me to have all the LED's turn on/off not the first one

constantly be on I could fix this without turning the 3rd LED on but that would involve

another delay and I don't want that. This method also calls the varriableDelay() twice the

first delay is roughly 100ms the second takes place after they are all turned on and is 200ms
***********************************************************************************************/
leftTurn()  {
  LED_PORT = 0b00001000;
  for(led = 3; led <= 7; led++) {
    toggleBit(LED_PORT, led);
    variableDelay(100);
  }
  variableDelay(200);
}
/***********************************************************************************************

This method activates the state for my leds to shift from pin 4 to 0 first it initializes

the fourth pin and changes its state which turns it off because I have it initiallly set to

on this is unnoticable and it alowed me to have all the LED's turn on/off not the first one

constantly be on I could fix this without turning the 4th LED on but that would involve

another delay and I don't want that. This method also calls the varriableDelay() twice the

first delay is roughly 100ms the second takes place after they are all turned on and is 200ms
***********************************************************************************************/
rightTurn() {
  LED_PORT = 0b00010000;
  for(led = 4; led >= 0; led--) {
    toggleBit(LED_PORT, led);
    variableDelay(100);
  }
  variableDelay(200);
}
/***********************************************

This method checks to see if the left button

was clicked then returns 1 if yes and 0 if no
***********************************************/
leftBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON2)){
    return 1;
  }
  else {
    return 0;  
  }
}
/***********************************************

This method checks to see if the right button 

was clicked then returns 1 if yes and 0 if no 
***********************************************/
rightBtn() {
  if(bit_is_clear(BUTTON_PIN, BUTTON)){
    return 1;
  }
  else {
    return 0;  
  }
}
/*******************************************************************************

This method takes an integer value and stores it as a temporary variable 

time Then the delay lasts for the input delay time in milliseconds              
*******************************************************************************/
variableDelay(time) {
  for (delay = 0; delay <= time; delay++) {
    _delay_ms(1);
    if (leftBtn() == 1 | rightBtn() == 1){
      break;
    }
  }
}
/**************
* Main Method *
**************/
int main(void){
  uint8_t bita;                       //unused
  uint8_t bitb;                       //unused
  BUTTON_DDR &= ~(1 << BUTTON);       //activates input
  BUTTON_PORT |= (1 << BUTTON);       //activates resistor
  BUTTON_DDR &= ~(1 << BUTTON2);      //activates input
  BUTTON_PORT |= (1 << BUTTON2);      //activates resistor
  LED_DDR = 0xff;                     // All output

  /****************************
  * This Loops the LED states *
  ****************************/
  while (1){
    /**********************************
    * This Statement sets the LED     *
    * state to all pins off           *
    **********************************/
    if (offState == 1) {
      while (rightBtn() == 1 || leftBtn() == 1){
        _delay_us(5);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        LED_PORT = 0b00000000;
      }
      offState = 0;
    }
    /************************************
    * This Statement sets the LED       *
    * state to the right turn method    *
    * if the right button is hit a      *
    * second time the loop ends and     *
    * all LED's are turned off but if   *
    * the left button is hit it         *
    * merely activates the other lights.* 
    ************************************/
    else if (rightBtn())  {
      while(rightBtn()==1){
        _delay_us(5);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        rightTurn();
      }
      if (rightBtn() == 1) {
        offState = 1;
      }
      if (leftBtn() == 1) {
        offState = 0;
      }  
    }
    /************************************
    * This Statement sets the LED       *
    * state to the left turn method     *
    * if the left button is hit a       *
    * second time the loop ends and     *
    * all LED's are turned off but if   *
    * the right button is hit it        *
    * merely activates the other lights.* 
    ************************************/
    else if (leftBtn())  {
      while(leftBtn() == 1){
        _delay_us(5);
      }
      while(rightBtn()==0 && leftBtn()==0 ){
        leftTurn();
      }
      if (rightBtn() == 1) {
        offState = 0;
      }
      if (leftBtn() == 1) {
        offState = 1;
      }
    }
  }
}
