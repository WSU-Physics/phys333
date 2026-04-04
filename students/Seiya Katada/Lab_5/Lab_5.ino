#include <RTClib.h>

char dist[4];  //

void setup() {
  Serial.begin(9600);
}

void loop() {

  while (Serial.available()) Serial.read();

  while (Serial.read() != 'R');

  Serial.readBytes(dist, 3);
  dist[3] = '\0'; 

  Serial.print("Distance: ");
  Serial.println(dist);
}