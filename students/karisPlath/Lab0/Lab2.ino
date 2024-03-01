// pins!!
const int apin=0;
const int rLED=5;
const int yLED=6;
const int cLED=8;
const int gLED=9;
const int bLED=10;

const float aref = 3.3;
const int adc_max = 1023;
const float temp_slope = 100;

int val;
float volt;
float temp;


void setup() {
  // adding serial for debug reasons...
  Serial.begin(9600);
  analogReference(EXTERNAL);

  // init pins
  pinMode(apin, INPUT);
  pinMode(rLED, OUTPUT);
  pinMode(yLED, OUTPUT);
  pinMode(cLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
}

void loop() {
  // read sensor
  val = analogRead(apin);

  // convert to voltage
  volt = val * aref / adc_max;
  // volt = map(val, fromLow, formHigh, toLow, toHigh);
  val = map(val, 0, adc_max, 0, aref);

  // convert to temperature
  temp = volt * temp_slope;

  // print to serial
  Serial.println(temp);

  // temp ranges chosen out of person preference
  if(temp <= 5){
    // tmep is out of lower bounds
    digitalWrite(bLED, HIGH);
    delay(500);
    digitalWrite(bLED, LOW);
  }
  else if(temp > 5 && temp <= 30){
    // temp is cold
    digitalWrite(bLED, HIGH);
  }
  else if(temp > 30 && temp <= 60){
    // temp is less cold
    digitalWrite(gLED, HIGH);
  }
  else if(temp > 60 && temp <= 90){
    // temp is perfect!
    digitalWrite(cLED, HIGH);
  }
  else if(temp > 90 && temp <= 110){
    // temp is heatin up
    digitalWrite(yLED, HIGH);
  }
  else if(temp > 110 && temp < 300){
    // temp is boiling
    digitalWrite(rLED, HIGH);
  }
  else if(temp >= 300){
    // temp is out of upper bounds
    digitalWrite(rLED, HIGH);
    delay(500);
    digitalWrite(rLED, LOW);
  }
}
