const int gLED = 10; 


void setup() {
  // put your setup code here, to run once:
   pinMode(gLED, OUTPUT); 
}

void pwm(int pin, double duty_cycle, double duration) {

  double Current_time = millis()/1000; 
  
  if (Current_time < duration){
      //Calculate Ton
  int Ton; 
  //Calculate Toff
  int Toff; 

  Ton = duty_cycle * .01; 

  Toff = abs(Ton - .01); 


  digitalWrite(pin, HIGH); 

  delayMicroseconds(Ton); 

  digitalWrite(pin, LOW); 

  delayMicroseconds(Toff); 

  

  
}
}

void loop() {
  // put your main code here, to run repeatedly:
  
  double duration = 1; 
  
  double dutycycle = 0; 
 
  pwm(gLED, dutycycle, duration ); 

}
