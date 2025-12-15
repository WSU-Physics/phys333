#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

// Pin definitions
#define BUTTON_PIN 2
#define LED_PIN_0 0
#define LED_PIN_1 1
const int HX711_dout = 4; 
const int HX711_sck = 5; 

// Variables
int buttonState = 0;
int ledBrightness0 = 0;
int ledBrightness1 = 0;
bool buttonPressed = false;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

void setup() {
  Serial.begin(57600); delay(10);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Using internal pull-up resistor
  pinMode(LED_PIN_0, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  analogWrite(LED_PIN_0, ledBrightness0); // Initialize LED brightness
  analogWrite(LED_PIN_1, ledBrightness1); // Initialize LED brightness
  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      float j = i / 28.35;
      if (ledBrightness0 == 0) {
      ledBrightness0 = 255;
      ledBrightness1 = 0;
      Serial.print("grams = ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
    }
      if (ledBrightness0 == 255){
      ledBrightness0 = 0;
      ledBrightness1 = 255;
      Serial.print("oz = ");
      Serial.println(j);
      newDataReady = 0;
      t = millis();
    }
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }

}
