const int RLED=11;
const int GLED=10;
const int BLED=9;
const int BUTTON=2;


boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;

void setup()
{
pinMode(RLED, OUTPUT);
pinMode(GLED, OUTPUT);
pinMode(BLED, OUTPUT);
pinMode(BUTTON, INPUT);
}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last != current)
  {
    delay(10);
    current = digitalRead(BUTTON);
  }
  return current;
}

void setMode(int mode)
{
  //off
  if (mode==0)
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  //white blinks
  else if (mode==1)
  {
    digitalWrite(RLED, 255);
    digitalWrite(GLED, 255);
    digitalWrite(BLED, 255);
    delay(500);
    digitalWrite(RLED, 0);
    digitalWrite(GLED, 0);
    digitalWrite(BLED, 0);
    delay(500);
  }
  //purple fade on and off
  else if (mode==2)
  {
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) 
    {
    analogWrite(RLED, fadeValue);
    analogWrite(BLED, fadeValue);
    delay(30);
    }
    for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) 
    {
      analogWrite(RLED, fadeValue);
      analogWrite(BLED, fadeValue);
      delay(30);
    }
  }
  //fades red to blue and repeats
  else if (mode==3)
  {
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) 
    {
      analogWrite(RLED, fadeValue);
      delay(30);
    }
    for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) 
    {
      analogWrite(BLED, fadeValue);
      delay(30);
    }
  }
} 

void loop() 
{
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH)
  {
    ledMode++;
  }
  lastButton = currentButton;
  if (ledMode == 4) ledMode = 0;
  setMode(ledMode);
}
