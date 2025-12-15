void setup() {
  Serial.begin(9600); // Initialize serial communication
}
 
void loop() {
  unsigned long duration; // Variable to store the pulse duration
  float distance_cm; // Variable to store the distance in centimeters
 
  // Trigger the sensor
  pinMode(0, OUTPUT); // Set pin 0 (RX) as OUTPUT for triggering
  digitalWrite(0, LOW);
  delayMicroseconds(2);
  digitalWrite(0, HIGH);
  delayMicroseconds(10);
  digitalWrite(0, LOW);
 
  // Measure the duration of the echo pulse
  pinMode(0, INPUT); // Set pin 0 (RX) as INPUT for reading echo
  duration = pulseIn(0, HIGH);
 
  // Convert the pulse duration to distance (in centimeters)
  distance_cm = duration * 0.034 / 2; // Speed of sound in air is approximately 0.034 cm/microsecond
 
  // Print distance reading to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
 
  delay(1000); // Delay before taking the next reading
