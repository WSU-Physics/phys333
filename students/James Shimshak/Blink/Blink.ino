

void setup() {
 // pinMode(pin, OUTPUT);


}

 // function to do manual pwm
 //inputs: pin number, how long to stay on, T_on, T_off
 //outputs: NONE
 void pwm(uint8_t pin, unsigned int T_on, unsigned int T_off){
    // turn on LED for specified time
    digitalWrite(pin, HIGH);
      delayMicroseconds(T_on);
    // turn off LED for specified time
    digitalWrite(pin, LOW);
    delayMicroseconds(T_off);
 }

void loop() {
  //analogWrite(pin, 127);

  // TODO: Call our manual pwm function
  pwm(2, 500000, 15000);
}
