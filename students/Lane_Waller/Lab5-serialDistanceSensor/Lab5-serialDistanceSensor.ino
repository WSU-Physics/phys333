void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);     //initiate the serial monitor with the proper baud 
}

void loop() {
  // put your main code here, to run repeatedly:
  char distance[3];
  if(Serial.read() == 82) {
    Serial.readBytes(distance, 3);
    Serial.println(distance);
    _delay_ms(1000);
  }
}
