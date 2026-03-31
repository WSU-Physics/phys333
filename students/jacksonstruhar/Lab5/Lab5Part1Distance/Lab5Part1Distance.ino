const int pinRX = 0;

void setup() {
  pinMode(pinRX, INPUT);
  Serial.begin(9600);   //9600 baud
}

void loop() {
  if (Serial.available()) {   
    char distance = Serial.read(); 
    Serial.print("Distance: "); 
    Serial.print(distance);
    Serial.println("inches");
  }
}
