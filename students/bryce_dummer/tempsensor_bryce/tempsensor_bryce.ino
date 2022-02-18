/*
Exploring Arduino, Second Edition
Code Listing 3-2: Temperature Alert Sketch
https://www.exploringarduino.com/content2/ch3
Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )
*/

// Temperature Alert!
const int BLED=9;          // Blue LED Cathode on Pin 9
const int GLED=10;         // Green LED Cathode on Pin 10
const int RLED=11;         // Red LED Cathode on Pin 11
const int TEMP=0;          // Temp Sensor is on pin A0
const int BUTTON=7;

const int LOWER_BOUND=20; // Lower Threshold
const int UPPER_BOUND=23; // Upper Threshold

int val = 0;               // Variable to hold analog reading


void setup()
{
  pinMode (BLED, OUTPUT); // Set Blue LED as Output
  pinMode (GLED, OUTPUT); // Set Green LED as Output
  pinMode (RLED, OUTPUT); // Set Red LED as Output
  pinMode (BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  float voltage;
  float degree;
  float degreef;
  val = analogRead(TEMP);

  voltage = val*(5.0/1023);
  degree = (voltage*100)-50.0;
  degreef = (degree * 9/5) + 32;

  if (BUTTON == HIGH)
  {
  Serial.println(degree);
  Serial.println("degrees Celsius");
  delay(1000);
  }
  else (BUTTON == LOW);
  {
  Serial.println(degreef);
  Serial.println("degrees Fahrenheit");
  delay(1000);
  }

  // LED is Blue
  if (degree < LOWER_BOUND)
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
  // LED is Red
  else if (degree > UPPER_BOUND)
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  // LED is Green
  else
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }

}
