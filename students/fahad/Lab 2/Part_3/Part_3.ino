/**
   Sheikh Fahad
   JT7372WD
   LED Nightlight with single LED
   LED will turn on when natural light will be low
   LED will turn off when natural light will be high
*/


//Constants
const int aPin = A0; // photoresistor analog pin A0
const int ledPin = 9; // LED pin 9
int MAX = 30; // natural light after testing and calibrating

//Variables
int value; // analog read value from the photocell

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(aPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(aPin);
  if (value > MAX) {
    value = MAX;
  }
  Serial.print(value); //Debug
  Serial.println(" This is value"); //Debug
  int pwm;
  pwm = map(value, 0, MAX, 255, 0); //mapping
  Serial.print(pwm); //Debug
  Serial.println(" This is pwm"); //Debug
  analogWrite(ledPin, pwm); //PWM is used so that the light slowly increases and decreases
  delay(500); //Small delay
}
