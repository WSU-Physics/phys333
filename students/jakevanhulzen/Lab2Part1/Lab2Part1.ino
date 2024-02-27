// Function: pwm
// Practice writing functions and understanding 
// PWM by explicitly setting output high/low
// according to input parameters.
// Sets pin to HIGH, delays, sets to LOW, delays.
// 
// pin: Pin number to execute PWM on
// brightness: How bright the LED should be.
//             0 is off, 255 is maximum.
// period: period of pulse in microseconds
void pwm(int pin, double brightness, double period){
  // Calculate Ton and Toff
  double Ton;  // using double precision to avoid overflow
  double Toff;
  Ton = (brightness * period) / 255;
  Toff = period - Ton;
  
  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds(Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds(Toff);
}

void setup() {
  // Set pin mode to output
  pinMode(9, OUTPUT);
}

void loop() {
  // Vary brightness and period parameters
double brightness = 200;
double period = 2040; // in ms

  pwm(9, brightness, period);
   
}

