// Define LED pin constants
const int RED_PIN = 11; // Pin connected to Red LED
const int GREEN_PIN = 10; // Pin connected to Green LED
const int BLUE_PIN = 9; // Pin connected to Blue LED

void setup() {
  // Set the LED pins as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Turn on the Red LED
  digitalWrite(RED_PIN, HIGH); // Turns the LED ON
  delay(1000); // Wait for 1 second
  digitalWrite(RED_PIN, LOW); // Turns the LED OFF
  // Repeat for green and blue LEDs...
}
