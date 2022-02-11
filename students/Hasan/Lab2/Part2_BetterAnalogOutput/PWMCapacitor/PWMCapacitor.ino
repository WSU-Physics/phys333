const int gLED = 10; 


void setup() {
  // put your setup code here, to run once:
   pinMode(gLED, OUTPUT); 
   Serial.begin(9600);
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

  Ton = duty_cycle * 10/1000.0; 

  Toff = abs(Ton - (10/1000.0)); 

  // Debug statements use these when necessary 
  /* 
  Serial.println("Ton is: "); 
  Serial.println( Ton, 10); 
  Serial.println("Toff is: "); 
  Serial.println(Toff,10); 
  */
  
 //boolean logic
  digitalWrite(pin, duty_cycle && HIGH); 

  delayMicroseconds(Ton*1000000); 

  digitalWrite(pin, duty_cycle && LOW); 

  delayMicroseconds(Toff*1000000); 

  

  
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
  double duration = 10000; 
  
  double dutycycle = .5; 

  pwm(gLED, dutycycle, duration ); 

 

}
