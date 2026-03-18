const int pinOSC = 13;

void pwm(int pinOSC, double dutycycle, double duration, double pwmPeriod)
{
  double Ton  = (dutycycle * pwmPeriod) / 255.0;
  double Toff = pwmPeriod - Ton;
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
  pinMode(pinOSC, OUTPUT);
}

void loop()
{
  double duration = 500000; //0.5s duration
  double pwmPeriod = 10000;     // 10 ms PWM period (us)
  double sawPeriod = 100000;   // 2 s sawtooth period (us)

  int steps = sawPeriod / pwmPeriod;  // 200 steps
  double dutyStep = 255.0 / steps;

  for (int i = 0; i < steps; i++)
  {
    double dutycycle = i * dutyStep;

    pwm(pinOSC, dutycycle, pwmPeriod, pwmPeriod); //pwm function
  }
}
