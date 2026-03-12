const int LED = 6;
double Ton; 
double Toff;
void pwm(int pin, double dutycycle, double duration){
  int period = 10;
  Ton = ((dutycycle*period)*100)+0.5; 
  Toff = (((1-dutycycle)*period)*100)+0.5;

  // Turn on
  digitalWrite(pin, HIGH);
  // delay for Ton
  delayMicroseconds(10*Ton);
  // Turn off
  digitalWrite(pin, LOW);
  // delay for Toff
  delayMicroseconds(10*Toff);
}

void setup() {
  pinMode(LED, OUTPUT);
  // set LED pin to output
  Serial.begin(9600);
  
}

void loop() {

unsigned long start = millis();
  while(millis() - start <= 0.5) {
    pwm(6, 0.5, 0.5);
  
  }
  start = 0;
  Serial.println(Ton);
}
