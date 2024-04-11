// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <util/setbaud.h>

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

void transmitByte(uint8_t data) { /* Wait for empty transmit buffer */
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */
  return UDR0;                         /* return register value */
}

void setup(void) {
  Serial.begin(9600);
}

void loop() {
  char serialCharacter;

  initUSART();
  // Serial.println("");
  serialCharacter = receiveByte();
  // while (Serial.available()) { Serial.read(); }
  // while (Serial.read() != 82) {
  //   delayMicroseconds(1);
  // }
  // int nbytes = Serial.readBytes(dist, 3);
  if(serialCharacter = 'R'){
    Serial.print("/n");
  }else{
    Serial.print(serialCharacter);
  }
  

}
