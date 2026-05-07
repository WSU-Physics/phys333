#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

struct Data {
  int x;
  int y;
};

Data data;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  data.x = analogRead(A1);
  data.y = analogRead(A0);

  radio.write(&data, sizeof(data));

  Serial.print("X: ");
  Serial.print(data.x);
  Serial.print("  Y: ");
  Serial.println(data.y);

  delay(20);
}