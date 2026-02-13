const int LED=9;
const int BUTTON=2;

void setup() 
{
  // put your setup code here, to run once:
pinMode(LED, OUTPUT);
pinMode(BUTTON, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON) == LOW)
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}
