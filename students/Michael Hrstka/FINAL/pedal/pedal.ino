int guitarInput = 0;
int outputPins[5] = {3, 4, 5, 6, 7};

double sinWave = 0;

void setup() {
  // Serial.begin(57600);
  pinMode(outputPins[0], OUTPUT);
  pinMode(outputPins[1], OUTPUT);
  pinMode(outputPins[2], OUTPUT);
  pinMode(outputPins[3], OUTPUT);
  pinMode(outputPins[4], OUTPUT);

}

void loop() {
  int guitarVal = analogRead(guitarInput);
  // Serial.print("X:");
  // Serial.print(guitarVal);

  // Serial.print("\n");

  sinWave += 1;

  double wave = sin(sinWave);

  int newWave = (wave + 1) * 16; // Should give a value ranging from 0 to 31

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
    digitalWrite(outputPins[3], output % 2); //Serial.print(output % 2);
    output = output / 2;
    digitalWrite(outputPins[4], output % 2); //Serial.print(output % 2);
    output = output / 2;

    // Serial.print("\n");
}
