const int BLED = 9;     // Blue LED pin
const int GLED = 10;    // Green LED pin
const int RLED = 11;    // Red LED pin
const int BUTTON = 2;   // Button pin

boolean lastButton = HIGH;
boolean currentButton = HIGH;
int ledMode = 0;

//blink variables
unsigned long pastMillis = 0;
const long blinkTime = 500;  //ms
boolean ledState = false;

//fade variables
int Brightness = 0;
int Step = 5;
const unsigned long fadeTime = 20; //ms

//rainbow fade
int Color = 0;
int r = 255, g = 0, b = 0;

// Set Color Function
void setColor(int redValue, int greenValue, int blueValue);

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP); // Button pressed = LOW
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(50);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);

  // Detect button press (LOW --> HIGH transition)
  if (lastButton == HIGH && currentButton == LOW) {
    ledMode++;
    if (ledMode > 5) ledMode = 0;         //Once case 7 is done, switches back to case 0
  }

  lastButton = currentButton;

  switch (ledMode) {
    case 0: //OFF
    setColor(0, 0, 0);
    break;           
    case 1: { //White Blinking 
    unsigned long nowMillis = millis();

    if (nowMillis - pastMillis >= blinkTime) {
      pastMillis = nowMillis;
      ledState = !ledState;
    
    if (ledState) {
      setColor(255, 255, 255); //on
    } else {
      setColor(0,0,0); //off
      }
    }  
    break;
    }

    case 2: {   //fade purple
    unsigned nowMillis = millis();

    if (nowMillis - pastMillis >= fadeTime) {
      pastMillis = nowMillis;
      Brightness += Step;

     if (Brightness <= 0 || Brightness >= 255) {
       Step = -Step;
       Brightness = constrain(Brightness, 0, 255);
     }

      setColor(Brightness, 0, Brightness);
    }
    break;
    }

    case 3: { //red to blue fade
    unsigned nowMillis = millis();

    if (nowMillis - pastMillis >= fadeTime) {
      pastMillis = nowMillis;
      Brightness += Step;

      if (Brightness <= 0 || Brightness >= 255) {
        Step = -Step;
        Brightness = constrain(Brightness, 0, 255);
      }

      setColor(Brightness, 0, -Brightness);
    }
    break;
    }

    case 4: { //rainbow fade
    unsigned nowMillis = millis();

    if (nowMillis - pastMillis >= fadeTime) {
      pastMillis = nowMillis;

      if (Color >= 6) Color = 0;

      switch (Color) {
          case 0: g++; if (g >= 175) Color = 1; break;    //when g brightness is >= 255, the green brightness will increase
          case 1: r--; if (r <= 0) Color = 2; break;      // when r is greater than 0, decrease brightness of red LED
          case 2: b++; if (b >= 175) Color = 3; break;    //when b less than 255, increase brightness of blue LED
          case 3: g--; if (g <= 0) Color = 4; break;
          case 4: r++; if (r >= 175) Color = 5; break;
          case 5: b--; if (b <= 0) Color = 6; break;
        }
      
        setColor( r, g, b);
       }
        break;



      }
    }
}


void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RLED, redValue);
  analogWrite(GLED, greenValue);
  analogWrite(BLED, blueValue);
}

