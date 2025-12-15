// Define the analog pin connected to the sensor output
const int ANALOG_PIN = A0;
const float voltage = 5.0;        //Sensor power supply
const float voltage_per_in = voltage / 512.0; 
 

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(ANALOG_PIN);

  // Convert the analog value to distance (adjust the formula based on your sensor's specifications)
  float distance_cm = map(sensorValue, 0, 1023, 15, 600); // Example mapping from 0-1023 to 10-80 cm

  // Print the distance to the serial monitor
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print("\tDistance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

int analog_value = analogRead(ANALOG_PIN);     // Read analog voltage from the sensor
 
  
  float distance = analog_value * voltage_per_in;   // Convert analog voltage to inches

 
 
  delay(2000);
}
 
