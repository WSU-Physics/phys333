#include <LiquidCrystal.h>
#include <IRremote.h>

/**
   PHYS 333 - Microprocessor Electronics
   Dr. Adam P. Beardsley
   Final Project
   Sheikh Fahad

   This project will take an input from a remote through an IR receiver
   and control a fan, an LED, and show the status of both the output devices
   through an LCD screen
*/

#define on_off_key 41565
#define fan_on_off_key 36975
#define light_on_off_key 57375
#define fan_speed_up 25245
#define fan_speed_down 43095
#define bright_light 49725
#define dim_light 8925

// defining arduino pins
int receiver_pin = 8;
int fan_pin = 9;
int led_pin = 10;

// defining parameters in the LCD object
LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

//arrays for fan speed and brightness
int fan_speed[] = {0, 70, 180, 255};
int led_brightness[] = {0, 50, 127, 255};

//counters
int on_off = 0;
int fan_on_off = 0;
int light_on_off = 0;
int current_fan_speed = fan_speed[2];
int current_light_status = led_brightness[2];

IRrecv receiver(receiver_pin);
decode_results output;

void setup() {
  Serial.begin(9600); // need to print out the values from the remote in order to make it work
  receiver.enableIRIn();
  lcd.begin(16, 2);
  pinMode(fan_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  lcd.setCursor(5, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(6, 1);
  lcd.print("OFF!");
}

String fanStatus(int fan) {
  if (fan == fan_speed[1]) {
    return "LOW";
  }
  else if (fan == fan_speed[2]) {
    return "MED";
  }
  else if (fan == fan_speed[3]) {
    return "HIGH";
  }
  else {
    return "OFF";
  }
}

String lightStatus(int light) {
  if (light == led_brightness[1]) {
    return "LOW";
  }
  else if (light == led_brightness[2]) {
    return "MED";
  }
  else if (light == led_brightness[3]) {
    return "HIGH";
  }
  else {
    return "OFF";
  }
}

void lcdOutput(int fanSpeed, int brightness) {
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("Fan Speed:  ") + String(fanStatus(fanSpeed)));
  lcd.setCursor(0, 1);
  lcd.print(String("Brightness: ") + String(lightStatus(brightness)));
}
void loop() {
  if (receiver.decode(&output)) {
    unsigned int value = output.value;
    switch (value) {
      case on_off_key:
        if (on_off == 1) {
          analogWrite(fan_pin, fan_speed[0]);
          analogWrite(led_pin, led_brightness[0]);
          on_off = 0;
          lcd.clear();
          delay(500);
          lcd.setCursor(5, 0);
          lcd.print("SYSTEM");
          lcd.setCursor(6, 1);
          lcd.print("OFF!");
        }
        else {
          analogWrite(fan_pin, fan_speed[3]);
          delay(10);
          analogWrite(fan_pin, current_fan_speed);
          analogWrite(led_pin, current_light_status);
          on_off = 1;
          lcd.clear();
          delay(500);
          lcd.setCursor(5, 0);
          lcd.print("SYSTEM");
          lcd.setCursor(7, 1);
          lcd.print("ON");
          lcdOutput(current_fan_speed, current_light_status);
        }
        break;
      case fan_on_off_key:
        if (on_off == 1) {
          if (fan_on_off == 1) {
            analogWrite(fan_pin, fan_speed[0]);
            fan_on_off = 0;
            lcdOutput(fan_speed[0], current_light_status);
          }
          else {
            analogWrite(fan_pin, fan_speed[3]);
            delay(10);
            analogWrite(fan_pin, current_fan_speed);
            fan_on_off = 1;
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
      case light_on_off_key:
        if (on_off == 1) {
          if (light_on_off == 1) {
            analogWrite(led_pin, led_brightness[0]);
            light_on_off = 0;
            lcdOutput(current_fan_speed, led_brightness[0]);
          }
          else {
            analogWrite(led_pin, current_light_status);
            light_on_off = 1;
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
      case fan_speed_up:
        if (on_off == 1) {
          if (current_fan_speed == fan_speed [1]) {
            analogWrite(fan_pin, fan_speed[3]);
            delay(10);
            analogWrite(fan_pin, fan_speed[2]);
            current_fan_speed = fan_speed[2];
            lcdOutput(current_fan_speed, current_light_status);
          }
          else {
            analogWrite(fan_pin, fan_speed[3]);
            current_fan_speed = fan_speed[3];
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
      case fan_speed_down:
        if (on_off == 1) {
          if (current_fan_speed == fan_speed [3]) {
            analogWrite(fan_pin, fan_speed[2]);
            current_fan_speed = fan_speed[2];
            lcdOutput(current_fan_speed, current_light_status);
          }
          else {
            analogWrite(fan_pin, fan_speed[1]);
            current_fan_speed = fan_speed[1];
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
      case bright_light:
        if (on_off == 1) {
          if (current_light_status == led_brightness [1]) {
            analogWrite(led_pin, led_brightness[2]);
            current_light_status = led_brightness[2];
            lcdOutput(current_fan_speed, current_light_status);
          }
          else {
            analogWrite(led_pin, led_brightness[3]);
            current_light_status = led_brightness[3];
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
      case dim_light:
        if (on_off == 1) {
          if (current_light_status == led_brightness [3]) {
            analogWrite(led_pin, led_brightness[2]);
            current_light_status = led_brightness[2];
            lcdOutput(current_fan_speed, current_light_status);
          }
          else {
            analogWrite(led_pin, led_brightness[1]);
            current_light_status = led_brightness[1];
            lcdOutput(current_fan_speed, current_light_status);
          }
        }
        break;
    }
    Serial.println(value);
    receiver.resume();
  }
}
