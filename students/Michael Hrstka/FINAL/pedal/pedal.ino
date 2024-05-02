int guitarInput = 0;
int outputPins[5] = {9, 10, 11, 12, 13};
bool distortion = 0;

int distortionBtn = 2;
int chorusBtn = 3;

double sinWave = 0;

void setup() {
  // Serial.begin(57600);
  pinMode(outputPins[0], OUTPUT);
  pinMode(outputPins[1], OUTPUT);
  pinMode(outputPins[2], OUTPUT);
  pinMode(outputPins[3], OUTPUT);
  pinMode(outputPins[4], OUTPUT);

  pinMode(distortionBtn, INPUT);
  digitalWrite(distortionBtn, HIGH);

  attachInterrupt(digitalPinToInterrupt(distortionBtn), toggleDistortion, FALLING);

}

void loop() {
  double guitarVal = analogRead(guitarInput);
  // sinWave += .1;

  // double wave = sin(sinWave);

  if (distortion) {
    guitarVal *= 5;
  }

  double wave = guitarVal * 2 / 1023.0;

  int newWave = wave * 16;
  if (newWave > 31) {
    newWave = 31;
  }

  // Serial.print("X:");
  // Serial.print(wave);
  // Serial.print("\n");

  setOutput(newWave);

  // Serial.print("Y:");
  // Serial.print(newWave);
  // Serial.print("\n");

  // delay(500);

}

void toggleDistortion(){
  distortion = !distortion;
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
