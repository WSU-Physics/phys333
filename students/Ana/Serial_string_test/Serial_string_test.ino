//Code adjusted from Serial.test from
//https://www.youtube.com/watch?v=Lm_xfm1d5h0

String in_bytes;
String prev_song;
const int BUTTON = 2;

boolean lastButton = LOW;
boolean currentButton = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);

}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if(last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}

void loop() {
  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    Serial.println("skip");
  }
  lastButton = currentButton;

  if(Serial.available() > 0) {  //is equal to -1 if not data I think
    in_bytes = Serial.readStringUntil('\n');  //read until new line
    // Serial.write("current song");

    if(prev_song != in_bytes){
      Serial.print(in_bytes); //this prints in visual studio terminal  
    }

    prev_song = in_bytes;
  }

}
