
// ------- Preamble -------- //

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define LED_MOTOR_PORT          PORTD
#define LED_MOTOR_DDR           DDRD

// ------- Pin Defines -------- //

#define BUTTON1                 PD1     //Digital Pin 1
#define BUTTON2                 PD2     //Digital Pin 2
#define BUTTON3                 PD3     //Digital Pin 3
#define BUTTON4                 PD4     //Digital Pin 4
#define BUTTON5                 PD5     //Digital Pin 5
#define BUTTON6                 PD6     //Digital Pin 6
#define BUTTON7                 PD7     //Digital Pin 7

#define ALL_RED_LEDS            PB0     //Digital Pin 8
#define GREEN_LED1              PB1     //Digital Pin 9
#define GREEN_LED2              PB2     //Digital Pin 10
#define GREEN_LED3              PB3     //Digital Pin 11
#define GREEN_LED4              PB4     //Digital Pin 12
#define MOTOR                   PB5     //Digital Pin 13

// ------- Macros -------- //
#define BV(bit)               (1 << (bit))       // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// ------- Global Variables -------- //
const int setPasssword = [1,2,3,4]; //Sets the password you need for checking if the buttons were clicked in the correct order
const int delay = 5;                //Sets the delay that is used for a small delay in the button press. 
int getPassword[3];                 //This establishes the array we will be using for our input password. 
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
    _delay_ms(delay);
    if (bit_is_clear(BUTTON_PIN, button)) {return 1;}
    else {return 0;}
  }
  else {return 0;}
}

/******************************************************************************
This Function runs an instance of chkButton for every button after being 
called and if any of them return 1 then this method will return their given 
number i.e. 1,2,3,4....
******************************************************************************/
uint8_t chkButton() {
  if (btnCheck(BUTTON1))       {return 0;}
  else if (btnCheck(BUTTON2))  {return 1;}
  else if (btnCheck(BUTTON3))  {return 2;} 
  else if (btnCheck(BUTTON4))  {return 3;} 
  else if (btnCheck(BUTTON5))  {return 4;}
  else if (btnCheck(BUTTON6))  {return 5;}
  else if (btnCheck(BUTTON7))  {return 6;}
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
  getPassword[getIndex] = chkButton();
  if (getPassword[getIndex] == 6) {
    getIndex = 0;
    flag = 0;
  } 
  else {
    getIndex++;
    if (getIndex == 4){
      flag = 1;
      getIndex = (getIndex) % 4;
    }  
  }
}

/******************************************************************************
This function activates the interupts on digital pins 1-7. Any change in 
voltage across those pins will then activate my ISR function located below.
******************************************************************************/
void intInterrupt0()  {
  PCICR |= (1 << PCIE2);
  for(int i = 1; i <= 7; i++) {
    BUTTON_DDR &= ~(1 << i);       //activates input
    BUTTON_PORT |= (1 << i);       //activates resistor
    PCMSK2 |= (1 << i);} //sets up a loop that initializes my interrupts
  sei();
}

/******************************************************************************
Function activates interrupts our arduino and runs our updatePassword 
function.
******************************************************************************/
ISR(PCINT2_vect) {
  updatePassword();
}

/******************************************************************************
This function turns all LEDs off. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void ledsOff(){
  //turns all leds to off
  for (int i = 0; i <= 4;i++){
    clearBit(LED_PORT,i); 
  }
}

/******************************************************************************
This function turns one LED on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void oneLED(){
  //turns on first led
  setBit(LED_MOTOR_PORT, GREEN_LED1);
}

/******************************************************************************
This function turns two LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void twoLED(){
  //turns on first 2 leds
  setBit(LED_MOTOR_PORT, GREEN_LED2);
}

/******************************************************************************
This function turns three LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void threeLED(){
  //turns on first 3 leds
  setBit(LED_MOTOR_PORT, GREEN_LED3);
}

/******************************************************************************
This function turns four LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin. This 
function is also structured differently than the other LED states because 
it takes place in a state where no user input is allowed so it needs a 
delay followed by the turning off of all LEDs. 
******************************************************************************/
void fourLED(){
  setBit(LED_MOTOR_PORT, GREEN_LED4);
  _delay_ms(1000);
  ledsOff();
  _delay_ms(100);
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
  ledsOff();
  for(int i = 0; i<=3; i++){
    for(int i = 1; i <= 4;i++){
      toggleBit(LED_MOTOR_PORT, i);
    }
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
  ledsOff();
  for(int i = 0; i<=3; i++){
    toggleBit(LED_MOTOR_PORT, ALL_RED_LEDS);
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
  if (flag == 1) {
    cli();
    flag = 0;
    fourLED();
    if (getPassword == setPassword){
      passwordCorrect();
    }
    else {
      paasswordIncorrect();
    }
    sei();
  }
}

// ------- Main Code -------- //
int main(void) {

  // ------- Inits -------- //
  //Initializes flag that will be used to turn off our buttons after the password has been input
  int flag = 0;
  //Initializes our interrupts
  intInterrupt0();
  //Initializes the directory for our LED's and motor
  LED_MOTOR_DDR = 0xff;
  
  // ------- Loop -------- //
  while (1){
    //an array that indexes from 0 to 3
    switch(getIndex){   
      //this state is run when a button has not been pressed or our password has been fully input. 
      case(0):          
      flagCheck();
      ledsOff();
      //This state is run after one number has been input. 
      case(1):
      oneLED();
      //This state is run after two numbers have been input. 
      case(2):
      twoLED();
      //This state is run after three numbers have been input. 
      case(3):
      threeLED();
    }
  }  
}
