
const unsigned long period_ms = 10000; //~10 ms period
const unsigned long Time_step_us  = 10;    //~10 us 

void pwmSoft(uint8_t pin, uint8_t dutyPercent, unsigned long duration_ms) {
  unsigned long ton = (period_ms * dutyPercent) / 100; 
  unsigned long toff = period_ms - ton; 

  unsigned long startTime = millis(); 

  while (millis() - startTime < duration_ms) {
    unsigned long cycleStart = mircos(); 

    //ON 
    digitalWrite(pin, HIGH); 
    while ( micros() - cycleStart < ton) {

    }

    //OFF 
    digitalWrite(pin, LOW); 
    while(micros() - cycleStart < period_ms) {

    }

  }
  digitalWrite(pin, LOW); 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  pwmSoft(9, 25, 5000); 
  delay(1000); 

  pwmSoft(9, 50, 5000); 
  delay(1000); 

  pwmSoft(9, 75, 5000); 
  delay(1000); 
}
