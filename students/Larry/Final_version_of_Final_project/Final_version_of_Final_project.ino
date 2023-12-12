/*
 * this is the final version of the Final project
 * 
 */







#define x A3
#define y A2
//unsigned 8 bit value that buffers the value for the keyboard input
uint8_t buf[8] {0};
// I did not change this match the x adn y values because it was not used nor needed
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

//finds the x values of when the sensor is titled in the x value direction
// it takes the give values of device when its tilted as far as it can on the x axis
  xvalue = analogRead(x);
  int vx = map(xvalue, 261, 396, -100, 100);
  // convert the int value given into a degree value
  float xg = (float) vx/(-100.00);
  //Serial.print(xg);
  //Serial.print("x g     ");
  
//finds the y value of when the sensor is tilted
// it takes the give values of device when its tilted as far as it can on the x axis
  yvalue = analogRead(y);
  int vy = map(yvalue, 261, 395, -100, 100);
  //converts the int value into a float number to a decimal degree value
  float yg = (float) vy/(-100.00);


// reads the z value however this section of code is not used
//in the final project
  zvalue = analogRead(z);
  int vz = map(zvalue,272, 403, -100, 100);
  float zg = (float) vz/(-100.00);

// the 9 value is take in consideration for errors in values and for values that may spike higher or smaller than they should
  if(yg > 0.09){
    //corresponds to the left moving keycode
    buf[2] = 20;
    Serial.write(buf, 8);
    //Serial.println('q');
    
   // buf[2] = 20;
   // Serial.write(buf, 8);
    
    Serial.println("Moving left");
    
  }
  else if(yg < -0.09){
    //corresponds to the right moving keycode
    buf[2] = 26;
    Serial.write(buf, 8);
    //stateW = true;
    
    
   Serial.println("moving right");

    
  }
  if(xg > 0.09) {
    //correspodns to space bar
    buf[2] = 8;
    Serial.write(buf, 8);
    Serial.println("is jumping");
  }
  if(xg < -0.09){
    //corresponds to the z letter key
    buf[2] = 21;
    Serial.write(buf, 8);
    
    //stateR = true;

    Serial.println("is attacking");
  }
  else{
    //release the key
    // this function of the program is called when the device is laying completely flat
    onRelease();
  }

// a delay may be needed in case it's too fast
 // delay(200);

  


// this was  test function that first viewed the raw data from the sensor
  /*
  Serial.println("Raw Data:");
  // put your main code here, to run repeatedly:
  Serial.println(analogRead( x));
  Serial.println(analogRead( y));
  Serial.println(analogRead(z));
  delay(500);
  */
}
/*
 * this function is used to clear the buffer value that holds the key value
 * the serial. write updates these values to the give value of 0;
 */
void onRelease(){
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}
