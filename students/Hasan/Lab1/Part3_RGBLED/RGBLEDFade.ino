const int BLED=10; // Blue LED Cathode on Pin 9
const int GLED=9; // Green LED Cathode on Pin 10
const int RLED=8; // Red LED Cathode on Pin 11

void setup()
{
 pinMode (BLED, OUTPUT); // Set Blue LED as Output
 pinMode (GLED, OUTPUT); // Set Green LED as Output
 pinMode (RLED, OUTPUT); // Set Red LED as Output
}

void loop()
{

  
  for (int i=0; i<256; i++)
 {
 analogWrite(BLED, i);
 delay(1);
 }
 for (int i=255; i>=0; i--)
 {
 analogWrite(BLED, i);
 delay(1);
 }

 for (int i=0; i<256; i++){
 analogWrite(GLED, i);
 delay(1);
 }
 
 for (int i=255; i>=0; i--)
 {
 analogWrite(GLED, i);
 delay(1);
 }
for (int i=0; i<256; i++){
 analogWrite(RLED, i);
 delay(1);
 }
 for (int i=255; i>=0; i--)
 {
 analogWrite(RLED, i);
 delay(1);
 }
}
