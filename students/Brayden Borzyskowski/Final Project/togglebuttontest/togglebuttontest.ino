// Pin definitions
#define BUTTON_PIN 2
#define LED_PIN_0 0
#define LED_PIN_1 1

// Variables
int buttonState = 0;
int ledBrightness0 = 0;
int ledBrightness1 = 0;
bool buttonPressed = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Using internal pull-up resistor
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  analogWrite(LED_PIN_0, ledBrightness0); // Initialize LED brightness
  analogWrite(LED_PIN_1, ledBrightness1); // Initialize LED brightness
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(BUTTON_PIN);

  // Check if the button is pressed and released
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    // Toggle LED brightness
    if (ledBrightness0 == 0) {
      ledBrightness0 = 255;
      ledBrightness1 = 0;
    } else {
      ledBrightness0 = 0;
      ledBrightness1 = 255;
    }
    analogWrite(LED_PIN_0, ledBrightness0);
    analogWrite(LED_PIN_1, ledBrightness1);
  } else if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }

  // Delay to debounce button
  delay(50);
}
