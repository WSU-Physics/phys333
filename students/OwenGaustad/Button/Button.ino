// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 9;    // the number of the LED pin also a ~PWM port

// variables will change:
int buttonState = 0;                 //variable for reading the pushbutton status
int bright = 0;                      //variable for the inital state of the LED
int fade = 2;                        //variable for increasing the LED brightness
//int LEDState = 0;                    variable for the State program 
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin); 
  bright = bright + fade;            //added brightness function that goes from dull to bright
  if (bright == 60) {                //upper limit of brightness is 60
    fade = -fade;                    //if the upper limit is hit the fade constant gets inverted  
  }
  if (bright == 0)  {
    fade = -fade;                    //if the lower limit is hit the fade constant gets inverted
  }
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    /*
    Following code will be implemented in a State machine
    while (buttonState == HIGH) {    //puts a loop in the code so it won't move forward until you release the button
      delay(1);                      //filler code I fugure a slight delay will be nessecary but I don't know what yet
    }
    LED State = LEDState + 1;        //changes the LEDState between different cods set ups
    */
    // turn LED on:
    analogWrite(ledPin, bright);
  } else{
    // turn LED off:    
  bright = 0;
    analogWrite(ledPin, bright);
  }
  delay(40);                          //small delay to make the LED fade more noticible
}
 