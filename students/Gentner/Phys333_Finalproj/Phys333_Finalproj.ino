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

const int Lights=12;
const int PR=11;
const int IR=4;
const int IRD=A0;
boolean lastDetect = LOW; // variable containing the previous Detect state
boolean currentDetect = LOW; // variable constaing the current Detect state
unsigned int ledMode = 1; // present state of the Blue Light


void setup() {
pinMode(IR,OUTPUT);
pinMode(IRD,INPUT);
Serial.begin(9600);
}

void loop() {
int DetectRead = 0;
int Detect = 0;


  //Detector Debounce
// {
  //   currentDetect = debounce(lastDetect);             //Read debounced state
  //   if (lastDetect >= 1000 && currentDetect <= 1015)  //if it was pressed...
  //   {
  //     ledMode++;  //Increase the LED state value
  //     Serial.print("LedMode-");
  //     Serial.print(ledMode);
  //     Serial.print(" ");
  //   }
// lastDetect = currentDetect;  //Reset Detect value
   if (ledMode == 3) ledMode = 1;

// }
//old test
/*
  digitalWrite(IR, HIGH);
  delay(500);
  DetectRead = analogRead(IRD);
  Detect=map(DetectRead, 0, 1023, 0, 5000);
  Serial.print("High ");
  Serial.print(DetectRead);
  Serial.print(" - ");
  Serial.println(Detect);
  delay(500);
  digitalWrite(IR,LOW);
  delay(500);
  DetectRead = analogRead(IRD);
  Detect=map(DetectRead, 0, 1023, 0, 5000);
  Serial.print("Low ");
  Serial.print(DetectRead);
  Serial.print(" - ");
  Serial.println(Detect);
  delay(500);
*/

switch (ledMode){
  case 1:
  {
  digitalWrite(Lights, LOW);
  digitalWrite(IR, HIGH);
  DetectRead = analogRead(IRD);
  Detect=map(DetectRead, 0, 1023, 0, 5000);
  Serial.print(DetectRead);
  Serial.print(" - ");
  Serial.println(Detect);
  delay(100);
  if (DetectRead <= 430)
{
  ledMode++;
}
}
  break;

case 2:
{
digitalWrite(Lights, HIGH);
delay(4000);
ledMode++;

  break;
}
}

}