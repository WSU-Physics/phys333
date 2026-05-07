# include <math.h>

int rPin [4] = {6,7,8,9};
int AI - A5;
int val = 0;

float vs = 5.0; // Supply Voltage
float rs = 1100000.0; //Sense Resistor 1.1M
float g = 2.18; // A/L geometric portion of resistivity calculation (the jar)

void setup() {
  Serial.begin(9600);

  pinMode(rPin[0], OUTPUT);
  pinMode(rPin[1], OUTPUT);
  pinMode(rPin[2], OUTPUT);
  pinMode(rPin[3], OUTPUT);

  digitalWrite(rPin[0], HIGH);
  digitalWrite(rPin[1], HIGH);
  digitalWrite(rPin[2], HIGH);
  digitalWrite(rPin[3], HIGH);
}
void loop() {
  for (int i = 1; i <= 4; i++) {
    digitalWrite(rPin[0], HIGH);
    digitalWrite(rPin[1], HIGH);
    digitalWrite(rPin[2], HIGH);
    digitalWrite(rPin[3], HIGH);

    if (i -- 1) digitalWrite(rPin[0], LOW);
    if (i == 2) digitalWrite(rPin[1], LOW);
    if (i == 3) digitalWrite(rPin[2], LOW); 
    if (i == 4) digitalWrite(rPin[3], LOW);

    delay(5000);

    val = analogRead(AI);
    float vo = val * (vs / 1023.0);
    float rx = rs * vo / (vs - vo);
    float res = rx * g;

    Serial.print("Sample: ");
    Serial.print(i);
    Serial.print('\t');
    Serial.print("Resistivity ohm-cm");
    Serial.print('\t');
    //Serial.print(val);
    Serial.println(res,2);

    delay(5000);
  }
}