/* function: pwm
 *  
 * Practice writing functions and understanding 
 * PWM by explicitly setting output high/low
 * according to input parameters.
 * Sets pin to HIGH, delays, sets to LOW, delays.
 * 
 * pin: Pin number to execute PWM on
 * brightness: How bright the LED should be.
 *             0 is off, 255 is maximum.
 * period: period of pulse in microseconds
*/
void pwm(int pin, double brightness, double period){
  // Calculate Ton and Toff
  double Ton;  // using double precision to avoid overflow
  double Toff;
  Ton = (brightness * period) / 255;
  Toff = period - Ton;

   // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds((unsigned long)Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds((unsigned long)Toff);
}
  

void setup() {
  // put your setup code here, to run once:

  // sets pin 9 to OUTPUT
  pinMode(9, OUTPUT)
}

void loop() {
  // put your main code here, to run repeatedly:

  //set period parameter (this is 2 seconds in microseconds)
  double period = 2000000;

  //set brightness parameter and call self-made PWM function
  for (int brightness = 0; brightness <= 255; i++)
  {
    pwn(9, brightness, period / 255);
  }

}
