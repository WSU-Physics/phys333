int guitarInput = 0;
int outputPins[3] = {0, 1, 2}; // 0 being LEAST sig

int outputTEST = 0;

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

  // Serial.print("Y:");
  // Serial.print(sineWave);

  // Serial.print("\n");

  delay(1000);

  setOutput(outputTEST);
  outputTEST = outputTEST < 7 ? outputTEST + 1 : outputTEST = 0;

}

void setOutput(int output) {

    Serial.println(output);

    // Converting to binary between the pins
    digitalWrite(outputPins[0], output % 2); Serial.print(output % 2); // Serial outputs for testing conversion, in an awkward spot so they annoy me and I remove them later.
    output = output / 2;
    digitalWrite(outputPins[1], output % 2); Serial.print(output % 2);
    output = output / 2;
    digitalWrite(outputPins[2], output % 2); Serial.print(output % 2);
    output = output / 2;

    Serial.print("\n");
}
