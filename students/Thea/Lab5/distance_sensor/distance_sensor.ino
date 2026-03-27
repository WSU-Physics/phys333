//Analog Sensor DISTANCE - serial print
//Lab 5

char data;
int dist;

//int val = 0;             //distance variable 


void setup() {
  Serial.begin(9600);       //baud rate
}

void loop() {
  if (Serial.available()){
    data = Serial.read();
    
    
  }


}