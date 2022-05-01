#define x A3
#define y A2
uint8_t buf[8] {0};
const int z = A1;

int xvalue;
int yvalue;
int zvalue;

bool stateQ;
bool stateW;
bool stateE;
bool stateR;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {

//Serial.println("interpeted data");
  xvalue = analogRead(x);
  int vx = map(xvalue, 261, 396, -100, 100);
  float xg = (float) vx/(-100.00);
  //Serial.print(xg);
  //Serial.print("x g     ");

  yvalue = analogRead(y);
  int vy = map(yvalue, 261, 395, -100, 100);
  float yg = (float) vy/(-100.00);
 // Serial.print(yg);
  //Serial.print("yg     ");

  zvalue = analogRead(z);
  int vz = map(zvalue,272, 403, -100, 100);
  float zg = (float) vz/(-100.00);
 // Serial.print(zg);
 // Serial.print("zg     ");
 // Serial.println();

  if(yg > 0.09){
    buf[2] = 20;
    Serial.write(buf, 8);
    //Serial.println('q');
    
   // buf[2] = 20;
   // Serial.write(buf, 8);
    
    //Serial.println("Moving left");
    
  }
  else if(yg < -0.09){
    buf[2] = 26;
    Serial.write(buf, 8);
    //stateW = true;
    
    
   //Serial.println("moving right");

    
  }
  if(xg > 0.09) {
    buf[2] = 2;
    Serial.write(buf, 8);
   // Serial.println("is jumping");
  }
  if(xg < -0.09){
    buf[2] = 6;
    Serial.write(buf, 8);
    
    stateR = true;

    //Serial.println("is attacking");
  }
  else{
    onRelease();
  }


  delay(200);

  



  /*
  Serial.println("Raw Data:");
  // put your main code here, to run repeatedly:
  Serial.println(analogRead( x));
  Serial.println(analogRead( y));
  Serial.println(analogRead(z));
  delay(500);
  */
}
void onRelease(){
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}