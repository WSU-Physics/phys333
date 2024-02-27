
const int SONAR_PIN = A0;   // Analog pin connected to the sensor output
const int R_LED = 11; // Red LED on pin 9
const int G_LED = 10; // Green LED on pin 10
const int B_LED = 9; // Blue LED on pin 11
const float VOLTAGE_SUPPLY = 5.0; // Voltage supply to the sensor in volts
const float VOLTAGE_PER_INCH = VOLTAGE_SUPPLY / 512.0; // Voltage per inch scaling factor

const float DISTANCE_THRESHOLD_HALF_INCH = 0.5; // Distance threshold in inches for red color

void setup() {
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read analog voltage from the sensor
  int sensorValue = analogRead(SONAR_PIN);
  
  // Convert analog voltage to inches
  float distanceInches = sensorValue * VOLTAGE_PER_INCH;
  
  // Output distance
  Serial.print("Distance: ");
  Serial.print(distanceInches);
  Serial.println(" inches");
  
  // Change LED color based on distance
  if (distanceInches <= DISTANCE_THRESHOLD_HALF_INCH) {
    // Close object detected, turn on red LED
    digitalWrite(R_LED, HIGH);
    digitalWrite(G_LED, LOW);
    digitalWrite(B_LED, LOW);
  } else {
    // Far object detected, turn off all LEDs
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
    digitalWrite(B_LED, LOW);
  }
  
  delay(1000);
}