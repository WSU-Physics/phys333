// Distnace sensor
const int distance = 0; // Sensor on Analog Pin 0
int val = 0; // Variable to hold the analog reading from the sensor
const int LED = 3;
const int min = 0;
const int max = 255;

void setup() {
 pinMode(LED, OUTPUT);

}

//Max 
void loop() {
 val = analogRead(distance);
 long map_val = map(val, 10, 153, min, max);  //lowest value the sensor reads is 10 and the highest is 153
 analogWrite(LED, map_val);

}