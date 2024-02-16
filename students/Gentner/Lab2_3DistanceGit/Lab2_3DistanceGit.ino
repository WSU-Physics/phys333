// v/in 
// needs a V reading then that will be converted to distance
// Error response of too close if distance is under 6in 
// If V=<.25v then print Too Close Back Up
int Vin;
int distanceReading;
int Reading;
int Sensor = 0; // distance sensor is on pin A0
unsigned long distance;

void setup() {
  Serial.begin(9600); //sends info through serial
  Serial.print("Hello");
}

void loop() {
Reading= analogRead(Sensor);
Vin=map(distanceReading, 0, 1023, 0, 5000); // converts analog into V
Serial.print("Vin : ");
Serial.print(Reading );

if(Vin<30)
{
  Serial.println(" Too Close");
}
else
{
distance = Vin * 9.8;
Serial.print("Distance : ");
Serial.println(distance);
}
delay(500);
}
