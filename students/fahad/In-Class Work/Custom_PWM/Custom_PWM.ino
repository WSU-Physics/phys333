// Turn on an LED using PWM
// Turn on another LED using our own PWM function

const int yLED = 9;
// constant for my blue LED
const int bLED = 8;

/** Write a PWN functon
    Inputs:
        Pin number
        PWM value corresponds to brightness (0 for off, 255 for brightest setting
        period (in micrseconds)
    Outputs:
        none
 **/

void PWM(int pin, double brightness, double period) {
  int duty_cycle;
  double T_on;
  double T_off;

  // Calculate T_on
  duty_cycle = brightness / 255;
  T_on = duty_cycle * period;

  // Calculate T_off
  T_off = period - T_on;

  // Turn on
  digitalWrite(pin, HIGH);

  // Delay for T_on
  delayMicroseconds(T_on);

  // Turn off
  digitalWrite(pin, LOW);

  // Delay for T_off
  delayMicroseconds(T_off);
}



void setup() {
  // put pin mode to output
  pinMode(yLED, OUTPUT);
  // set blue LED pin to output
  pinMode(bLED, OUTPUT);

}

void loop() {

  int brightness = 255;
  int period = 2040000;
  // Set yLED brightness
  analogWrite(yLED, brightness);
  // call self-made PWN function
  for(int i=0; i<255; i++){
  PWM(bLED, i, period);
  }

}
