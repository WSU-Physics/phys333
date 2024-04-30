#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 7;

char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '*', 'a', 'b', 'c'},
  {'4', '5', '6', 's', 'd', 'e', 'f'},
  {'1', '2', '3', 't', 'g', 'h', 'i'},
  {'n', '0', '#', 'p', 'j', 'k', 'l'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {13, 12, 11, 10, 9, 8, 7};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int led = 53;                // the pin that the LED is attached to
int sensor = 52;              // the pin that the sensor is attached to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
unsigned long motionStartTime = 0; // variable to store the time when motion started
unsigned long motionTimeout = 5000; // timeout for motion detection in milliseconds (5 seconds)
unsigned long entryDelay = 10000; // entry delay in milliseconds (10 seconds)
unsigned long exitDelay = 10000;  // exit delay in milliseconds (10 seconds)
bool systemArmed = false;    // Variable to track whether the system is armed or not
bool sensorEnabled = true;   // variable to track whether the sensor is enabled or disabled
bool entryInProgress = false; // flag to track if entry delay is in progress
bool exitInProgress = false;  // flag to track if exit delay is in progress

void setup() {
  pinMode(led, OUTPUT);      // initialize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial
}

void loop() {
  char key = customKeypad.getKey();  // Check for keypad input
  
  if (key == '#') { // Toggle the sensor when '#' key is pressed
    sensorEnabled = !sensorEnabled;

    // Print status to serial monitor
    Serial.print("Sensor ");
    Serial.println(sensorEnabled ? "enabled" : "disabled");
  }

  if (sensorEnabled && systemArmed) {
    val = digitalRead(sensor);   // read sensor value
    if (val == HIGH) {           // check if the sensor is HIGH
      digitalWrite(led, HIGH);   // turn LED ON
      delay(100);                // delay 100 milliseconds 

      if (state == LOW) {
        Serial.println("Motion detected!"); 
        state = HIGH;       // update variable state to HIGH
        motionStartTime = millis(); // record the time when motion started
      }
    } 
    else {
      if (state == HIGH && millis() - motionStartTime >= motionTimeout) {
        digitalWrite(led, LOW);  // turn LED OFF if motion has stopped for the specified timeout
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
      }
    }
  } else {
    digitalWrite(led, LOW); // turn off LED if sensor is disabled or system is disarmed
  }

  // Check for entry/exit delay
  if (entryInProgress || exitInProgress) {
    delay(1000); // wait 1 second
    if (entryInProgress) {
      Serial.println("Entry delay in progress...");
      if (millis() - motionStartTime >= entryDelay) {
        Serial.println("Entry delay complete. System armed.");
        entryInProgress = false;
        systemArmed = true;
      }
    }
    if (exitInProgress) {
      Serial.println("Exit delay in progress...");
      if (millis() - motionStartTime >= exitDelay) {
        Serial.println("Exit delay complete. System disarmed.");
        exitInProgress = false;
        systemArmed = false;
      }
    }
  }

  // Check for keypad input for arming/disarming
  if (key == '*') { // Disarm the system when '*' key is pressed
    if (systemArmed) {
      exitInProgress = true;
      motionStartTime = millis();
    }
  } 
  else if (key == 'p') { // Arm the system when 'p' key is pressed
    if (!systemArmed) {
      entryInProgress = true;
      motionStartTime = millis();
    }
  }
}