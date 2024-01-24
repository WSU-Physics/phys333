int pin = 3;
int man_pin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  pinMode(man_pin, OUTPUT);
}

// function to do manual pwm
// inputs: pin number, Ton, Toff
// outputs: none
void pwm(uint8_t pin, unsigned int Ton, unsigned int Toff){
  // turn on LED for spcified time
  digitalWrite(pin, HIGH);
  delayMicroseconds(Ton);
  // turn off LED for specified time
  digitalWrite(pin, LOW);
  delayMicroseconds(Toff);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(pin, 127);

  // TODO: call our manual pwm function
  pwm(man_pin, 500, 1500);
}
