/*
Plays a simple tune, broadcasts it in the AM radio band.

Based on amRadio from Williams AVR book, 
https://github.com/hexagon5un/AVR-Programming/tree/master/Chapter09_Introduction-to-Timer-Counter-Hardware/amRadio
with slight modifications to work directly on Arduino Uno board.
*/

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include <avr/interrupt.h>
#include "scale16.h"

#define ANTENNA                 PD5        /* OC0B */
#define ANTENNA_PORT            PORTD
#define ANTENNA_PIN             PIND
#define ANTENNA_DDR             DDRD

#define COUNTER_VALUE   7              /* determines carrier frequency */

// From f = f_cpu / ( 2* N* (1 + OCRnx) )
// Good values for the AM band from 5 to 15: pick one that's clear
// Divide by two b/c we're toggling on or off each loop;
//  a full cycle of the carrier takes two loops.
// 16MHz / (2 * 1 * (1+5)) = 1333 kHz
// 16Mhz / (2 * 1 * (1+7)) = 1000 kHz
// 16Mhz / (2 * 1 * (1+9)) = 800 kHz
// 16Mhz / (2 * 1 * (1+11)) = 670 kHz
// 16Mhz / (2 * 1 * (1+13)) = 570 kHz
// 16Mhz / (2 * 1 * (1+15)) = 500 kHz

static inline void initTimer0(void) {
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0B0);            /* Toggles pin each time through */
  TCCR0B |= (1 << CS00);              /* Clock at CPU frequency, ~8MHz */
  OCR0A = COUNTER_VALUE;                          /* carrier frequency */
}

static inline void initTimer1(void) {
  TCCR1B |= (1 << WGM12);                                  /* CTC mode */
  // Cannot scale to 1 MHz as in example. Need to adjust pitches in scale.h
  TCCR1B |= (1 << CS11);            /* Clock at CPU/8 frequency, ~2MHz */
  TIMSK1 |= (1 << OCIE1A);          /* enable output compare interrupt */
}

static inline void initTimer2(void) {
    // User Timer/Counter0 to track ms
  TCCR2B |= (1 << CS22); /* CPU clock / 64 */
  TIMSK2 |= (1 << TOIE2); // enable overflow interrupt
}

ISR(TIMER1_COMPA_vect) {                 /* ISR for audio-rate Timer 1 */
  ANTENNA_DDR ^= (1 << ANTENNA);          /* toggle carrier on and off */
}

static inline void transmitBeep(uint16_t pitch, uint16_t duration) {
  OCR1A = pitch;                               /* set pitch for timer1 */
  sei();                                         /* turn on interrupts */
  do {
    _delay_ms(1);                            /* delay for pitch cycles */
    duration--;
  } while (duration > 0);
  cli();                  /* and disable ISR so that it stops toggling */
  ANTENNA_DDR |= (1 << ANTENNA);               /* back on full carrier */
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT2 = 0;         /* reset the counter */
  OCR1A = period;    /* set pitch */

  if (period == REST){
    // Disable if rest
    SPEAKER_DDR &= ~(1 << SPEAKER);
  } else{
    // Otherwise enable
    SPEAKER_DDR |= (1 << SPEAKER);
  }
}

int main(void) {
  // -------- Inits --------- //

  initTimer0();
  initTimer1();
  initTimer2();

  // ------ Event loop ------ //
  while (1) {

    // 1/8 -> 150
    transmitBeep(E3, 100);
    _delay_ms(50);
    transmitBeep(E3, 100);
    _delay_ms(200);
    transmitBeep(E3, 100);
    _delay_ms(200);
    transmitBeep(C3, 100);
    _delay_ms(50);
    transmitBeep(E3, 100);
    _delay_ms(200);
    transmitBeep(G3, 200);
    _delay_ms(400);
    transmitBeep(G2, 300);
    _delay_ms(300);

    transmitBeep(C3, 300);
    _delay_ms(150);
    transmitBeep(G2, 300);
    _delay_ms(150);
    transmitBeep(E2, 300);
    _delay_ms(150);
    transmitBeep(A2, 300);
    transmitBeep(B2, 300);
    transmitBeep(Ax2, 150);
    transmitBeep(A2, 200);
    _delay_ms(100);

    transmitBeep(G2, 150);
    _delay_ms(50);
    transmitBeep(E3, 150);
    _delay_ms(50);
    transmitBeep(G3, 150);
    _delay_ms(50);
    transmitBeep(A3, 200);
    _delay_ms(100);
    transmitBeep(F3, 100);
    _delay_ms(50);
    transmitBeep(G3, 100);
    _delay_ms(200);
    transmitBeep(E3, 200);
    _delay_ms(100);
    transmitBeep(C3, 100);
    _delay_ms(50);
    transmitBeep(D3, 100);
    _delay_ms(50);
    transmitBeep(B2, 200);
    _delay_ms(450);
    
    
    
    
    
    // transmitBeep(G3, 200);
    // _delay_ms(200);
    
    
    

    _delay_ms(1500);

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
