/*
 * Compare digital and analog reads
 * Questions to answer:
 *   - At what voltage does digital transition LOW to HIGH?
 *   - What values do we expect from analogRead()?
 *   - How long do digitalRead() and analogRead() take?
 */

const int dPin=13;  // Digital input pin
const int aPin=0;  // Analog input pin
int dval = 0;  // Digital value
int aval = 0;  // Analog value
unsigned long starttime;
unsigned long dtime;
unsigned long atime;

void setup() {
  pinMode(dPin, INPUT);
  Serial.begin(9600);
  Serial.println("D. Val\tA. Val\tD. Time\tA. Time");
}

void loop() {
  // Read digital value, and time how long it takes
  starttime = micros();
  dval = digitalRead(dPin);
  dtime = micros() - starttime;

  // Read analog value, and time how long it takes
  starttime = micros();
  aval = analogRead(aPin);
  atime = micros() - starttime;

  // Print the results
  Serial.print(dval);
  Serial.print("\t");
  Serial.print(aval);
  Serial.print("\t");
  Serial.print(dtime);
  Serial.print("\t");
  Serial.println(atime);

  // Delay so the display doesn't run super fast
  delay(1000);
  
}
