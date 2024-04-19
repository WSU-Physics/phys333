
// ------- Preamble -------- //

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB

#define LED_PORT                PORTD
#define LED_DDR                 DDRD

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
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// ------- Global Variables -------- //

const int setPasssword = [1,2,3,4];              //Sets the password you need for checking if the buttons were clicked in the correct order
const int delay = 5;                             //Sets the delay that is used for a small delay in the button press. 
int getPassword[3];                              //This establishes the array we will be using for our input password. 
int getIndex = 0;                                //This establishes a variable I use for shifting the index of my get password array

// ------- Functions -------- //

/******************************************************************************
This Function checks the button pin that is being recieved and if that button 
is pressed it waits 5 milliseconds then if it is still depressed it returns 
1 otherwise it will return 0. If you want to improve this mess around with 
the delay time. Maybe a while loop could be useful here otherwise this 
should work for our cerruent design. 
******************************************************************************/
uint8_t btnCheck(button)  {
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
//must return # into the first index in our getPassword array if the first index is filled it must go in the second and so on...
  if (btnCheck(BUTTON1))       {return 0;}
  else if (btnCheck(BUTTON2))  {return 1;}
  else if (btnCheck(BUTTON3))  {return 2;} 
  else if (btnCheck(BUTTON4))  {return 3;} 
  else if (btnCheck(BUTTON5))  {return 4;}
  else if (btnCheck(BUTTON6))  {return 5;}
  else if (btnCheck(BUTTON7))  {return 6;} //if 6 returns this should clear the numbers in my array
}

/******************************************************************************
This Function establishes our input password array. The first time this 
program is run it will start its index at zero and every time following it 
will be increased by 1 until it hits 3 then it will reset to zero. This is 
how we will be able to keep our pasword to 4 digits. There is also a clear 
function which will be button 7 and if that is hit the index will be reset 
to 0 and our LED's will all be reset. 
******************************************************************************/
updatePassword()  {
  getPassword[getIndex] = chkButton();//I have to be careful around this because there is a delay in here and my interrupt could cause problems with everything after this 
  if (getPassword[getIndex] == 6) {
    //This has to clear my LEDs and resent my index
    getIndex = 0;
    flag = 0;
  } else {
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
  for(int i = 1; i <= 7; i++) {PCMSK2 |= (1 << i);} //sets up a loop that initializes my interrupts
  sei();
}
/******************************************************************************
Function activates interrupts our arduino and runs our updatePassword 
function.
******************************************************************************/
ISR(PCINT2_vect) {
  updatePassword();
}



int main(void) {

// ------- Inits -------- //
  int flag = 0;
  intInterrupt0();

  // ------- Code -------- //
  while (1){
    switch(getIndex){
      case(0):
        if (flag == 1) {
          cli();
          flag = 0;
          //4 leds
          //delay
          if (getPassword == setPassword){
            //blink green twice
            //turn motor forward
            //turn motor back to  start position(theoretccially this won't lock it)
            //intInterrupt0(); or sei();
          }
          else {
            //blink red twice
            //intInterrupt0(); or sei();
          }
        }
        //off
      case(1):
        //1 led
      case(2):
        //2 led
      case(3):
        //3 led
    }












    // //no light function
    // while (getIndex == 0){} // stop sign
    // //if I get zero that means it is waiting on the first input so none of the lights shold be on

    // //single light function
    // while (getIndex == 1){}// stop sign
    // //if I get 1 a button has been pressed

    // //two light function
    // while (getIndex == 2){} // stop sign
    // //if I get 2 the second button has been pressed

    // //three light function
    // while (getIndex == 3){} // stop sign
    // //if I get 3 the third button has been pressed

    // //four light function maybe followed by a delay if I think it looks ugly
    // //if password was correct flash green twice and turn motor
    // //else flash lightss red twice
  }  
}
