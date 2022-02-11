const int gLED = 10; 


void setup() {
  // put your setup code here, to run once:
   pinMode(gLED, OUTPUT); 
}

void pwm(int pin, double duty_cycle, double duration) {

// In seconds
  double Current_time = millis()/1000; 

  // Check if the time is less than the duration 
  if (Current_time < duration){
      //Calculate Ton
      
  double Ton; 
  //Calculate Toff
  double Toff; 

  Ton = duty_cycle * 10/100.0; 

  Toff = abs(Ton - (10/100.0)); 


 //boolean logic
 // Need to multiply seconds by 1000000
  digitalWrite(pin, duty_cycle && HIGH); 

  delayMicroseconds(Ton*1000000); 

  digitalWrite(pin, duty_cycle && LOW); 

  delayMicroseconds(Toff*1000000); 

  

  
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
  double duration = 10; 
  
  double dutycycle = .5; 

  pwm(gLED, dutycycle, duration ); 

}
