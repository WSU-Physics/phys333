//Analog Sensor DISTANCE 
//Lab 2

const int LED = 9;           //can be any color (chose white)
const int DISTANCE = 0;      //Distance sensor on Analog pin 0
//const int Close = 0;     //cm 
//const int Far = 24;        //cm


//int val = 0;             //distance variable 


void setup() {
  
  pinMode(LED, OUTPUT);     //LED set as output
  Serial.begin(9600);

}

void loop() {
  
  int val = analogRead(DISTANCE);

  float voltage = val * (3.36 / 1023.0);       //V
  float distance_cm = val * 1.30352;           //cm

  int bright = map(val, 1, 150, 0, 255);

  bright = constrain(bright, 0, 255);

  analogWrite(LED, bright);

  Serial.print("Sensor Value: ");
  Serial.print(val);
  Serial.print("      ");
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  delay(200);


}
