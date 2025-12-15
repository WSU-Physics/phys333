
// ------- Preamble -------- //
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


#define BUTTON_PORT             PORTD
#define BUTTON_PIN              PIND
#define BUTTON_DDR              DDRD

#define LED_MOTOR_PORT          PORTB
#define LED_MOTOR_DDR           DDRB

// ------- Pin Defines -------- //

#define BUTTON_1                 PD1     //Digital Pin 1
#define BUTTON_2                 PD2     //Digital Pin 2
#define BUTTON_3                 PD3     //Digital Pin 3
#define BUTTON_4                 PD4     //Digital Pin 4
#define BUTTON_5                 PD5     //Digital Pin 5
#define BUTTON_6                 PD6     //Digital Pin 6
#define BUTTON_7                 PD7     //Digital Pin 7

#define ALL_RED_LEDS            PB0     //Digital Pin 8
#define LED_9                   PB1     //Digital Pin 9
#define LED_10                  PB2     //Digital Pin 10
#define LED_11                  PB3     //Digital Pin 11
#define LED_12                  PB4     //Digital Pin 12
#define MOTOR                   PB5     //Digital Pin 13

// ------- Macros -------- //
#define BV(bit)               (1 << (bit))       // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// ------- Global Variables -------- //
  //Initializes flag that will be used to turn off our buttons after the password has been input
int flag = 0;
int DELAY = 5;                //Sets the delay that is used for a small delay in the button press. 
int setPassword[4] = {1,2,3,4};
int getPassword[4];                 //This establishes the array we will be using for our input password. 
int getIndex = 0;                   //This establishes a variable I use for shifting the index of my get password array

// ------- Functions -------- //
/******************************************************************************
This Function checks the button pin that is being recieved and if that button 
is pressed it waits 5 milliseconds then if it is still depressed it returns 
1 otherwise it will return 0. If you want to improve this mess around with 
the delay time. Maybe a while loop could be useful here otherwise this 
should work for our cerruent design. 
******************************************************************************/
uint8_t btnCheck(int button)  {
  if (bit_is_clear(BUTTON_PIN, button)){
    while (bit_is_clear(BUTTON_PIN, button)){}
    _delay_ms(DELAY);
    return 1;
  }
  else {return 0;}
}

/******************************************************************************
This Function runs an instance of chkButton for every button after being 
called and if any of them return 1 then this method will return their given 
number i.e. 1,2,3,4....
******************************************************************************/
uint8_t chkButton() {
  if (btnCheck(BUTTON_1))       {return 1;}
  else if (btnCheck(BUTTON_2))  {return 2;}
  else if (btnCheck(BUTTON_3))  {return 3;} 
  else if (btnCheck(BUTTON_4))  {return 4;} 
  else if (btnCheck(BUTTON_5))  {return 5;}
  else if (btnCheck(BUTTON_6))  {return 6;}
  else if (btnCheck(BUTTON_7))  {return 7;}
  else                          {return 255;} //No button Pressed
}

/******************************************************************************
This Function establishes our input password array. The first time this 
program is run it will start its index at zero and every time following it 
will be increased by 1 until it hits 3 then it will reset to zero. This is 
how we will be able to keep our pasword to 4 digits. There is also a clear 
function which will be button 7 and if that is hit the index will be reset 
to 0 and our LED's will all be reset. 
******************************************************************************/
void updatePassword()  {
  uint8_t buttonPressed = chkButton();

  if (buttonPressed != 255 && buttonPressed != 7) {
    getPassword[getIndex] = buttonPressed;
    getIndex++;
    if (getIndex == 4){
      getIndex = 0;
      flag = 1;
      fourLED();
    }
  } 

  if (buttonPressed == 7) {
    getIndex = 0;
  }
}

/******************************************************************************
This function activates the interupts on digital pins 1-7. Any change in 
voltage across those pins will then activate my ISR function located below.
******************************************************************************/
void initButtons()  {
  BUTTON_DDR &= ~((1 << BUTTON_1) | (1 << BUTTON_2) | (1 << BUTTON_3) |
                  (1 << BUTTON_4) | (1 << BUTTON_5) | (1 << BUTTON_6) |
                  (1 << BUTTON_7));
  BUTTON_PORT |= ((1 << BUTTON_1) | (1 << BUTTON_2) | (1 << BUTTON_3) |
                  (1 << BUTTON_4) | (1 << BUTTON_5) | (1 << BUTTON_6) |
                  (1 << BUTTON_7));
  // Enable interrupts for the buttons
  PCICR |= (1 << PCIE2); // Enable PCINT[23:16] interrupts
  PCMSK2 |= ((1 << BUTTON_1) | (1 << BUTTON_2) | (1 << BUTTON_3) |
             (1 << BUTTON_4) | (1 << BUTTON_5) | (1 << BUTTON_6) |
             (1 << BUTTON_7));
  sei();
}

