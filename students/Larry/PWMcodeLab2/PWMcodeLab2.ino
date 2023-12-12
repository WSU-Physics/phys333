
const int LED=9;  // Define LED for pin 9


// synax error is was missing a ; for line 6

//inputs: 
// PWM value that corresponds to brightness
//    0 - 255 for brightness settings
// pin number
//    
// period --- at what ipoint can youre eye detect the of off and on of the LED
//    is in Microseconds

//output; what it returns?
// currently none
const int rLED = 9;

const int photo = A0;


 void PWM(double pin, double cycle, double period) {
  //calulate Ton
  //calulate Toff

  double ton;
  double toff;
  double f = 1/1000; //max value is 1000
  //double cycle;
  


  //ton = (brightness * Time) * period;
  //toff = (ton - Time);
 // cycle = (brightness * (Time/period));
  //ton = cycle * f; ---------------
  ton = cycle * period;
  toff = period - ton;
  //ton = 
  double check = ton + toff;


  

  // turn on
  digitalWrite(pin, HIGH);
  //Serial.println(ton);
  
  // delay for Ton
  delayMicroseconds(ton);
  
  //turn off
  digitalWrite(pin, LOW);
  //delay for Toff
  delayMicroseconds(toff);
  //Serial.println(toff );
 // Serial.println(" OFF TIME");

    
  
 }


//

void setup() {
  pinMode(photo, INPUT);
  pinMode(rLED, OUTPUT);
  //pinMode(bLED, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  int b = 5;
  double br = .5;
  // Nothing to loop over
  //firs part of function takes the led variable to the other a value between 0 and 256
  int period =  1000;

  //for (int i = 0; i < 100; i++){
   int val = analogRead(photo);

 // PWM(rLED, val, period);
  //Serial.println(val);
   //analogWrite(rLED, val);

 

 double voltage = val* 3/ 1023;
 //to test value
  //Serial.println(val);
    PWM(rLED, voltage, period);
  
  
  //}
  
  //analogWrite(bLED, b);
  //uses an 8 bit register to set a specfic brightness to the LED
  

  //call PMW function

  
}
