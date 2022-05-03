// if the soil is dryer than this number, then start watering
const int dry = 450;

const int pumpPin = 12;
const int soilSensor = A4;

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(soilSensor, INPUT);
  Serial.begin(9600);
  digitalWrite(pumpPin, HIGH);
  delay(5000);
}

void loop() {
  // read current moisture
  int moisture = analogRead(soilSensor);
  Serial.println(moisture);
  
 // delay(5000);
  
  if (moisture >= dry) {
    // the soil is too dry, water!
    Serial.println("Watering starts now..moisture is " + String(moisture));
    digitalWrite(pumpPin, LOW);

    // keep watering for 5 sec
    delay(5000);

    // turn off water
    digitalWrite(pumpPin, HIGH);
    Serial.println("Done watering.");
  } else {
    Serial.println("Moisture is adequate. No watering needed " + String(moisture));
  }
}
