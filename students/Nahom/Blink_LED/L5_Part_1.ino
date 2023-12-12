int sensor = A0;
double dist;
double cm , mm;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (sensor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  dist = pulseIn(sensor,HIGH);
  mm = dist/ (147);
  cm =  mm*0.1;
  
  Serial.println(cm);

}
