int led = 53;                // the pin that the LED is attached to
int sensor = 52;              // the pin that the sensor is attached to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
unsigned long motionStartTime = 0; // variable to store the time when motion started
unsigned long motionTimeout = 5000; // timeout for motion detection in milliseconds (5 seconds)

void setup() {
  pinMode(led, OUTPUT);      // initialize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial
}

void loop(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
      motionStartTime = millis(); // record the time when motion started
    }
  } 
  else {
    if (state == HIGH && millis() - motionStartTime >= motionTimeout) {
      digitalWrite(led, LOW); // turn LED OFF if motion has stopped for the specified timeout
      Serial.println("Motion stopped!");
      state = LOW;       // update variable state to LOW
    }
  }
}