const int BLED=9;
const int GLED=10;
const int RLED=11;
const int BUTTON=2;

boolean lastButton = LOW;
boolean currentButton=LOW;
int ledMode = 0;

void setup() {
  // put your setup code here, to run once:
pinMode (BLED, OUTPUT); //Set Blue LED as Output
pinMode (GLED, OUTPUT); //Set Green LED as Output
pinMode (RLED, OUTPUT); //Set Red LED as Output
pinMode (BUTTON, INPUT); //Set button as input
}


boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); //Read the button state
 if (last != current) 
 {
 delay(5); //wait 5ms
 current = digitalRead(BUTTON); 
 }
 return current; 
}

void setMode(int mode)
{
 //RED
 if (mode == 1)
 {
 digitalWrite(RLED, HIGH);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }
 //GREEN
 else if (mode == 2)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, HIGH);
 digitalWrite(BLED, LOW);
 }
 //BLUE
 else if (mode == 3)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 //PURPLE (RED and BLUE)
 if (mode == 4)
 {
 analogWrite(RLED, 127);
 analogWrite(GLED, 0);
 analogWrite(BLED, 127);
 }
 //TEAL (BLUE and GREEN)
 else if (mode == 5)
 {
 analogWrite(RLED, 0);
 analogWrite(GLED, 127);
 analogWrite(BLED, 127);
 }
 //YELLOW
 else if (mode == 6)
 {
 analogWrite(RLED, 127);
 analogWrite(GLED, 127);
 analogWrite(BLED, 0);
 }
 //WHITE (GREEN and RED and BLUE)
 else if (mode == 7)
 {
 analogWrite(RLED, 85);
 analogWrite(GLED, 85);
 analogWrite(BLED, 85);
 }
//OFF (mode = 0)
 else
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }
}

void loop() {
currentButton = debounce(lastButton); //read deboucned state
 if (lastButton == LOW && currentButton == HIGH) 
 {
 ledMode++; //increment the LED value
 }
 lastButton = currentButton; //reset button value
 if (ledMode == 8) ledMode = 0;
 setMode(ledMode);
}




