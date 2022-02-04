const int gLED = 10; 


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); 
   pinMode(gLED, OUTPUT); 

}

void pwm(int pin, double duty_cycle, double duration) {

  unsigned long On_time = 0; 
  
  while((millis() - On_time) < duration){
      //Calculate Ton

    Serial.println(millis()/1000);
    double Ton; 
    //Calculate Toff
    double Toff; 

    if(duty_cycle == 0){
      digitalWrite(pin, LOW); 
  
      delayMicroseconds(Toff*1000); 
    }
    
    else if(duty_cycle == 1){
      digitalWrite(pin, HIGH); 
  
      delayMicroseconds(Ton*1000); 
    }
    
    else{
      
    Ton = (duty_cycle * double(.01)); 


    
    Toff = abs(Ton - double(.01)); 
  
    digitalWrite(pin, HIGH); 
  
    delayMicroseconds(Ton*1000000); 

    
    
    digitalWrite(pin, LOW); 
  
    delayMicroseconds(Toff*1000000); 
     

    }
  
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
  double duration = 30; 
  
  double dutycycle = .5; 
 
  pwm(gLED, dutycycle, duration); 
  
  delay(50); 


}
