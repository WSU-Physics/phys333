
const int sensor = 8;

void setup() {
  pinMode(sensor, OUTPUT);

}

void loop() {
  
  double Rm = x;
  double Rfsr = y;
  double voltage = z;

  sensor = (Rm * voltage) / (Rm + Rfsr);

}
