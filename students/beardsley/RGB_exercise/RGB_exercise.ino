const int GLED = 10;  // Green LED pin
const int BUTTON = 2;  // Button pin
boolean lastButton = LOW;
boolean currentButton = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(GLED, OUTPUT);
  Serial.begin(9600);
  }

boolean debounce(boolean last){
  boolean current = digitalRead(BUTTON);
  if (last != current){
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  // Check for button press
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH){
    Serial.println("Button pushed!");
  }
  lastButton = currentButton;
  
  digitalWrite(GLED, HIGH);
  delay(1000);
  digitalWrite(GLED, LOW);
  delay(1000);

}
