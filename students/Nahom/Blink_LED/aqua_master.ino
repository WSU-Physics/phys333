#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>
#include <nRF24L01.h>
#include <RF24.h>

const int chipSelect = 4;  // for SD

int card = 0;
File dataFile;

float temp_c;
float temp_f;

float trans[2];
/*
  struct sending{
  byte phValue;
  byte temp_c;
  byte temp_f;
  };

  sending data;
*/
#define SensorPin 0          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10], temp;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//--------------------------------------radio------------------
RF24 radio(7, 8); // CE and CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;
//-------------------------------------------temp data wire----------------
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


void setup() {
  Serial.begin(9600);

  //-----------------------------------------radio-----------------------------

  radio.begin();
  radio.openWritingPipe(pipe);
  radio.stopListening();
  //radio.setAutoAck(false);
  //radio.setDataRate(RF24_250KBPS);
  //radio.setPALevel(RF24_PA_LOW);


  //---------------------------------------------------------------LCD / pH/ Temp-------------------------
  lcd.begin();
  lcd.backlight();
  sensors.begin();

  Serial.println("Ready");    //Test the serial monitor
  // ---------------------------------------------------------------end Setup---------------------

  // --------------------------------------------SD setup----------------------------------------

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  String header = "pH , Temp_C , Temp_F ";


  dataFile = SD.open("aquaData.txt", FILE_WRITE); //--------------create file --------------
  if (dataFile) {
    Serial.println("--aqua_data-- File created");
    dataFile.println("pH , Temp_C , Temp_F ");
    dataFile.close();
  }


  //----------------------------------------------------------------end of SD-----------------------------
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";


  //-----------------------------------------------------------PH--------------------
  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(SensorPin);
    delay(10);
  }
  for (int i = 0; i < 9; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0;
  for (int i = 2; i < 8; i++)               //take the average value of 6 center sample
    avgValue += buf[i];
  float phValue = (float)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  phValue = 3.5 * phValue;                  //convert the millivolt into pH value

  //dataString += String(phValue);  //----------------ph data to SD--------

  //------------------------------------------------------------------temp-------------------------
  sensors.requestTemperatures();
  temp_c = sensors.getTempCByIndex(0);
  temp_f = DallasTemperature::toFahrenheit(temp_c);

  // dataString += String(temp_c); // ---------------temp data to SD--------
  // dataString += String(temp_f);
  //------------------------------------------------------------LCD------------------------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp_c);
  lcd.print((char)223);
  lcd.print("C");
  lcd.print("/");
  lcd.print(temp_f);
  lcd.print("F");

  lcd.setCursor(0, 1);
  lcd.print("pH: ");
  lcd.print(phValue);

  Serial.print("pH: ");
  Serial.print("  Temp in C:");
  Serial.println("  Temp in F:");
  Serial.print(phValue, 2);
  Serial.print(" , ");
  Serial.print(temp_c);
  Serial.print(" , ");
  Serial.println(temp_f);


  //-----------------------------------------------------SD----------------------------------
  dataFile = SD.open("aquaData.txt", FILE_WRITE);
  String header = "pH , Temp_C , Temp_F ";

  //dataString += (String(temp_c) + "," + String(phValue));
  //collected += String(phValue) ;

  if (dataFile) {
    //dataFile.print(dataString);
    Serial.println("Printing on file");

    dataFile.print((long)phValue);
    dataFile.print(" ,  ");
    dataFile.print((long)temp_c);
    dataFile.print("    ,  ");
    dataFile.println((long)temp_f);

    dataFile.close();

  }


  trans[0]=temp_c;
  trans[1]=temp_f;
  trans[2]=phValue;
  radio.write(&trans,sizeof(trans));
  //Serial.println("Sending data");

  if (!radio.write(&trans,sizeof(trans))) {
    Serial.println("packet delivery failed");
  }


  delay(500);


}
