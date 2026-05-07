//Code from: https://www.youtube.com/watch?v=Lm_xfm1d5h0
//Adjusted line 19

String InBytes;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  if(Serial.available() > 0) {
    InBytes = Serial.readStringUntil('\n');
    if(InBytes == "on") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.write("LED on");
    }
    else if(InBytes == "off") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("LED off");
    } 
    else {
      Serial.write("invalid input");
    }
  }


}
