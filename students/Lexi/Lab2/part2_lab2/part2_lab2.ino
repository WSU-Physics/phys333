
const uint8_t PWM_pin = 9; 

const unsigned long PWM_period_us = 10000; 
const unsigned long SAW_period_ms = 2000; 
const int steps = 1000; 
const unsigned long Step_time_ms = SAW_period_ms / steps; 

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_pin, OUTPUT); 
}

void pwmFixed (int duty) {
  unsigned long t0 = micros(); 

  unsigned long ton = (PWM_period_us * duty) / steps; 

  if(ton>0) {
    digitalWrite(PWM_pin, HIGH); 
    while(micros() - t0 < ton) {}
  }

  digitalWrite(PWM_pin, LOW); 
  while(micros() - t0<PWM_period_us){}
}
void loop() {
  // put your main code here, to run repeatedly:
  for (int duty = 0; duty <= steps; duty++) {
    unsigned long stepTime = millis(); 

    while (millis() - stepTime < Step_time_ms) {
      pwmFixed(duty); 
    }
  }
}
