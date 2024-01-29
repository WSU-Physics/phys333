// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPinR = 6;    // the number of the Red LED pin also a ~PWM port
const int ledPinG = 9;    // the number of the Green LED pin
const int ledPinB = 10;    // the number of the Blue LED pin


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
      //When the LED is flashing green it is ready to initialize the new state
      analogWrite(ledPinR, 0);
      analogWrite(ledPinG, 10);
      analogWrite(ledPinB, 0);
      delay(100);
      analogWrite(ledPinG, 0);
      delay(100);
    }
  }
  //Turns all LED's off
  if (LEDState == 0) {
    analogWrite(ledPinR, 0);
    analogWrite(ledPinG, 0);
    analogWrite(ledPinB, 0);

  }
  //Initializes the first state where only the Red LED is on
  if (LEDState == 1) {
    analogWrite(ledPinR, 70);
    analogWrite(ledPinG, 75);
    analogWrite(ledPinB, 110);
    delay(500);
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
    delay(500);
  }
  //Initializes the second state where only the Green LED is on
  if (LEDState == 2) {
    analogWrite(ledPinR, 0);
    analogWrite(ledPinG, 100);
    analogWrite(ledPinB, 100);

  }
  //Initializes the third state where only the Blue LED is on
  if (LEDState == 3) {
    analogWrite(ledPinR, 125);
    analogWrite(ledPinG, 0);
    analogWrite(ledPinB, 100);

  }
  //Resets the state series
  if (LEDState == 4)  {
    LEDState = 0;
  }   
}
 