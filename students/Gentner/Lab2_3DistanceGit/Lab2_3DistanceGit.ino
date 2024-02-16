// v/in 
// needs a V reading then that will be converted to distance
// Error response of too close if distance is under 6in 
// If V=<.25v then print Too Close Back Up
double Vin;
int distanceReading;
int Reading;
int Sensor = 0; // distance sensor is on pin A0
double distance;
double Feet;

void setup() {
  Serial.begin(9600); //sends info through serial
  Serial.print("Hello");
}

void loop() {
Reading= analogRead(Sensor);
Vin=map(Reading, 0, 1023, 0, 5000); // converts analog into V
Serial.print("Vin : ");
Serial.print(Vin );

if(Vin<60)
{
  Serial.println(" Too Close");
}
else
{
distance = Vin / 9.8;
Serial.print("  Distance : ");
Serial.print(distance);
Feet = distance / 12;
Serial.print("  In Feet : ");
Serial.println(Feet);
}
delay(1000);
}
