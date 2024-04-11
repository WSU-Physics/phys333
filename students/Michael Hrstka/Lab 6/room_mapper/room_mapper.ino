#include <SD.h>
#include <Wire.h>

const int sdPin = 10;

File logfile;

void logToSD(int distance, double angle){
  Serial.print(distance);
  Serial.print(" / ");
  Serial.print(angle);
  Serial.print("\n");
  logfile.print(distance);
  logfile.print(", ");
  logfile.print(angle);
  logfile.print(",\n");
  logfile.flush();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // SD Output
  pinMode(sdPin, OUTPUT);

  if (!SD.begin(sdPin)) {
    Serial.println("No SD card found :(");
    exit(1);
  }

  char filename[] = "scan.csv"; // Should probably use a new file later on, this is fine for now
  logfile = SD.open(filename, FILE_WRITE);
  Serial.print("Writing to file:");
  Serial.print(filename);
  Serial.println();

  if (!logfile) {
    Serial.println("Couldn't create file :(");
    exit(1);
  }

  Wire.begin();  

  logfile.print("Distance, Angle,");
  logfile.print("\n");
}

void loop() {
  delay(500);
  logToSD(0, 0);
}
