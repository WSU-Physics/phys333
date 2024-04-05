// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT                PORTB
#define LED_DDR                 DDRB
#define R_LEDS                 PB0    //Digital Pin 8
#define G_LED1                 PD1    //Digital Pin 9
#define G_LED2                 PD2    //Digital Pin 10
#define G_LED3                 PD3    //Digital Pin 11
#define G_LED4                 PD4    //Digital Pin 12
#define MOTOR                  PD4    //Digital Pin 13

#define BUTTON_PORT             PORTD
#define BUTTON_PIN              PIND
#define BUTTON_DDR              DDRD
#define BUTTON1                 PD1    //Digital Pin 1
#define BUTTON2                 PB2    //Digital Pin 2
#define BUTTON3                 PD3    //Digital Pin 3
#define BUTTON4                 PB4    //Digital Pin 4
#define BUTTON5                 PD5    //Digital Pin 5
#define BUTTON6                 PB6    //Digital Pin 6
#define BUTTON7                 PD7    //Digital Pin 7

// ------- Macros ------- //
#define BV(bit)               (1 << (bit))       // Mask with single bit set
#define toggleBit(byte, bit)  (byte ^= BV(bit))  // toggle bit

// ------- Functions ------- //
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * This function initializes the interupts for digital pins 8 through 13 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void initInterupt0(void) {
  PCICR |= (1 << PCIE0);
  for(int i = 0; i <= 6; i++){
    PCMSK0 |= (1 << i);
  }
  PCMSK0 |= (1 << i);
  sei();
}


