//Lab 1 - Part 3
const int BLED = 9;
const int GLED = 10; 
const int RLED = 11; 
const int BUTTON = 2; 

boolean lastButton = LOW; 
boolean currentButton = LOW; 
int ledMode = 0; 

void setup() {
pinMode (BLED, OUTPUT);
pinMode (GLED, OUTPUT);
pinMode (RLED, OUTPUT);
pinMode (BUTTON, INPUT); 
}

//Debouncing function
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if (last!=current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
return current; 
}

void setMode(int mode)
  {
    if(mode==1) //red
    {
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
    }
    else if (mode==2) //green
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, LOW);
    }
    else if(mode==3) //blue
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
    }
    else 
    {
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
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
