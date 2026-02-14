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
  //RED
  if (mode == 1)
  {
    digitalWrite(LED_Red, HIGH);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, LOW);
  }
  //GREEN
  else if (mode == 2)
  {
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Green, HIGH);
    digitalWrite(LED_Blue, LOW);
  }
  //BLUE
  else if (mode == 3)
  {
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, HIGH);
  }
  //PURPLE (RED+BLUE)
  if (mode == 4)
  {
    analogWrite(LED_Red, 127);
    analogWrite(LED_Green, 0);
    analogWrite(LED_Blue, 127);
  }
  //TEAL (BLUE+GREEN)
  else if (mode == 5)
  {
    analogWrite(LED_Red, 0);
    analogWrite(LED_Green, 127);
    analogWrite(LED_Blue, 127);
  }
  //ORANGE (GREEN+RED)
  else if (mode == 6)
  {
    analogWrite(LED_Red, 127);
    analogWrite(LED_Green, 127);
    analogWrite(LED_Blue, 0);
  }
  //WHITE(GREEN+RED+BLUE)
  else if (mode == 7)
  {
    analogWrite(LED_Red, 85);
    analogWrite(LED_Green, 85);
    analogWrite(LED_Blue, 85);
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
  if (ledMode == 8) ledMode = 0;
  setMode(ledMode);
}