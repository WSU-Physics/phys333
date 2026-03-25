const int trig = A0; 
const int echo = A1; 

const int green = 3; 
const int yellow = 4; 
const int red = 5; 

unsigned long previousMillis = 0; 
const long interval = 60; 

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT); 
  
  pinMode(green, OUTPUT); 
  pinMode(yellow, OUTPUT); 
  pinMode(red, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis(); 

  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; 

    long duration; 
    int distance; 

    //ultrasonic pulse
    digitalWrite(trig, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 

    duration = pulseIn(echo, HIGH, 25000); 
    //conversion of time to distance
    distance = duration * 0.034 / 2; 

    //LEDs OFF
    digitalWrite(green, LOW); 
    digitalWrite(yellow, LOW); 
    digitalWrite(red, LOW); 

    if(duration == 0 || distance < 5 || distance > 400) {
      //LEDs still OFF
    } else if (distance > 60) {
      digitalWrite(green, HIGH); 
    } else if (distance > 30) {
      digitalWrite(yellow, HIGH); 
    } else {
      digitalWrite(red, HIGH); 
    }
  }
}
