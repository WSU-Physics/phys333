#include <avr/io.h>
#include <util/delay.h>
#define LED_START_PIN 0
#define LED_END_PIN 7
#define BUTTON1_PIN 9
#define BUTTON2_PIN 11

// Define debounce time
#define DEBOUNCE_TIME 50 // 50 ms

void setup() {
  // setting the pins to use as output
  for (int i = LED_START_PIN; i <= LED_END_PIN; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON1_PIN, INPUT_PULLUP); 
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

bool checkButtonPress(int buttonPin) {
  static unsigned long lastDebounceTime = 0;
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(buttonPin);
  bool buttonPressed = false;

  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    if (buttonState == LOW) {
      buttonPressed = true;
    }
  }
  lastButtonState = buttonState;
  return buttonPressed;
}

// Function to light up LEDs sequentially
void lightUpLEDs(int startPin, int endPin) {
  for (int i = startPin; i <= endPin; i++) {
    digitalWrite(i, HIGH); // LED on
    delay(500); // Delay 500 milliseconds
    digitalWrite(i, LOW); // LED off
  }
}

void loop() {
  // Button 1 pressed
  if (checkButtonPress(BUTTON1_PIN)) {
    // Light up LEDs 0-3 sequentially
    lightUpLEDs(LED_START_PIN, LED_START_PIN + 3);
    // Turn off LEDs 0-3
    for (int i = LED_START_PIN; i <= LED_START_PIN + 3; i++) {
      digitalWrite(i, LOW);
    }
    //Button 9 released
    while (digitalRead(BUTTON1_PIN) == LOW) {
      delay(10);
    }
  }

  //Button 2 pressed
  if (checkButtonPress(BUTTON2_PIN)) {
    // Light up LEDs 4-7 sequentially
    lightUpLEDs(LED_START_PIN + 4, LED_END_PIN);
    // Turn off LEDs 4-7
    for (int i = LED_START_PIN + 4; i <= LED_END_PIN; i++) {
      digitalWrite(i, LOW);
    }
    //Button 2 released
    while (digitalRead(BUTTON2_PIN) == LOW) {
      delay(10);
    }
  }
}
