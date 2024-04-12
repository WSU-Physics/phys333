//Part4 Lab1

// pin ins
const int redPin = 9;        
const int greenPin = 10;     
const int bluePin = 11;      
const int buttonPin = 3;    

// mode constants
const int OFF = 1;            
const int BLINK_WHITE = 2;    
const int FADE_PURPLE = 3;    
const int FADE_RED_BLUE = 4;  
const int FLASH_BLUE_GREEN = 5;

// variable to store the current mode
int currentMode = OFF;

// variables to handle button state
int lastButtonState = HIGH;    // variable to store the last button state
int buttonState;               // variable to store the current button state

// setup function runs once at the beginning
void setup() {
  // set pin modes for RGB and button
  pinMode(redPin, OUTPUT);     // set red led pin as OUTPUT
  pinMode(greenPin, OUTPUT);   // set green led pin as OUTPUT
  pinMode(bluePin, OUTPUT);    // set blue led pin as OUTPUT
  pinMode(buttonPin, INPUT_PULLUP);  // set button pin as INPUT_PULLUP

  // initialize serial communication for debugging
  Serial.begin(9600);
}

// main loop function runs repeatedly
void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // check if the button is pressed (LOW) and was not pressed in the last loop
  if (buttonState == LOW && lastButtonState == HIGH) {
    // change to the next mode
    changeMode();
    // add a delay to debounce the button press
    delay(1000);
  }

  // execute the functionality of the current mode
  executeMode();

  // save the current button state for the next loop iteration
  lastButtonState = buttonState;
}

// function to change the mode
void changeMode() {
  // increment the current mode, and wrap around to 1 if it exceeds 5
  currentMode = (currentMode % 5) + 1;
  // print the current mode for debugging
  Serial.print("Switching to mode ");
  Serial.println(currentMode);
}

// function to execute the functionality of the current mode
void executeMode() {
  // switch statement to determine the action for each mode
  switch (currentMode) {
    //mode one: off
    case OFF:
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break; //breaks into void defined statements

    // mode two: blink white 
    case BLINK_WHITE:
      blinkWhite();
      break;

    // mode three: fade purple
    case FADE_PURPLE:
      fadePurple();
      break;

    // mode four: fade red blue
    case FADE_RED_BLUE:
      fadeRedBlue();
      break;

    //mode five: flash blue and green, go seahawks!
    case FLASH_BLUE_GREEN:
      flashBlueGreen();
      break;
  }
}


void blinkWhite() {
  // set the red, green and blue pins to maximum brightness 
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  // wait for 500 milliseconds
  delay(500);
  // turn off the red, green and blue pins
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(500);
}

// function to fade purple from bright to dim and back
void fadePurple() {
  // loop from 0 to 255 with increments of 5
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    // set the red and blue pins to the same brightness value
    analogWrite(redPin, brightness);
    analogWrite(bluePin, brightness);
    delay(50);
  }
  // loop from 255 to 0 with decrements of 5
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    // Set the red and blue pins to the same brightness value
    analogWrite(redPin, brightness);
    analogWrite(bluePin, brightness);
    delay(50);
  }
}

// function to fade red to blue and back
void fadeRedBlue() {
  // loop from 0 to 255 with increments of 5
  for (int i = 0; i <= 255; i += 5) {
    // set the red pin to i and the blue pin to 255 - i
    analogWrite(redPin, i);
    analogWrite(bluePin, 255 - i);
    delay(50);
  }
  // loop from 255 to 0 with decrements of 5
  for (int i = 255; i >= 0; i -= 5) {
    // set the red pin to i and the blue pin to 255 - i
    analogWrite(redPin, i);
    analogWrite(bluePin, 255 - i);
    delay(50);
  }
}

// function to flash blue and green alternatively
void flashBlueGreen() {
  // set the blue pin to maximum brightness 
  analogWrite(bluePin, 255);
  delay(500);
  // turn off the blue pin
  analogWrite(bluePin, 0);
  // set the green pin to maximum brightness 
  analogWrite(greenPin, 255);
  delay(500);
  // turn off the green pin
  analogWrite(greenPin, 0);
}
