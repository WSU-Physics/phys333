// Define constants and variables
const int soundSensor = A0; // Microphone connected to analog pin A0
const int threshold = 550; // Threshold value to determine a clap
const int debounceTime = 250; // Debounce time in milliseconds
const int quietPeriod = 400; // Quiet period to finalize clap count
int leds[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Array to hold LED pin numbers
int clapCount = 0;
unsigned long lastClapTime = 0;
boolean lightsOn = false; // Track the state of lights

void setup() {
  pinMode(soundSensor, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud to debug
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT); // Initialize LED pins as output
  }
}

void loop() {
  int sensorValue = analogRead(soundSensor); // Read the sound level
  unsigned long currentTime = millis();

  // Detect claps with debounce
  if (sensorValue > threshold) {
    if (currentTime - lastClapTime > debounceTime) { // Debounce check
      lastClapTime = currentTime;
      clapCount++;
      Serial.println("Clap detected 0");
    }
  }

  // Process claps after a quiet period
  if (currentTime - lastClapTime > quietPeriod && clapCount > 0) {
    Serial.print("Clap Count: ");
    Serial.println(clapCount);
    if (clapCount == 2) {
      toggleLights();
    }
    clapCount = 0; // Reset clap counter after handling
  }
}

void toggleLights() {
  lightsOn = !lightsOn; // Toggle the current state of the lights
  for (int i = 0; i < 8; i++) {
    digitalWrite(leds[i], lightsOn ? HIGH : LOW); // Update LEDs to new state
  }
  Serial.println(lightsOn ? "Lights turned on." : "Lights turned off.");
}
