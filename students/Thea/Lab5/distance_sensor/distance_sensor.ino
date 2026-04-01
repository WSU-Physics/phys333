//Analog Sensor DISTANCE - serial print
//Lab 5

const int pin = 0;
char dist; 


void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);       //baud rate
}

void loop() {
  if (Serial.available()){
    dist = Serial.read();
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.print("inches");
  }
}