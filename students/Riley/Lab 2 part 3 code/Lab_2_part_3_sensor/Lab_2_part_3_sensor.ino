// Temperature Alert!
const int BLED=9; // Blue LED Cathode on Pin 9
const int GLED=10; // Green LED Cathode on Pin 10
const int RLED=11; // Red LED Cathode on Pin 11
const int WLed = 5; // White LED on pin 5
const int YLed = 6; // Yellow LED on pin 6
const int TEMP=0; // Temp Sensor is on pin A0
const int LOWER_BOUND_C=23; // Lower Threshold
const int UPPER_BOUND_C=27; // Upper Threshold
const int LOWER_BOUND_F=74; // Lower Threshold
const int UPPER_BOUND_F=82; // Upper Threshold
const int BUTTON=2; //BUTTON on pin 2
int value = 0; // Variable to hold analog reading
float volt; //convert to voltage
float DegC;  // in celcius
float DegF; // in fahrenheit
void setup()
{
  Serial.begin(9600);
 pinMode (BLED, OUTPUT); // Set Blue LED as Output
 pinMode (GLED, OUTPUT); // Set Green LED as Output
 pinMode (RLED, OUTPUT); // Set Red LED as Output
}

void loop()
{
 value = analogRead(TEMP);
  volt = value*(5.0/1023);    // Convert binary to volts (use 5.0 to make sure it reads float not int)
  DegC = (volt*100)-50;      // Convert voltage to temperature ( 10mV per deg celsius) (750mV at 25 deg celsius)(((volt*1000)-500)/10)
  DegF = (DegC*9/5)+32;       // Convert C to F
if (digitalRead(BUTTON) == LOW){
  digitalWrite(YLed, HIGH);
  digitalWrite(WLed,LOW);
  
   // LED is Blue
 if (DegF < LOWER_BOUND_F)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 // LED is Red
 else if (DegF > UPPER_BOUND_F)
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
 Serial.print("Degrees Fahrenheit: ");
 Serial.println(DegF);
  delay(1000);
}

else{
  digitalWrite(YLed, LOW);
  digitalWrite(WLed,HIGH);
 if (DegC < LOWER_BOUND_C)
 {
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, HIGH);
 }
 // LED is Red
 else if (DegC > UPPER_BOUND_C)
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
 Serial.print("Degrees Celsius: ");
 Serial.println(DegC);
 delay(1000);
}
}
