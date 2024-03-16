//Lab 2 part 3
//Distance sensor as analog input 

const int input_pin = A0;   //Analog input from sensor
const int led = 13;         //Digital utput pin
const float voltage = 5.0;        //Sensor power supply
const float voltage_per_in = voltage / 512.0; 
 
const float half_inch_ref = 0.5; 
 
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {
  int analog_value = analogRead(input_pin);     // Read analog voltage from the sensor
 
  
  float distance = analog_value * voltage_per_in;   // Convert analog voltage to inches
 
  // Output distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" inches");
 
 
  if (distance <= half_inch_ref) {
    digitalWrite(led, HIGH);        // Turn on LED if objects is close 
  } 
  else {
    digitalWrite(led, LOW);         // Turn off LED if no object detected
  }
 
  delay(1000);
}