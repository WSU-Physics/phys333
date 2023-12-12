//const int read = 9;
char dis[4];
int bytes;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(0, INPUT);
  

}
//determines if there is a connection for the wire
bool WaitForWire(){
  /*
   * if wire is detect return True
   * else:
   * return false;
   */
  if(digitalRead(0)== HIGH){
    return true;
    
  }
  else {
    return false;
  }
}


void loop() {

  //char sensor = Serial.read();
 
  if(WaitForWire()){
    while(Serial.available()){
      Serial.read();
      
    }
    while(Serial.read() != 82){
      delayMicroseconds(1);
    }
    int bytes = Serial.readBytes(dis,3);
    Serial.println(dis);
  }

  // old code used to read the values from the distance sensor
  // the values it would read were rather glitchy and instead of buffering adn reading the desired value it 
  // would be all over the place when reading values it would sometimes read the inital R sending data
  /*
  //int true_val = map(sensor, 0, 1023, 0, 255);
  if (sensor == 'R'){
     Serial.read();
  char sensor2 = Serial.read();
  char sensor3 = Serial.read();
  //char sensor4 = Serial.read();
    
  
    Serial.print(sensor2);
    Serial.print(sensor3);
    //  Serial.print(sensor4);
      Serial.println();
  }
  Serial.println(sensor);
  */
  delay(1000);
  


}
