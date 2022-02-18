/**
   Function: customPWM

   Pin: Pin number to execute PWM on
   dutyCycle: Percentage of brightness. 0 is off and 100 is maximum brightness
   duration: how long the LED should be on for in microseconds
*/
const int bLED = 8;
void customPWM (int pin, float dutyCycle, double duration) {

  static const int period = 10000;
  float brightness;
  float T_on, T_off;

  brightness = dutyCycle * 10;
  T_on = (brightness * period) / 1000;
  T_off = period - T_on;

  for (double i = 0; i <= duration; i++) {
    // Turn on
    digitalWrite(pin, HIGH);
    // delay for Ton
    delayMicroseconds(T_on);
    // Turn off
    digitalWrite(pin, LOW);
    // delay for Toff
    delayMicroseconds(T_off);
  }
}

void setup() {
  // set blue LED pin to output
  pinMode(bLED, OUTPUT);
}

void loop() {
  // call the customPWM function
  for (float i = 0; i <= 100 ; i += 1.5) {
      customPWM(bLED, i , 10);
  }
}
