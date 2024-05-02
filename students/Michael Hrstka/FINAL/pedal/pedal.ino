int guitarInput = 0;
int outputPins[5] = {9, 10, 11, 12, 13};
bool distortion = 0;
bool reverb = 0;

int distortionBtn = 2;
int reverbBtn = 3;

int previousWave = 0;
int reverbArray[300];
int reverbIndex = 0;

void setup() {
  pinMode(outputPins[0], OUTPUT);
  pinMode(outputPins[1], OUTPUT);
  pinMode(outputPins[2], OUTPUT);
  pinMode(outputPins[3], OUTPUT);
  pinMode(outputPins[4], OUTPUT);

  pinMode(distortionBtn, INPUT);
  digitalWrite(distortionBtn, HIGH);

  pinMode(reverbBtn, INPUT);
  digitalWrite(reverbBtn, HIGH);

  attachInterrupt(digitalPinToInterrupt(distortionBtn), toggleDistortion, FALLING);
  attachInterrupt(digitalPinToInterrupt(reverbBtn), toggleReverb, FALLING);

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

  /* Misguided initial attempt at adding reverb - Fixes crackling */
  newWave = (newWave + previousWave) / 2; // Average wave
  previousWave = newWave;

  if (reverb) {
    newWave = (newWave +  reverbArray[reverbIndex]) / 2;
    reverbArray[reverbIndex == 0 ? 299 : reverbIndex - 1] = newWave + reverbArray[reverbIndex] / 4;
    reverbIndex = reverbIndex >= 299 ? 0 : reverbIndex + 1;
  }

  setOutput(newWave);
}

void toggleDistortion() {
  distortion = !distortion;
}

void toggleReverb() {
  reverb = !reverb;
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
