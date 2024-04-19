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
const int IRD=3;


void setup() {
pinMode(4,OUTPUT);
pinMode(3,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int DetectRead = 0;
int Detect = 0;
digitalWrite(IR, HIGH);
DetectRead = analogRead(IRD);
Detect=map(DetectRead, 0, 1023, 0, 5000);
Serial.print("High ");
Serial.print(DetectRead)
Serial.println(Detect);
delay(500);
digitalWrite(IR,LOW);
DetectRead = analogRead(IRD);
Detect=map(DetectRead, 0, 1023, 0, 5000);
Serial.print("Low ");
Serial.println(Detect);
delay(500);
}
