const int apin=0;
int val=0;
float voltage;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL); // Use 3.3V connected to AREF
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void setLights(int a, int b, int c, int d, int e, int f, int g, int h){
  digitalWrite(0, a);
  digitalWrite(1, b);
  digitalWrite(2, c);
  digitalWrite(3, d);
  digitalWrite(4, e);
  digitalWrite(5, f);
  digitalWrite(6, g);
  digitalWrite(7, h);
}

void loop() {
  val = analogRead(apin);

  // Convert binary value to voltage
  voltage = val * 3.36 / 1023;  // 3.36 V per 1023 binary values

  Serial.print("V:");
  Serial.println(voltage);

  if(voltage > 1.5)
    setLights(1, 0, 0, 0, 0, 0, 0, 0);
  if(voltage > 1.725)
    setLights(1, 1, 0, 0, 0, 0, 0, 0);
  if(voltage > 1.95)
    setLights(1, 1, 1, 0, 0, 0, 0, 0);
  if(voltage > 2.175)
    setLights(1, 1, 1, 1, 0, 0, 0, 0);
  if(voltage > 2.4)
    setLights(1, 1, 1, 1, 1, 0, 0, 0);
  if(voltage > 2.625)
    setLights(1, 1, 1, 1, 1, 1, 0, 0);
  if(voltage > 2.85)
    setLights(1, 1, 1, 1, 1, 1, 1, 0);
  if(voltage > 3.075)
    setLights(1, 1, 1, 1, 1, 1, 1, 1);

  delay(1);
}


