


const int BLED=11; // Blue LED Cathode on Pin 9
const int GLED=10; // Green LED Cathode on Pin 10
const int RLED=9; // Red LED Cathode on Pin 11
const int BUTTON=2; // The Button is connected to pin 2
boolean lastButton = LOW; // Last Button State
boolean currentButton = LOW; // Current Button State
int ledMode = 0; // Cycle between LED states
void setup()
{
 pinMode (BLED, OUTPUT); // Set Blue LED as Output
 pinMode (GLED, OUTPUT); // Set Green LED as Output
 pinMode (RLED, OUTPUT); // Set Red LED as Output
 pinMode (BUTTON, INPUT); // Set button as input (not required)
}
/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); // Read the button state
 if (last != current) // If it's different...
 {
 delay(5); // Wait 5ms
 current = digitalRead(BUTTON); // Read it again
 }
 return current; // Return the current value
}
/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly
* Note, since the RGB LED is COMMON ANODE, you must set the
* cathode pin for each color LOW for that color to turn ON.
*/
void setMode(int mode)
{
 //White blinking 
 if (mode == 1)
 {

 analogWrite(RLED, 255);
 analogWrite(GLED, 255);
 analogWrite(BLED, 255);

 delay(50); 

 analogWrite(RLED, 0);
 analogWrite(GLED, 0);
 analogWrite(BLED, 0);

 delay(50); 

 }
 //purple bright and dim 
 else if (mode == 2)
 {

   
  for (int i=0; i<130; i++)
 {
 analogWrite(RLED, i);
 analogWrite(BLED, i); 
 delay(1);
 }
 for (int i=127; i>=0; i--)
 {
 analogWrite(RLED, i);
 analogWrite(BLED, i); 
 delay(1);
 }

 }


 
 //Red fades to blue and then back 
 else if (mode == 3)
 {

 analogWrite(RLED, 255);
 analogWrite(BLED, 0); 

  for (int i=255; i>=0; i--){
    
  
  if(debounce(lastButton == true)){
    break; 
    }
 
 analogWrite(RLED, i--); 
 delay(20);
 }

 
 for (int i=0; i<255; i++)
 {
  if(debounce(lastButton == true)){
    break; 
  }
    
 analogWrite(BLED, i++);
 delay(20);
 }

  for (int i=255; i>=0; i--)
 {
  if(debounce(lastButton == true)){
    break; 
 }
 analogWrite(BLED, i--); 
 delay(20);
 }

  for (int i=0; i<255; i++)
 {
  if(debounce(lastButton == true)){
    break; 
 }
 analogWrite(RLED, i++); 
 
 delay(20);
 }

 
 
 }

 else if(mode == 4)
 {

  while(true){
  
  if(debounce(lastButton == true)){
    break;
  }
  
  int i = random(0, 255); 
  int j = random(0, 255); 
  int k = random(0, 255); 

  analogWrite(RLED, i); 
  analogWrite(GLED, j); 
  analogWrite(BLED, k); 
  }
 }
  
 
 //OFF (mode = 0)

 else
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }
}


void loop()
{
 currentButton = debounce(lastButton); // Read debounced state
 if (lastButton == LOW && currentButton == HIGH) // If it was pressed...
 {
 ledMode++; // Increment the LED value
 }
 lastButton = currentButton; // Reset button value
 // If you've cycled through the different options,
 // reset the counter to 0
 if (ledMode == 5) {
  ledMode = 0;
 }
 setMode(ledMode); // Change the LED state

}
