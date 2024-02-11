// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPinR = 9;    // the number of the Red LED pin also a ~PWM port
const int ledPinG = 10;    // the number of the Green LED pin
const int ledPinB = 11;    // the number of the Blue LED pin
// variables will change:
int buttonState = 0;                 //variable for reading the pushbutton status
int LEDState = 0;                    //variable for the State program 
int State = 5;                      //varaible for the number of states in the code
int n = 1;                          //variable used for changing the fade speed in lights
int value = 0;                      //variable fo light fading
void setup() {
  // initialize the Red LED pin as an output:
  pinMode(ledPinR, OUTPUT);
    // initialize the Blue LED pin as an output:
  pinMode(ledPinG, OUTPUT);
    // initialize the Green LED pin as an output:
  pinMode(ledPinB, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
void loop() {
  /*
  The following block of code is used throughout 
  the loop to check for button pressing 
  */
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    LEDState = (1 + LEDState) % State;             
    //changes the LEDState between different cods set up
    //f LEDState completely divides by State, the result of the expression is 0.
    while (buttonState == HIGH) {            //puts a loop in the code so it won't move forward until you release the button
      buttonState = digitalRead(buttonPin);  //exits the loop when the button is released                
      //When the LED is flashing green it is ready to initialize the new state
    }
  }
  //Turns all LED's off
  if (LEDState == 0) {
    analogWrite(ledPinR, 0);
    analogWrite(ledPinG, 0);
    analogWrite(ledPinB, 0);
  }
  //Initializes the first state where the white light is blinking
  if (LEDState == 1) {
    for (int i = 0; i <= 1000; i += 1) {
      //this state declares it as on 
      analogWrite(ledPinR, 255);    //sets value for the LED to its maximum
      analogWrite(ledPinG, 255);    //sets value for the LED to its maximum
      analogWrite(ledPinB, 255);    //sets value for the LED to its maximum
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        while (buttonState == HIGH) {
            buttonState = digitalRead(buttonPin);
          }
        } 
      delay(1);
      /*
      The delay is within a for loop where the for loop is actually 
      what is deciding the wait time so your total time a delay is on 
      will be this value in seconds then the loop ends. 
      */
    }
    for (int i = 1000; i >= 0; i -= 1) {
      //this state declares the LED as off
      analogWrite(ledPinR, 0);    //sets value for the LED to 0
      analogWrite(ledPinG, 0);    //sets value for the LED to 0
      analogWrite(ledPinB, 0);    //sets value for the LED to 0
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        while (buttonState == HIGH) {
            buttonState = digitalRead(buttonPin);
          }
        } 
      delay(1);
      //for loop ends after delay time in seconds. 
    }
  }
  //initializes the second state where the purple light fades high to low to high
  if (LEDState == 2) {
    for (int i = 0; i <= 255; i += 1) {
      //initially the light is off then it slowly goues to full brightness.
      analogWrite(ledPinR, i);
      analogWrite(ledPinG, 0);
      analogWrite(ledPinB, i);
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        while (buttonState == HIGH) {
            buttonState = digitalRead(buttonPin);
          }
        } 
      delay(4);
      /*
      This delay determines the rate this LED fades by
      the lower the number the faster the LED fades
      */
    }
    for (int i = 255; i >= 0; i -= 1) {
      //initially the light is at full brightness and it slowly goes to off. 
      analogWrite(ledPinR, i);
      analogWrite(ledPinG, 0);
      analogWrite(ledPinB, i);
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        while (buttonState == HIGH) {
            buttonState = digitalRead(buttonPin);
          }
        } 
      delay(4);
    }
  }
  //this state sets the LED to blue fades it to red then fades it back to blue. 
  if (LEDState == 3) {
    for (int i = value; i <= 255; i += n) {
      //this for loop simply fades the LED from blue to red
      analogWrite(ledPinR, i);
      analogWrite(ledPinG, 0);
      analogWrite(ledPinB, 255 - i);
      delay(8);                             //this changes the rate the fade occurs by 
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        i = 300;                            // this breaks the for loop when the button is pressed
        value = 0;                          //this sets the value to zero so when you enter the state again you start at blue.         
        while (buttonState == HIGH) { 
            buttonState = digitalRead(buttonPin); 
        }
      } 
      //this if statement is used to make the LED fade from red to blue
      if (i == 255){
        value = 255;
        n = -1;
      }
      //this if statement is used to make the LED fade from blue to red
      if (i == 0){
        value = 0;
        n = 1;
      }
    }
  }
  //RGB light this state makes a soothing light that fades from Green to Red to Blue then repeat. 
  if (LEDState == 4)  {
    for (int i = 0; i <= 255; i += 1) {
      //fades the light from green to red
      analogWrite(ledPinR, i);
      analogWrite(ledPinG, 255 - i);
      analogWrite(ledPinB, 0);
      delay(2);
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        i = 300;  
        while (buttonState == HIGH) { 
            buttonState = digitalRead(buttonPin); 
        }
      } 
    }
    for (int i = 0; i <= 255; i += 1) {
      //fades the light from Red to blue
      analogWrite(ledPinR, 255-i);
      analogWrite(ledPinG, 0);
      analogWrite(ledPinB, i);
      delay(2);
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        i = 300;
        while (buttonState == HIGH) { 
            buttonState = digitalRead(buttonPin); 
        }
      } 
    }
    for (int i = 0; i <= 255; i += 1) {
      //fades th elight from blue to green
      analogWrite(ledPinR, 0);
      analogWrite(ledPinG, i);
      analogWrite(ledPinB, 255-i);
      delay(2);
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH) {
        LEDState = (1 + LEDState) % State;
        i = 300;     
        while (buttonState == HIGH) { 
            buttonState = digitalRead(buttonPin); 
        }
      } 
    }


  }   
}
 