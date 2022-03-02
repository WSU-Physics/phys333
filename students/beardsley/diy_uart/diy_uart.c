/*
 * Just for fun, can we use simple digital io to drive
 * a UART interface?
 * Goals for this code:
 * X transmit a single character "a"
 * - Create function to transmit arbitrary byte 
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

int main(void){

  int baud = 9600;  // Slow baud rate
  int sdelay_us = 1000000 / baud;  // delay between serial bits, in microseconds

  SERIAL_DDR ^= (1 << TX);

  while (1){
    // transmit letter a = 0b01100001
    // note it should be transmitted LSB first
    clearBit(SERIAL_PORT, TX); // start bit
    _delay_us(sdelay_us);
    setBit(SERIAL_PORT, TX); // 1
    _delay_us(sdelay_us);
    clearBit(SERIAL_PORT, TX); // 0
    _delay_us(sdelay_us);
    clearBit(SERIAL_PORT, TX); // 0
    _delay_us(sdelay_us);
    clearBit(SERIAL_PORT, TX); // 0
    _delay_us(sdelay_us);
    clearBit(SERIAL_PORT, TX); // 0
    _delay_us(sdelay_us);
    setBit(SERIAL_PORT, TX); // 1
    _delay_us(sdelay_us);
    setBit(SERIAL_PORT, TX); // 1
    _delay_us(sdelay_us);
    clearBit(SERIAL_PORT, TX); // 0
    _delay_us(sdelay_us);
    setBit(SERIAL_PORT, TX); // Stop bit
    _delay_us(sdelay_us);
    
    _delay_ms(1000);  // wait a second
  }

  return (0);
}
