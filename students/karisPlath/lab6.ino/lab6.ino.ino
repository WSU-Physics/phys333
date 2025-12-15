// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <util/setbaud.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

char serialCharacter;

// the logging file
File myFile;
const int chipSelect = 10;

 void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);
}

void initUSART(void) {                                /* requires BAUD */
  UBRR0H = UBRRH_VALUE;                        /* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= (1 << U2X0);
#else
  UCSR0A &= ~(1 << U2X0);
#endif
                                  /* Enable USART transmitter/receiver */
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
}
 
uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);       /* Wait for incoming data */
  return UDR0;                                /* return register value */
}


 
void setup(void) {
  Serial.begin(9600);


  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop() {
  char serialCharacter;
 
  initUSART();

    // serialCharacter = receiveByte();
    
    //   if(serialCharacter == 'R'){
    //     Serial.print("\n");
    //   }else{
        
    //       logfile.print("serialCharacter");           // milliseconds since start
    //       logfile.print(", ");        
    //    }
  
    
  }
