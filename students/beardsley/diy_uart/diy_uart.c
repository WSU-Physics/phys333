/*
 * Just for fun, can we use simple digital io to drive
 * a UART interface?
 * Goals for this code:
 * X transmit a single character "a"
 * X Create function to transmit arbitrary byte 
 * X Create function to transmit arbitrary message
 * - Read a byte, loopback to computer
 */

#include <avr/io.h>
#include <util/delay.h>

#define SERIAL_DDR DDRD
#define SERIAL_PORT PORTD
#define SERIAL_PIN PIND
#define TX 1
#define RX 0
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit


void transmitByte(uint8_t byte, int sdelay_us){
  uint8_t mask;
  uint8_t currState;
  clearBit(SERIAL_PORT, TX); // start bit
  _delay_us(sdelay_us);

  for (int i=0; i<8; i++){
    mask = (byte >> i);  // Shift relevant bit to LSB
    mask = (mask << TX); // Shift to TX bit
    mask &= (1 << TX);  // Set rest of bits to 0
    currState = SERIAL_PORT;
    currState = clearBit(currState, TX);
    SERIAL_PORT = currState | mask;
    _delay_us(sdelay_us);
  }

  setBit(SERIAL_PORT, TX); // Stop bit
  _delay_us(sdelay_us);
}

void transmitMessage(char message[], int sdelay_us){
    int i = 0;
    while(message[i] != '\0'){
      transmitByte(message[i++], sdelay_us);
    }
}


int main(void){

  int baud = 9600;  // Slow baud rate
  int sdelay_us = 1000000 / baud;  // delay between serial bits, in microseconds
  char message[] = "Hello World!";

  SERIAL_DDR ^= (1 << TX);

  while (1){

    transmitMessage(message, sdelay_us);    
    _delay_ms(1000);  // wait a second
  }

  return (0);
}
