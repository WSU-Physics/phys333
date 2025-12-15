#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int pumpPin = 11;
const int greenLedPin = 7;
const int yellowLedPin = 6;
const int redLedPin = 5;

int waterLevel = 0;
int pumpsSinceColorChange = 0;

void printTime(DateTime dt);

//initialization
//the setup function initializes the pins for the pump and LEDs and starts the serial communication
//it also sets the RTC to a specific date and time if the RTC is found

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  Serial.begin(9600); 

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); 
  }

  Serial.println("RTC initialized.");
  
  rtc.adjust(DateTime(2024, 4, 28, 7, 00, 0));
  Serial.println("Initial time set on RTC: 2024-04-28 6:59:00");
}

//main loop
//the loop() function runs continuously and performs the following actions:
//gets the current time from the RTC
//prints the current time
//checks if it’s time to start the pump is called at 7:00:00
//updates the LED indicators based on the water level

void loop() {
  DateTime now = rtc.now();

  Serial.print("Current Time: ");
  printTime(now); 

  if (now.hour() == 7 && now.minute() == 00 && now.second() == 0) {
    Serial.println("Starting pump...");
    startPump();
  }

  updateLedLevelIndicators();

  delay(1000); 
}

//pump activation
//the start pump function turns the pump on for 10 seconds and then off
//it increments the pumpsSinceColorChange counter 
//if the pump has been activated three times, it calls changeLedLevelColor to update the LED color

void startPump() {
  digitalWrite(pumpPin, HIGH); 
  Serial.println("Pump activated");
  delay(10000); 
  digitalWrite(pumpPin, LOW); 
  pumpsSinceColorChange++;

  if (pumpsSinceColorChange >= 3) {
    Serial.println("Changing LED color...");
    changeLedLevelColor();
    pumpsSinceColorChange = 0;
  }
}


//LED color change
//the changeLedLevelColor function changes the LED color based on the waterLevel
//yellow LED for water level 1, red LED for levels 2 and 3
//if the water level reaches 3, it blinks the red LED five times and resets the water level to 0 (green LED)

void changeLedLevelColor() {
  waterLevel++;

  if (waterLevel == 1) {
    setLedColor(LOW, HIGH, LOW); // yellow LED
  } else if (waterLevel == 2) {
    setLedColor(LOW, LOW, HIGH); // red LED
  } else if (waterLevel == 3) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(redLedPin, HIGH);
      delay(500);
      digitalWrite(redLedPin, LOW);
      delay(500);
    }
    waterLevel = 0; 
    setLedColor(HIGH, LOW, LOW); // green LED
  }
}
//LED update
//the updateLedLevelIndicators() function sets the appropriate LED color based on the current waterLevel


void updateLedLevelIndicators() {
  setLedColor(LOW, LOW, LOW);

  if (waterLevel == 0) {
    digitalWrite(greenLedPin, HIGH); // green LED
  } else if (waterLevel == 1) {
    digitalWrite(yellowLedPin, HIGH); // yellow LED
  } else if (waterLevel == 2 || waterLevel == 3) {
    digitalWrite(redLedPin, HIGH); // red LED
  }
}

void setLedColor(int green, int yellow, int red) {
  digitalWrite(greenLedPin, green);
  digitalWrite(yellowLedPin, yellow);
  digitalWrite(redLedPin, red);
}

// print time
// the printTime function outputs the current time and date in serial monitor

void printTime(DateTime dt) {
  Serial.print(dt.year());
  Serial.print("-");
  if (dt.month() < 10) {
    Serial.print("0");
  }
  Serial.print(dt.month());
  Serial.print("-");
  if (dt.day() < 10) {
    Serial.print("0");
  }
  Serial.print(dt.day());
  Serial.print(" ");
  Serial.print(dt.hour());
  Serial.print(":");
  if (dt.minute() < 10) {
    Serial.print("0");
  }
  Serial.print(dt.minute());
  Serial.print(":");
  if (dt.second() < 10) {
    Serial.print("0");
  }
  Serial.println(dt.second());
}



