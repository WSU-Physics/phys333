
const uint8_t PWM_pin = 9; 

const unsigned long PWM_period_us = 1000; 
const unsigned long SAW_period_ms = 2000; 
const int steps = 100; 

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_pin, OUTPUT); 
}

void pwmSoft(uint8_t pin, uint8_t duty, unsigned long duration_ms) {
  unsigned long ton = (PWM_period_us * duty) / steps; 
  unsigned long startTime = millis(); 

  while(millis() - startTime < duration_ms) {
    unsigned long t0 = micros(); 

    digitalWrite(pin, HIGH); 
    while(micros() - t0 < ton) {}

    digitalWrite(pin, LOW); 
    while(micros() - t0 < PWM_period_us) {}
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  unsigned long stepTime = SAW_period_ms / steps; 

  for (int duty = 0; duty <= 100; duty++) {
    pwmSoft(PWM_pin, duty, stepTime); 
  }
}
