// ------- Preamble -------- //

#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "USART.h"
#include "RTClib.h"

#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

#define LOG_INTERVAL  1000 
#define SYNC_INTERVAL 1000 
#define ECHO_TO_SERIAL   1 
#define WAIT_TO_START    0 

File logfile;
RTC_DS1307 RTC;
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

const int chipSelect = 10;
uint32_t syncTime = 0; 

void initUSART(void) {  /* requires BAUD */
  UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
  /* Enable USART transmitter/receiver */
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void transmitByte(uint8_t data) {
                                     /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;                                            /* send data */
  logfile.write(data);
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);       /* Wait for incoming data */
  return UDR0;                                /* return register value */
}

void error(char *str) {
  Serial.print("error: ");
  Serial.println(str);
  while(1);
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  Serial.println();

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }

  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  char filename[] = "RoomPlotterLogger.CSV";
  if (! SD.exists(filename)) {
    logfile = SD.open(filename, FILE_WRITE);
  }

  if (! logfile) {
    error("couldnt create file");
  }

  switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: break;
    case LIS3DH_DATARATE_10_HZ: break;
    case LIS3DH_DATARATE_25_HZ: break;
    case LIS3DH_DATARATE_50_HZ: break;
    case LIS3DH_DATARATE_100_HZ: break;
    case LIS3DH_DATARATE_200_HZ: break;
    case LIS3DH_DATARATE_400_HZ: break;
    case LIS3DH_DATARATE_POWERDOWN: break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: break;
  }
  
  Wire.begin();
   if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  //ECHO_TO_SERIAL
  }

  logfile.println("millis,stamp,datetime,light,temp,vcc");    
#if ECHO_TO_SERIAL
  Serial.println("millis,stamp,datetime,light,temp,vcc");
#endif //ECHO_TO_SERIAL
}

void loop() {
  char serialCharacter;
  lis.read();
  DateTime now;
  initUSART();
  sensors_event_t event;
  lis.getEvent(&event);
  // delay for the amount of time we want between readings
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

  // log milliseconds since starting
  uint32_t m = millis();
  logfile.print(m);           // milliseconds since start
  logfile.print(", ");    
#if ECHO_TO_SERIAL
  Serial.print(m);         // milliseconds since start
  Serial.print(", ");  
#endif

  now = RTC.now();
  logfile.print(now.unixtime()); // seconds since 1/1/1970
  logfile.print(", ");
  logfile.print('"');
  logfile.print(now.year(), DEC);
  logfile.print("/");
  logfile.print(now.month(), DEC);
  logfile.print("/");
  logfile.print(now.day(), DEC);
  logfile.print(" ");
  logfile.print(now.hour(), DEC);
  logfile.print(":");
  logfile.print(now.minute(), DEC);
  logfile.print(":");
  logfile.print(now.second(), DEC);
  logfile.print('"');




  logfile.print(", ");    
  logfile.print("HALLO :D");
  logfile.print(", ");    
  logfile.print(event.acceleration.z);

  logfile.println();

  if ((millis() - syncTime) < SYNC_INTERVAL) return;
  syncTime = millis();
}
  // serialCharacter = receiveByte();
  // Serial.print("\n");
  // while(serialCharacter != 82){
  //   transmitByte(serialCharacter);
  //   serialCharacter = receiveByte();
  // }
  // double angle = event.acceleration.z;
  // logfile.print(serialCharacter);
  // logfile.print('"');
  // logfile.print(angle);
  // logfile.println();