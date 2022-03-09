const int yLED = 9; 


/*
 * Write a PWM function
 * Inputs:
 *  PWM value corresponds to brightness
 *  `o for off, 255 for brightest setting 
 *  Pin Number
 *  period
 *    In microseconds 
 *  
 *  Outputs: 
 *    none 
 */

void pwm(double pin, double brightness, double period) {
  //Calculate Ton

  int Ton; 
  int Toff; 
  
  Ton = brightness * period/255; 
  
  //Calculate Toff 

  Toff = period = Ton;
  
  // Turn on 

  digitalWrite(pin, HIGH); 

  //  delay for t on 
  delayMicroseconds(Ton); 

  // Turn off 

  DigitalWrite(pin, LOW); 
  //delay for t off 

  delayMicroseconds(Toff); 
  
  
}

void setup() {
  // put your setup code here, to run once:

  // set pin mode to output 
  pinMode(yLED, OUTPUT); 

  pinMode(bLED, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int brightness = 100; 
  int period = 2040; 

  //set yLED brightness
  analogWrite(yLED, 100);
  //call self-make
  pwm(bLED, brightness, period); 

}
