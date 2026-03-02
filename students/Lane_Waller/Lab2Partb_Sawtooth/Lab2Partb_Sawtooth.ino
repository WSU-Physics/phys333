const int pin = 3;
unsigned long startMillis;
unsigned long duration = 100;
long Ton; 
long Toff;
int step = 0;
void pwm(int pin, double dutyCycle){
  // Calculate Ton and Toff
   // using double precision to avoid overflow
  
  double period = 10;
  Ton = ((dutyCycle * period) * 100) + 0.5;
  //Serial.print(Ton);
  Toff = (((1-dutyCycle) * period) * 100) + 0.5;
  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds(10 * Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds(10 * Toff);
  
}

void setup() {
  // set blue LED pin to output
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  //startMillis = millis();

}

void loop() {

    // save the last time you blinked the LED
  for (step = 0; step < 10; step ++){
    
    unsigned long startMillis = millis();

    while (millis() - startMillis < duration/ 10) {
    
      pwm(pin, step/10.0);

    }
    //currentMillis = millis();
  }
        
    //Serial.println(Ton);
    //Serial.println(Toff);
 
    //delay(1000);
}

