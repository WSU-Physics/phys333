// #include <RTClib.h>


//Hook Arduino RX up to sensor TX and unhook to upload
char dist[4];

void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT);

}

void loop() {
 
  while(Serial.available()) {
    Serial.read();
  }
  while(Serial.read() != 82) {
    delayMicroseconds(1);
  }
  int nbytes = Serial.readBytes(dist, 3);
  Serial.println(dist);

}
