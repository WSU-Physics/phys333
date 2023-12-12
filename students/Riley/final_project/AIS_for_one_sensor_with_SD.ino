#include <SPI.h>
#include <SD.h>

int IN1 = 2; //D2
int Pin1 = A0; // sensor Aout to Analog 0
const int dry = 570; //value of the sensor completely dry
const int wet = 244; //value of the sensor submerged in water
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
   Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  pinMode(IN1, OUTPUT);
  
  pinMode(Pin1, INPUT);
  
  digitalWrite(IN1, HIGH);
  delay(500);
}
void loop() {
  float value1 = analogRead(Pin1); //moisture reading from sensor
  float value2 = map(value1, wet, dry, 100, 0); //value2 is the percentage humidity;

  if(value1>454)//same as if the humidity percentage( value2) < 30% then water the plant
  //if(value2<30)
  {
      digitalWrite(IN1, LOW);
      delay(1000);
      digitalWrite(IN1, HIGH);
  }
  else
  {
    digitalWrite(IN1, HIGH);
    }
        delay(30000);
  
   String dataString = "";
    dataString += String("SD MOISTURE LEVEL: ");
    dataString += String(value1);
    
    dataString += String("\nPercentage Humidity: ");
    dataString += String(value2);
    dataString += String("%");
     delay(2000);
 
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
      
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
