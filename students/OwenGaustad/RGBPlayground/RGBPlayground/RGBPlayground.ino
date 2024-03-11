// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPinR = 4;    // the number of the Red LED pin also a ~PWM port
const int ledPinG = 7;    // the number of the Green LED pin
const int ledPinB = 8;    // the number of the Blue LED pin


// variables will change:
int buttonState = 0;                 //variable for reading the pushbutton status
int LEDState = 0;                    //variable for the State program 

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
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); 
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    LEDState = 1+LEDState;             //changes the LEDState between different cods set up
    while (buttonState == HIGH) {            //puts a loop in the code so it won't move forward until you release the button
      buttonState = digitalRead(buttonPin);  //exits the loop when the button is released                
    }
  }
  //Turns all LED's off
  if (LEDState == 0) {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
  }
  //Initializes the first state where only the Red LED is on
  if (LEDState == 1) {
    digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
  }
  //Initializes the second state where only the Green LED is on
  if (LEDState == 2) {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, HIGH);
    digitalWrite(ledPinB, LOW);
  }
  //Initializes the third state where only the Blue LED is on
  if (LEDState == 3) {
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, HIGH);
  }
  //Resets the state series
  if (LEDState == 4)  {
    LEDState = 0;
  }   
}
 