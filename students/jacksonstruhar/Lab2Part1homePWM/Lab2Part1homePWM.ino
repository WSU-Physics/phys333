const int pinOSC = 13;

void pwm(int pinOSC, double dutycycle, double duration, double period)
{
  double Ton = (dutycycle*period)/255;
  double Toff = period - Ton;

  double startTime = micros();

  while (micros() - startTime < duration)
  {
    digitalWrite(pinOSC, HIGH);
    delayMicroseconds(Ton);

    digitalWrite(pinOSC, LOW);
    delayMicroseconds(Toff);
  }
} 


void setup() 
{
  pinMode(pinOSC, OUTPUT); //pin for oscilloscope
}

void loop() 
{ 
  double period = 10000; //10ms in us
  double dutycycle = 128; //25% duty cycle from example
  double duration = 500000; //0.1s duration from example in us

  pwm(pinOSC, dutycycle, duration, period);
}
