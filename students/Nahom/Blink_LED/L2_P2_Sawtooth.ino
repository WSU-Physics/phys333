
const int LED = 5;


void pulse( int pin, double duty, double duration) {

  double   period = 10000.0;
  float brightness;
  double Ton = (duty * period);
  double Toff = ((Ton - Ton * duty) / duty);



  for (int t = 0 ; t < duration ; t += period) {
    // Turn on
    digitalWrite(pin, HIGH);
    // delay for Ton
    delayMicroseconds(Ton);
    // Turn off
    digitalWrite(pin, LOW);
    // delay for Toff
    delayMicroseconds(Toff);
    
   }
   
}



void setup() {
  // put your setup code here, to run once:

  pinMode(LED , OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

 
  //double duty = 0.2;
  double duration = 1000;

  for (float i =0; i<=1; i=i+0.005){
  
  pulse(LED, i, duration);
  
  }
  
}
