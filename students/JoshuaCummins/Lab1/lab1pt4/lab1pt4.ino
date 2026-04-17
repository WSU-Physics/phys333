const int BLED=9;      
const int GLED=10;     
const int RLED=11;     
const int BUTTON=2;

int mode = 1;
bool btn1 = HIGH;

void setup() {
  pinMode (BLED, OUTPUT);   
  pinMode (GLED, OUTPUT);   
  pinMode (RLED, OUTPUT);   
  pinMode (BUTTON, INPUT_PULLUP);  
}


void loop() {
  setmode();
  Smode();

}


void setmode(){
  bool btn = digitalRead(BUTTON);

  if(btn =! btn1){
    mode = mode + 1;
    btn1 = btn;
     if(mode == 6)
    {
    mode == 0;
    }
  }
  delay(20);

}

void Smode(){
  
  if(mode == 1){
    analogWrite(RLED,0);
    analogWrite(GLED, 0);
    analogWrite(BLED,0);
  }
  else if(mode == 2){
    analogWrite(RLED,255);
    analogWrite(GLED,255);
    analogWrite(BLED,255);
    delay(1000);
    analogWrite(RLED,255);
    analogWrite(GLED,255);
    analogWrite(BLED,255);
    delay(1000);
  }
  else if (mode == 3){
    int i = 0;
    analogWrite(RLED,i);
    analogWrite(GLED,0);
    analogWrite(BLED,i);
    
    i+=i;

    if(i == 255)
    {
      i = -1;
    }
    if(i == 0){
      i = 1;
    }

    
  }
  else if(mode == 4){
    int i = 0;
    analogWrite(RLED,255 - i);
    analogWrite(GLED,0);
    analogWrite(BLED,i);
    i += i;

    if (i == 255){
      i = -1;
    }
    if (i == 0){
      i = 1;
    }
  }
  else if(mode == 5){
    for(int i = 0; i < 3; i++){
      if(i == 0){
        analogWrite(RLED,255);
        analogWrite(GLED,0);
        analogWrite(BLED,0);
      }
      if(i == 1){
        analogWrite(RLED,0);
        analogWrite(GLED,255);
        analogWrite(BLED,0);
      }
      if(i == 2){
        analogWrite(RLED,0);
        analogWrite(GLED,0);
        analogWrite(BLED,255);
      }
      delay(1000);
    }
  }

}