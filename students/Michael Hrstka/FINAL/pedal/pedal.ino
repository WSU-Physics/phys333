int guitarInput = 0;
int outputPins[3] = {5, 6, 7}; // 0 being LEAST sig

double sinWave = 0;

void setup() {
  Serial.begin(9600);
  pinMode(outputPins[0], OUTPUT);
  pinMode(outputPins[1], OUTPUT);
  pinMode(outputPins[2], OUTPUT);
}

void loop() {
  int guitarVal = analogRead(guitarInput);
  // Serial.print("X:");
  // Serial.print(guitarVal);

  // Serial.print("\n");

  sinWave += 0.3;

  double wave = sin(sinWave);

  int newWave = (wave + 1) * 4; // Should give a value ranging from 0 to 7

  setOutput(newWave);

  // Serial.print("Y:");
  // Serial.print(newWave);
  // Serial.print("\n");

  // delay(500);

}

void setOutput(int output) {

    //Serial.println(output);

    // Converting to binary between the pins
    digitalWrite(outputPins[0], output % 2); //Serial.print(output % 2); // Serial outputs for testing conversion, in an awkward spot so they annoy me and I remove them later.
    output = output / 2;
    digitalWrite(outputPins[1], output % 2); //Serial.print(output % 2);
    output = output / 2;
    digitalWrite(outputPins[2], output % 2); //Serial.print(output % 2);
    output = output / 2;

    // Serial.print("\n");
}
