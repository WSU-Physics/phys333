const int LED_Green=9; //Green LED on Pin 9
const int LED_Blue=10; //Blue LED on Pin 10
const int LED_Red=11; //Red LED on Pin 11
const int BUTTON=2; //The Button is connected to pin 2

boolean lastButton = LOW; //Last Button State
boolean currentButton = LOW; //Current button State
int ledMode = 0; //Cycle between LED states

void setup() {
  pinMode (LED_Green, OUTPUT);
  pinMode (LED_Blue, OUTPUT);
  pinMode (LED_Red, OUTPUT);
  pinMode (BUTTON, INPUT);
}

boolean debounce(boolean last)
{
  boolean current=digitalRead(BUTTON);
  if (last !=current)
  {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void setMode(int mode)
{
  //Blink white LED
  if (mode == 1)
  {
    digitalWrite(LED_Red, HIGH);
    digitalWrite(LED_Green, HIGH);
    digitalWrite(LED_Blue, HIGH);
    delay(1000);
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, LOW);
    delay(1000);
  }
  //PURPLE fade out
  else if (mode == 2)
  { 
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      delay(10);
    }
  }
  //RED to BLUE
  else if (mode == 3)
  {
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Red, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Red, i);
      delay(10);
    }
  }
  //EVERY COLOR RED -> BLUE -> GREEN -> PURPLE -> TEAL -> ORANGE -> WHITE -> RED..
  if (mode == 4)
  {
    for (int i=255; i > 0; i--) { 
      analogWrite(LED_Red, i);
      delay(10);
    }
    for (int i=0; i < 255; i++) { 
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=255; i > 0; i--) { 
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=0; i < 255; i++) { 
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=255; i > 0; i--) { 
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Blue, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Blue, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=0; i < 127; i++) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=127; i > 0; i--) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=0; i < 85; i++) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=85; i > 0; i--) { 
      analogWrite(LED_Red, i);
      analogWrite(LED_Blue, i);
      analogWrite(LED_Green, i);
      delay(10);
    }
    for (int i=0; i < 255; i++) { 
      analogWrite(LED_Red, i);
      delay(10);
    }
  }
  
  //OFF (mode = 0)
  else
  {
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, LOW);
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
