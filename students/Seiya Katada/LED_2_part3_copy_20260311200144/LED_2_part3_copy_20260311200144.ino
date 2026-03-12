const int InputLED = 2;
const int pwmLED = 6;
const int GreenLED = 9;
const int RedLED = 10;
const int BlueLED = 11;
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
  pinMode(InputLED, INPUT);

  pinMode(pwmLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);  
  // set LED pin to output
  
}

void loop() {
  double dutycycle = 0.9;
  pwm(pwmLED, dutycycle, 0.5);

  unsigned long Ton = pulseIn(InputLED, HIGH);
  unsigned long Toff  = pulseIn(InputLED, LOW);
  
  if(dutycycle <= 0.33){
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    digitalWrite(BlueLED, LOW);
  }

  else if(dutycycle <= 0.66){
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
    digitalWrite(BlueLED, LOW);
  }

  else{
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, LOW);
    digitalWrite(BlueLED, HIGH);
  }
  
}
