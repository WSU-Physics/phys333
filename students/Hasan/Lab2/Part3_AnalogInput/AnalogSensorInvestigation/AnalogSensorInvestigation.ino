
//Set pins for flex sensor and servo 
const int flexsensor = A0; 

const int servo = 9; 

void setup() {
  // put your setup code here, to run once:

  //set servo to be the output 
  pinMode(servo, OUTPUT); 

  //Use Serial and servo, 
  // unfortunately, flex sensor has default of 600
  //So I needed to use serial to see what start was 
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  //read flexSensor
  int x = analogRead(flexsensor); 
  Serial.println(x); 

  //map result of flexsensor to 0 - 180 degree servo
  int val = map(x, 650, 800, 0, 180 ); 

   //write the value to the servo pin
  analogWrite(servo, val); 

  //give room to catch up 
  delay(15); 
}
