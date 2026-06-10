#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define SDL 10 // SD
char dist[4]; 
int distance= 0;

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
File logfile;

void setup(){
  Serial.begin(9600); //Match for all sensors and logger
  pinMode(10,OUTPUT);

  if(! lis.begin(0x18)){
    while(1);
  }

  if(! SD.begin(SDL)){
    while(1);
  }

  logfile = SD.open("demsa.csv",FILE_WRITE);
  logfile.println("Dist,Theta,X,Y");
}

void loop(){
  //The main concern addressed by the snippet in the lab6 sheet is to correct inproper inputs from the dist sensor. Comes in not like R123.
  while(Serial.available()){Serial.read();}
  while(Serial.read() != 'R'){ // Using char's instead of ASCII directly 
  delayMicroseconds(1);
  } 

  int nbytes = Serial.readBytes(dist,3);
  if(nbytes == 3){
    dist[3] = '\0';
  
    if(isdigit(dist[0]) && isdigit(dist[1]) && isdigit(dist[2])){ //Verifies that isn't a char like R (incorrect parsing from device)
    distance = atoi(dist); //Converts char to int. GPT'd for format/representation ^same up here^
    }
  }

  sensors_event_t event;
  lis.getEvent(&event);

  float AccelX = event.acceleration.x;
  float AccelY = event.acceleration.y;
  float AccelZ = event.acceleration.z;
  float theta_x = atan2(AccelX, AccelZ);
  float theta_y = atan2(AccelY, AccelZ);
  float theta = sqrt(theta_x * theta_x + theta_y * theta_y);

  static int last = 0;
  
  //Cardiasian
  float X = distance * cos(theta);
  float Y = distance * sin(theta);

  

  if(distance >= 6 && distance <= 240){
    if(abs(distance-last) < 20){ //Spike no no
      last = distance;

      logfile.print(distance);
      logfile.print(",");
      logfile.print(theta * 180 / 3.14);
      logfile.print(",");
      logfile.print(X);
      logfile.print(",");
      logfile.println(Y);
      logfile.flush();
    }
  }
  delay(100);
}