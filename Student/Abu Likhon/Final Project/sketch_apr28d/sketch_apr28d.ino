int soundsensor = 8; // Sound sensor connected to port 8
int leds[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Array to hold LED pin numbers
int clapCount = 0;
unsigned long lastClapTime = 0;
boolean lightsOn = false; // Track the state of lights

void setup() {
  pinMode(soundsensor, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 baud to debug
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT); // Initialize LED pins as output
  }
}

void loop() {
  int sensorStatus = digitalRead(soundsensor);
  unsigned long currentTime = millis();

  // Detect claps with debounce
  if (sensorStatus == 0) {
    if (currentTime - lastClapTime > 250) { // Debounce check (250 milliseconds)
      lastClapTime = currentTime;
      clapCount++;
      Serial.println("Clap detected");
    }
  }

  // Process claps after a quiet period
  if (currentTime - lastClapTime > 400 && clapCount > 0) { // Evaluation time after last clap
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
