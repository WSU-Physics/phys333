void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.read() != 82){
  nbytes = (Serial.readBytes() dist , 3);
  Serial.print(dist);
  }
  
}
