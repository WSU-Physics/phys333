//Code adjusted from Serial.test from
//https://www.youtube.com/watch?v=Lm_xfm1d5h0

String in_bytes;
String prev_song;

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);

}

void loop() {
  if(Serial.available() > 0) {  //is equal to -1 if not data I think
    in_bytes = Serial.readStringUntil('\n');  //read until new line
    // Serial.write("current song");

    if(prev_song != in_bytes){
      Serial.print(in_bytes); //this prints in visual studio terminal  
    }

    prev_song = in_bytes;
  }

}
