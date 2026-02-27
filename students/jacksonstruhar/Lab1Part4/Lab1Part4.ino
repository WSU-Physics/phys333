const int RLED=11;
const int GLED=10;
const int BLED=9;
const int BUTTON=2;
int ledState = LOW;


boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;
unsigned long previousMillis = 0;
const long Whiteinterval = 500;
const long Purpleinterval = 50;
const long Redinterval = 100;
int fadeValue = 0;
int fadeIncrement = 5;
int TacoBell = 0;

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
    unsigned long currentMillis = millis();

    if ((currentMillis - previousMillis) > Whiteinterval) 
      {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(RLED, ledState);
        digitalWrite(GLED, ledState);
        digitalWrite(BLED, ledState);
      }
  }
  //purple fade on and off
  else if (mode == 2)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= Purpleinterval)
    {
      previousMillis = currentMillis;

      fadeValue += fadeIncrement;

      if (fadeValue <= 0 || fadeValue >= 255)
      {
        fadeIncrement = -fadeIncrement; 
      }

      analogWrite(RLED, fadeValue);
      analogWrite(GLED, 0);
      analogWrite(BLED, fadeValue);
    }
  }

  //fades red to blue and repeats
  else if (mode == 3)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= Redinterval)
      {
      previousMillis = currentMillis;

      fadeValue += fadeIncrement;

      if (fadeValue <= 0 || fadeValue >= 255)
      {
        fadeIncrement = -fadeIncrement;
      }

      analogWrite(RLED, fadeValue);
      analogWrite(GLED, 0);
      analogWrite(BLED, 255 - fadeValue);
      }
  }

  //code taco bell
  else if (mode == 4)
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis > Whiteinterval) //uses same interval as the white blink state
    {
      previousMillis = currentMillis;
      ledState = !ledState;
    
      //uses different color states from the taco bell logo
      if (ledState == HIGH)
      {
        if (TacoBell == 0)
        {
          analogWrite(RLED, 185);   // purple and blue
          analogWrite(GLED, 0);
          analogWrite(BLED, 255);
        }
        else if (TacoBell == 1)
          {
            analogWrite(RLED, 255);  // pink
            analogWrite(GLED, 0);
            analogWrite(BLED, 125);
          }
          else if (TacoBell == 2)
          {
            analogWrite(RLED, 139);  // yellow
            analogWrite(GLED, 128);
            analogWrite(BLED, 0);
          }
          else if (TacoBell == 3)
          {
            analogWrite(RLED, 255); //white
            analogWrite(GLED, 255);
            analogWrite(BLED, 255);
          }

          TacoBell++;
          if (TacoBell > 3) TacoBell = 0;
      }
      else
      {
        analogWrite(RLED, 0);
        analogWrite(GLED, 0);
        analogWrite(BLED, 0);
      }
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
  if (ledMode == 5) ledMode = 0;
  setMode(ledMode);  
}
