//instantiate variable for PWM Pin 
const int pwmPin = 10; 

//set up period variable
double period = 10/1000.0;

void setup() {
  // put your setup code here, to run once:

  //Sets the pwmPin to output mode
   pinMode(pwmPin, OUTPUT); 

   //Uncomment Below line if using debug statements 
   //Serial.begin(9600);
}

void pwm(int pin, double duty_cycle, double duration) {

// Current time is in seconds and double 
  double Current_time = millis()/1000.0; 

  Serial.println(Current_time); 

  // Check if the time is less than the duration for each loop 
  while ((millis()/1000.0 - Current_time) < duration){
      //Calculate Ton

  //Calculate Ton and Toff 
  double Ton; 
  
  double Toff; 
  
  Ton = duty_cycle * period; 

  Toff = abs(Ton - period); 

  // Debug statements use these when necessary 
  /* 
  Serial.println("Ton is: "); 
  Serial.println( Ton, 10); 
  Serial.println("Toff is: "); 
  Serial.println(Toff,10); 
  */
  
 //boolean logic: Courtesy of professor beardsley, if duty cycle is 0, will not activate digitalWrite 
  digitalWrite(pin, duty_cycle && HIGH); 

  delayMicroseconds(Ton*1000000); 

  digitalWrite(pin, duty_cycle && LOW); 

  delayMicroseconds(Toff*1000000); 
  
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  // choose value that creates sawtooth waveform with 2 second period
  double duration = .005;

  // Loop through duty cycles at the resolution rate found average resolution section 
 for(double dutycycle = 0; dutycycle <=1; dutycycle+=.0025){ 
   
  pwm(pwmPin, dutycycle, duration);
 }
   

 

}
