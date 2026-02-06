const int RLED = 6;
const int GLED = 5;
const int BLED = 3;


void setup() {
  pinMode(RLED,OUTPUT);
  pinMode(GLED,OUTPUT);
  pinMode(BLED,OUTPUT);
}

void loop() {
  int RB = 255;
  int GB = 35; 
  int BB = 0;
  
  analogWrite(RLED,RB);
  analogWrite(GLED,GB);
  analogWrite(BLED,BB);

}
