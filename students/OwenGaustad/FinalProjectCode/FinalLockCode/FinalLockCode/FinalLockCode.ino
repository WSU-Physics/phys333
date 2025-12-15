
// ------- Preamble -------- //
#include <SPI.h>
#include <SD.h>

// ------- Pin Defines -------- //

#define BUTTON_1                 2     //Digital Pin 2
#define BUTTON_2                 3     //Digital Pin 3
#define BUTTON_3                 4     //Digital Pin 4
#define BUTTON_4                 5     //Digital Pin 5
#define BUTTON_5                 6     //Digital Pin 6
#define BUTTON_6                 7     //Digital Pin 7
#define BUTTON_7                 8     //Digital Pin 8

#define ALL_RED_LEDS            9     //Digital Pin 9
#define LED_9                   10    //Digital Pin 10
#define LED_10                  11    //Digital Pin 11
#define LED_11                  12    //Digital Pin 12
#define LED_12                  13    //Digital Pin 13
#define motorPin1               A0; // Pin for controlling direction 1
#define motorPin2               A1; // Pin for controlling direction 2

// ------- Macros -------- //
#define BV(bit)               (1 << (bit))       // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// ------- Global Variables -------- //
  //Initializes flag that will be used to turn off our buttons after the password has been input

const int chipSelect = 10; // Chip select pin for the SD card
int flag = 0;
int DELAY = 5;                //Sets the delay that is used for a small delay in the button press. 
int setPassword[4];
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
  if (digitalRead(button) == LOW) {
    while (digitalRead(button) == LOW){}
    delay(DELAY);
    return 1;
  }
  else {
    return 0;
  }
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
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);
  pinMode(BUTTON_6, INPUT_PULLUP);
  pinMode(BUTTON_7, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_1), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_3), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_4), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_5), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_6), updatePassword, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_7), updatePassword, CHANGE);
}

void initLEDs() {
  // Set LED pins as output
  pinMode(ALL_RED_LEDS, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  pinMode(LED_12, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
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
  digitalWrite(ALL_RED_LEDS, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(LED_11, LOW);
  digitalWrite(LED_12, LOW);
}

/******************************************************************************
This function turns one LED on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void oneLED(){
  digitalWrite(LED_9, HIGH);
}

/******************************************************************************
This function turns two LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void twoLED(){
  digitalWrite(LED_9, HIGH);
  digitalWrite(LED_10, HIGH);
}

/******************************************************************************
This function turns three LEDs on. Although the motor is on the same 
directory as the LEDs this function does not effect the motor pin.
******************************************************************************/
void threeLED(){
  digitalWrite(LED_9, HIGH);
  digitalWrite(LED_10, HIGH);
  digitalWrite(LED_11, HIGH);
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
  digitalWrite(LED_9, HIGH);
  digitalWrite(LED_10, HIGH);
  digitalWrite(LED_11, HIGH);
  digitalWrite(LED_12, HIGH);
  delay(1000);
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
    delay(200);
    digitalWrite(LED_9, HIGH);
    digitalWrite(LED_10, HIGH);
    digitalWrite(LED_11, HIGH);
    digitalWrite(LED_12, HIGH);
    delay(200);
  }
  ledsOff();
  motorAction();
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
    delay(200);
    digitalWrite(ALL_RED_LEDS, HIGH);
    delay(200);
  }
  ledsOff();
}

/******************************************************************************
******************************************************************************/
void motorAction(){
  // Turn the motor in one direction
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(1000); // 1 second

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // 1 second

  // Turn the motor in the opposite direction
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(1000); // 1 second

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(1000); // 1 second
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
    flag = 0;
    int isEqual = 1; 

    for (int i = 0; i < 4; i++) {
      if (getPassword[i] != setPassword[i]) {
        isEqual = 0;
        break;
      }
    }

    if (isEqual) {
      passwordCorrect();
    } else {
      passwordIncorrect();
    }
  }
}

// ------- Main Code -------- //
void setup() {
  Serial.begin(9600);
  
  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }

  // Check if the file exists
  if (!SD.exists("PASSWORD.txt")) {
    // Create the file if it doesn't exist
    File myFile = SD.open("PASSWORD.txt", FILE_WRITE);
    if (myFile) {
      // Write default password and message
      myFile.println("1234");
      myFile.println("^^^^");
      myFile.println("Above is the password set for your lock you can change it to whatever 4 letter");
      myFile.println("combination of numbers you want as long as they are from 1-6");
      myFile.println("if you have any questions about the use of the device please feel free to contact me");
      myFile.println("at [insert contact here]");
      // Flush the data to ensure it's written to the SD card
      myFile.flush();
      myFile.close();
      Serial.println("PASSWORD.txt created with default password.");
    } else {
      Serial.println("Error creating PASSWORD.txt");
      return;
    }
  }

  // Open the file for reading
  File myFile = SD.open("PASSWORD.txt");
  if (myFile) {
    const int MAX_CHARACTERS = 5; // Adjust the maximum number of characters as needed
    char data[MAX_CHARACTERS];
    int index = 0;

    // Read each character from the file until we reach the end or the maximum number of characters
    while (myFile.available() && index < MAX_CHARACTERS - 1) {
      char c = myFile.read();
      // Store the character in the array
      setPassword[index] = c;
      index++;
    }
    // Null-terminate the array to make it a valid C-string
    setPassword[index] = '\0';

    // Close the file
    myFile.close();

    // Print out the password
    Serial.println("Password:");
    Serial.println(data);


  } else {
    // If the file didn't open, print an error
    Serial.println("Error opening PASSWORD.txt");
  }

  // Initialize LEDs and Buttons
  initLEDs();
  initButtons();
}

void loop() {
  switch(getIndex){   
    case(0):
      flagCheck();
      ledsOff();
      break;
    case(1):
      oneLED();
      break;
    case(2):
      twoLED();
      break;
    case(3):
      threeLED();
      break;
  }
}