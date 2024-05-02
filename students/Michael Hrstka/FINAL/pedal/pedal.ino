int guitarInput = 0;
int outputPins[5] = {9, 10, 11, 12, 13};
bool distortion = 0;
bool chorus = 1;

int distortionBtn = 2;
int chorusBtn = 3;

int previousWave = 0;
int chorusArray[300];
int chorusIndex = 0;
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

  pinMode(chorusBtn, INPUT);
  digitalWrite(chorusBtn, HIGH);

  attachInterrupt(digitalPinToInterrupt(distortionBtn), toggleDistortion, FALLING);
  attachInterrupt(digitalPinToInterrupt(chorusBtn), toggleChorus, FALLING);

}

void loop() {
  double guitarVal = analogRead(guitarInput);

  if (distortion) {
    guitarVal *= 5;
  }

  double wave = guitarVal * 2 / 1023.0;

  int newWave = wave * 16;
  if (newWave > 31) {
    newWave = 31;
  }

  /* Misguided attempt at adding reverb */
  newWave = (newWave + previousWave) / 2; // Average wave
  previousWave = newWave;

  if (chorus) {
    chorusArray[chorusIndex == 0 ? 299 : chorusIndex - 1] = newWave;
    newWave = (newWave +  chorusArray[chorusIndex]) / 2;
    chorusIndex = chorusIndex >= 299 ? 0 : chorusIndex + 1;
  }

  setOutput(newWave);
}

void toggleDistortion() {
  distortion = !distortion;
}

void toggleChorus() {
  chorus = !chorus;
}

void setOutput(int output) {
    // Converting to binary between the pins
    digitalWrite(outputPins[0], output % 2);
    output = output / 2;
    digitalWrite(outputPins[1], output % 2);
    output = output / 2;
    digitalWrite(outputPins[2], output % 2);
    output = output / 2;
    digitalWrite(outputPins[3], output % 2);
    output = output / 2;
    digitalWrite(outputPins[4], output % 2);
    output = output / 2;
}
