//Analog Sensor DISTANCE - serial print
//Lab 5

const int pin = 0;
char dist[4]; 


void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);       //baud rate
}

void loop() {
  while(Serial.available()){Serial.read();}
  while(Serial.read() !=82){
    delayMicroseconds(1000);

  }
  int nbytes = Serial.readBytes(dist,3);

    Serial.println(" ");
    //Serial.print("Distance: ");
    Serial.print(dist);
    //Serial.print(" inches");
  
}