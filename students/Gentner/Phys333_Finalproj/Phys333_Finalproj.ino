//state machine

//Case 1 - If in bright light then do nothing
  //Do nothing
//Case 2 - If photoresitor detects low light then turn on IR led
  //Turn on IRLED
  //Case 1 - If Detector reads IR then do nothing
    //Do Nothing
  //Case 2 - Break in IR 
    //Check Debounce setting
    //If Debounce is true 
    //turn on Lights and do not check photoresistor
    //Leave on for ------
    //Turn off LED 
    //Return to top

const int Lights=13;
const int PR=11;
const int IR=4;
const int IRD=A0;
boolean lastDetect = LOW; // variable containing the previous Detect state
boolean currentDetect = LOW; // variable constaing the current Detect state
unsigned int ledMode = 0; // present state of the Blue Light


void setup() {
pinMode(IR,OUTPUT);
pinMode(IRD,INPUT);
Serial.begin(9600);
}

boolean debounce(boolean last)
{
 boolean current = digitalRead(IRD); // Read the Detect state
 if (1020 >= current) // if it's less than ambient
 {
 delay(3); //Wait 5ms
 currentDetect = digitalRead(IRD); //Read it again
 }
 return current; //Return the current value
}



void loop() {
  //Detector Debounce
  {
    currentDetect = debounce(lastDetect); //Read debounced state
 if (lastDetect == LOW &&currentDetect == HIGH) //if it was pressed...
 {
 ledMode++  ; //Increase the LED state value
 }
 lastDetect =currentDetect; //Reset Detect value
 if (ledMode == 2) ledMode=1;
 switch(ledMode);
  // put your main code here, to run repeatedly:
  }
int DetectRead = 0;
int Detect = 0;
digitalWrite(IR, HIGH);
DetectRead = analogRead(IRD);
Detect=map(DetectRead, 0, 1023, 0, 5000);
Serial.println(DetectRead);
delay(100);
//Serial.print("High ");

//Serial.print(" - ");
//Serial.println(Detect);
//delay(500);
//digitalWrite(IR,LOW);
//DetectRead = analogRead(IRD);
//Detect=map(DetectRead, 0, 1023, 0, 5000);
//Serial.print("Low ");
//Serial.print(DetectRead);
//Serial.print(" - ");
//Serial.println(Detect);
//delay(500);
}
