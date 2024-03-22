const int BLED=10; // Blue LED on pin 10
const int RLED=9; // Red LED on pin 9
const int TEMP=A0; // Temp Sensor is on pin A0
int val = 0; // Variable to hold analog reading

void setup() {
    pinMode(BLED, OUTPUT); // Set Blue LED as Output
    pinMode(RLED, OUTPUT); // Set Red LED as Output
    Serial.begin(9600); // Start serial communication
}

void loop() {
    val = analogRead(TEMP); // Read the value from the temperature sensor

    // Assuming the value is directly proportional to temperature
    // and the range 145-165 is considered 'normal' temperature
    if (val < 145) {
        // Temperature is low
        digitalWrite(BLED, HIGH); // Turn Blue LED on
        digitalWrite(RLED, LOW);  // Turn Red LED off
    } else if (val > 165) {
        // Temperature is high
        digitalWrite(BLED, LOW);  // Turn Blue LED off
        digitalWrite(RLED, HIGH); // Turn Red LED on
    } else {
        // Temperature is normal
        digitalWrite(BLED, LOW);  // Turn Blue LED off
        digitalWrite(RLED, LOW);  // Turn Red LED off
    }

    Serial.println(val); // Print the value to the serial monitor
    delay(100); // Delay for a short period of time before reading again
}

