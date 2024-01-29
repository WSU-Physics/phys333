//1. Store a previous button state and a current button state (initialized 
//to LOW).
//2. Read the current button state.
//3. If the current button state differs from the previous button state, wait 5ms 
//because the button must have changed state.
//4. After 5ms, reread the button state and use that as the current button state.
//5. If the previous button state was low, and the current button state is high, 
//toggle the LED state.
//6. Set the previous button state to the current button state.
//7. Return to step 2

const int LED = 9; //Attach LED to port 9
const int BUTTON = 2; //Attach Button to port 2
boolean LastButton = LOW; //variable containg past button state
boolean currentButton = LOW; //variable containg current button state
boolean LedOn = false; //The present state of LED (on/off)

void setup() {
  pinMode (LED, OUTPUT); //Set LED at output
  pinMode (BUTTON, INPUT); //set BUTTON as input

}
/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/

boolean debounce (boolean last){       
  boolean current = digitalRead(BUTTON);    //read button state
    if (last != current)                   //if it is different...
    {
      delay(5);                            //wait 5ms 
      current = digitalRead(BUTTON);       //read again
    }
    return current;                        //return current value 
}

void loop() {
  currentButton = debounce(LastButton);           //read debounced state
  if (LastButton == LOW && currentButton == HIGH) //if butrton was pressed...
    {
      LedOn = !LedOn;                             //toggle LED value
    }
  LastButton = currentButton;                     //reset button value

  digitalWrite(LED, LedOn);                       //toggle LED state
}
