// ------- Preamble -------- //

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include <time.h>
#include <stdio.h>
#include <unistd.h>


//Pin Defines
#define LED_PORT                PORTD
#define LED_PIN                 PIND
#define LED_DDR                 DDRD
#define LED0                    PD0 //R
#define LED1                    PD1 //G
#define LED2                    PD2 //B
#define LED3                    PD3 //W
#define LED4                    PD4 //W
#define LED5                    PD5 //B
#define LED6                    PD6 //G
#define LED7                    PD7 //R
//Buttons
#define BUTTON_PORT             PORTB
#define BUTTON_PIN              PINB
#define BUTTON_DDR              DDRB
#define BUTTON                  PB0
// Potentially useful macros
#define BV(bit)               (1 << (bit))  // Mask with single bit set
#define setBit(byte, bit)     (byte |= BV(bit))  // set bit within byte
#define clearBit(byte, bit)   (byte &= ~BV(bit)) // clear bit
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

int main(void){
DDRD =0b11111111; //all output



while(1){
  int sleep_seconds = 5;
  sleep(sleep_seconds);

  PORTD = 0b000001000;
sleep(150);
  PORTD = 0b0001100;
sleep(150);
  PORTD = 0b00001110;
sleep(150);
  PORTD = 0b00001111;
sleep(150);
  PORTD = 0b00000000;
sleep(150);
}
return(0);

}