void initLEDs() {
    // Set LED pins as output
    DDRB |= (1 << ALL_RED_LEDS) | (1 << LED_9) | (1 << LED_10) | (1 << LED_11) | (1 << LED_12) | (1 << MOTOR);
}

/******************************************************************************
Function activates interrupts our arduino and runs our updatePassword 
function.
******************************************************************************/
ISR(PCINT2_vect) {
  cli();
  updatePassword();
  sei();
}

/******************************************************************************
This function turns all LEDs off. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void ledsOff(){
  //turns all leds to off
  PORTB &= ~((1 << ALL_RED_LEDS) | (1 << LED_9) | (1 << LED_10) | (1 << LED_11) | (1 << LED_12));
}

/******************************************************************************
This function turns one LED on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void oneLED(){
  //turns on first led9
  ledsOff();
  PORTB |= (1 << LED_9);
}

/******************************************************************************
This function turns two LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void twoLED(){
  ledsOff();
  PORTB |= (1 << LED_9) | (1 << LED_10);
}

/******************************************************************************
This function turns three LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void threeLED(){
  //turns on first 3 leds
  ledsOff();
  PORTB |= (1 << LED_9) | (1 << LED_10) | (1 << LED_11);
}

/******************************************************************************
This function turns four LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin. This 
function is also structured differently than the other LED states because 
it takes place in a state where no user input is allowed so it needs a 
delay followed by the turning off of all LEDs. 
******************************************************************************/
void fourLED(){
  ledsOff();
  PORTB |= (1 << LED_9) | (1 << LED_10) | (1 << LED_11)| (1 << LED_12);
  _delay_ms(1000);
  ledsOff();
}

/******************************************************************************
This function takes place when all LEDs should already be off then it uses 
two for loops to initialize each green LED pin as either on or off and 
toggle them through the collective states on, off, on, off. it waits 200ms 
between each state and ends the state with all of them off. In the code we 
set the states of all LEDs to off before and after this funtion runs so it 
might seem like redundant code but if I decide to make changes in the 
future I might need them. Plus it doesn't change anything having them in 
there as a checker. 
******************************************************************************/
void passwordCorrect(){
  for(int i = 0; i<=3; i++){
    ledsOff();
    _delay_ms(200);
    PORTB |= (1 << LED_9) | (1 << LED_10) | (1 << LED_11)| (1 << LED_12);
    _delay_ms(200);
  }
  ledsOff();
  //turn motor forward
  //turn motor back to  start position(theoretccially this won't lock it)
}

/******************************************************************************
This function takes place when all LEDs should already be off then it 
flashes the red LEDs on, off, on, off. it waits 200ms between each state 
and ends the state with all of them off. In the code we set the states of 
all LEDs to off before and after this funtion runs so it might seem like 
redundant code but if I decide to make changes in the future I might need 
them. Plus it doesn't change anything having them in there as a checker. 
******************************************************************************/
void passwordIncorrect(){
  for(int i = 0; i<=3; i++){
    ledsOff();
    _delay_ms(200);
    PORTB |= (1 << ALL_RED_LEDS);
    _delay_ms(200);
  }
  ledsOff();
}

/******************************************************************************
******************************************************************************/
void motorAction(){
  //turn motor set distance in one direction and then that same distance back
}

/******************************************************************************
This function checks to see if the flag integer is equal to one. the only 
time the flag variable should be equal to one is after your password has 
been complete. Then all the buttons are immediately deactivated. Following 
the deactivation the flag is set to zero, the fourth button lights up for a 
second, turns off for .1 second, then finally our password checker is ran. 
If the input password is equal to our set password then the correctPassword 
function is run. Otherwise the incorrect Function is run. At the end of the 
Flag check the interrupts are reinitialized with sei() allowing you to 
reinput a password. 
******************************************************************************/
void flagCheck(){
  cli();
  if (flag == 1) {
    flag = 0;
    int isEqual = 1; // Flag to indicate if arrays are equal, initially assume they are equal

    // Check if arrays are equal
    for (int i = 0; i < 4; i++) {
      if (getPassword[i] != setPassword[i]) {
        isEqual = 0; // Arrays are not equal
        break;
      }
    }

    if (isEqual) {
      passwordCorrect();
    } else {
      passwordIncorrect();
    }
  }
  sei();
}

// ------- Main Code -------- //
int main(void) {

  // ------- Inits -------- //
  initLEDs(); // Initialize LED pins
  initButtons(); // Initialize button pins

  // ------- Loop -------- //
  while (1){
    //getIndex is used in my getPassword array that indexes from 0 to 3
    switch(getIndex){   
      //this case is run when a button has not been pressed or our password has been fully input. 
      case(0):
      flagCheck();
      ledsOff();
      break;
      //This case is run after one number has been input. 
      case(1):
      oneLED();
      break;
      //This case is run after two numbers have been input. 
      case(2):
      twoLED();
      break;
      //This case is run after three numbers have been input. 
      case(3):
      threeLED();
      break;
    }
  }  
}
