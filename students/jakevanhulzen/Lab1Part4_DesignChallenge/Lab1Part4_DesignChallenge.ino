const int BLED=9;
const int GLED=10;
const int RLED=11;
const int BUTTON=2;

boolean lastButton = LOW;
boolean currentButton=LOW;
int ledMode = 0;
unsigned long previousMillis = 0;
const long interval = 100;

void setup() {
  // put your setup code here, to run once:
pinMode (BLED, OUTPUT); //Set Blue LED as Output
pinMode (GLED, OUTPUT); //Set Green LED as Output
pinMode (RLED, OUTPUT); //Set Red LED as Output
pinMode (BUTTON, INPUT); //Set button as input
}

boolean debounce(boolean last)
{
 boolean current = digitalRead(BUTTON); //Read the button state
 if (last != current) 
 {
 delay(5); //wait 5ms
 current = digitalRead(BUTTON); 
 }
 return current; 
}

void setMode(int mode)
{
//OFF
 if (mode == 0){
 digitalWrite(RLED, LOW);
 digitalWrite(GLED, LOW);
 digitalWrite(BLED, LOW);
 }

 //WHITE BLINKING (GREEN and RED and BLUE)
 else if (mode == 1)
 {
 analogWrite(RLED, 85);
 analogWrite(GLED, 85);
 analogWrite(BLED, 85);
 delay(1000);                      // wait for a second
 analogWrite(RLED, LOW);
 analogWrite(GLED, LOW);
 analogWrite(BLED, LOW);
 delay(1000);                      // wait for a second
 }
 //Purple light, fades between bright -> dim -> bright, repeat
else if (mode == 2)
{
for (int i = 0; i <= 255; i += 5) {
  analogWrite(RLED, i);
  analogWrite(GLED, 0);
  analogWrite(BLED, i);
  delay(20);
    }
for (int i = 255; i >= 0; i -= 5) {
  analogWrite(RLED, i);
  analogWrite(GLED, 0);
  analogWrite(BLED, i);
  delay(20);
    }
  }
else if (mode == 3) {
    // Red to Blue fading, repeat
    for (int i = 0; i <= 255; i += 5) {
      analogWrite(RLED, i);
      analogWrite(GLED, 0);
      analogWrite(BLED, 255 - i);
      delay(20);
    }
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(RLED, i);
      analogWrite(GLED, 0);
      analogWrite(BLED, 255 - i);
      delay(20);
    }
  } else if (mode == 4) {
    // Party Mode - Flashes different colors
    for (int i = 0; i < 5; i++) {
      digitalWrite(RLED, HIGH);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      delay(100);
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, LOW);
      delay(100);
      digitalWrite(RLED, LOW);
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, HIGH);
      delay(100);
    }
  }
}



void loop() {
  currentButton = debounce(lastButton); // Read debounced state
  if (lastButton == LOW && currentButton == HIGH) {
    ledMode++; // Increment the LED value
  
  
  }
  lastButton = currentButton; // Reset button value

  // Check if it's time to update the LED
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the LED was updated
    previousMillis = currentMillis;

if (ledMode == 5) ledMode = 0;
    setMode(ledMode);
  }
}
