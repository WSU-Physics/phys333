int pin = 9;
int man_pin = 2;
void setup() {
  // put your setup code here, to run once:
pinMode(pin, OUTPUT);
pinMode (man_pin, OUTPUT);
}

// function to do manual pwm
// inputs: pin number, T_on, T_off 
// outputs: none  
void pwm(uint8_t pin, unsigned int Ton, unsigned int Toff){
// turn on LED for specified time 
digitalWrite(pin, HIGH);
delayMicroseconds(Ton);
// turn off LED for specified time 
digitalWrite(pin, LOW);
delayMicroseconds(Toff);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(pin,255);

// TODO: call our manual pwm function 
pwm(man_pin,50000,150000);
}
