#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

LiquidCrystal lcd(9, 6, 5, 4, 3, 2);

float trans[2];
//float trans_1;
//int test =0;

RF24 radio(7, 8); // CE and CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

float ph;
float tc;
int tf;
/*
  struct sending{
  byte phValue;
  byte temp_c;
  byte temp_f;
  };

  sending data;
*/
void setup() {
  lcd.begin(16, 2);
  lcd.clear();



  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  Serial.println("Radio listening ");



}

void loop() {

  //ph  = data.phValue;
  //tc  = data.temp_c;
  //tf  = data.temp_f;  ;

  radio.available();
  if (radio.available()) {
    while (radio.available()) {
      radio.read(trans , sizeof(trans));
      Serial.println("Recieving data ");

      Serial.print("temp_c :"); Serial.println(trans[0]);
      Serial.print("temp_f :"); Serial.println(trans[1]);
      Serial.print("phValue:"); Serial.println(trans[2]);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("T:");
      lcd.print(trans[0]);
      lcd.print((char)223);
      lcd.print("C");
      lcd.print("/");
      lcd.print(trans[1]);
      lcd.print((char)223);
      lcd.print("F");

      lcd.setCursor(0, 1);
      lcd.print("pH: ");
      lcd.print(trans[2]);
    }
  }
  else{
    Serial.println("No radio available");
  }




  delay(500);



}
