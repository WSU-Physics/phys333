/*
This is a combination of the AM Radio project from Williams Make: AVR Programming
and my little background music sketch.

Uses three timers to:
1. Create a carrier frequency
2. Modulate the carrier with an audio frequency
3. Time note length and move to next note when ready

All these are done using timer/counters and interrupts.
*/

// ------- Preamble -------- //
#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <avr/interrupt.h>
#include "scale_16MHz.h"
#include "songs.h"

#define ANTENNA                 PD6        /* OC0A */
#define ANTENNA_PORT            PORTD
#define ANTENNA_PIN             PIND
#define ANTENNA_DDR             DDRD

#define COUNTER_VALUE   7              /* determines carrier frequency */

// From f = f_cpu / ( 2 * N * (1 + OCRnx) )
// Good values for the AM band from 5 to 15: pick one that's clear
// Divide by two b/c we're toggling on or off each loop;
//  a full cycle of the carrier takes two loops.
// 16MHz / (2 * 1 * (1+5)) = 1333 kHz
// 16MHz / (2 * 1 * (1+6)) = 1143 kHz
// 16Mhz / (2 * 1 * (1+7)) = 1000 kHz
// 16MHz / (2 * 1 * (1+8)) = 889 kHz
// 16Mhz / (2 * 1 * (1+9)) = 800 kHz
// 16Mhz / (2 * 1 * (1+11)) = 670 kHz
// 16Mhz / (2 * 1 * (1+13)) = 570 kHz
// 16Mhz / (2 * 1 * (1+15)) = 500 kHz

// Define song up here (tones and durations)
//       Needs to be global so interrupts can use
int notes[] = MARIONOTES;
int lengths[] = MARIOLENGTHS;
int notei=0; // Note we are currently playing
int nms=0; // Number of ms since started playing note
int nnotes = sizeof(notes) / sizeof(notes[0]);

static inline void initTimersInterrupts(void) {
  // Timer/Counter0 used to set the carrier frequency
  TCCR0A |= (1 << WGM01);             /* CTC mode */
  TCCR0A |= (1 << COM0A0);            /* Toggles pin each time through */
  TCCR0B |= (1 << CS00);              /* Clock at CPU frequency, ~8MHz */
  OCR0A = COUNTER_VALUE;              /* carrier frequency */

  // Timer/Counter1 used to play audio frequency
  // Use compare match interrupt to signal ISR which will toggle antenna DDR
  TCCR1B |= (1 << WGM12);             /* CTC mode */
  TCCR1B |= (1 << CS11);              /* Clock at CPU/8 */
  TIMSK1 |= (1 << OCIE1A);            /* enable output compare interrupt */

  //  Timer/Counter2 to track ms
  TCCR2B |= (1 << CS22); /* CPU clock / 64 */
  TIMSK2 |= (1 << TOIE2); // enable overflow interrupt

  sei();
}


static inline void playNote(uint16_t period) {
  // Set up the timer - real work is done in the ISR
  TCNT1 = 0;         /* reset the counter */
  OCR1AH = (period >> 8);    /* set pitch */
  OCR1AL = (period & 0xff);
}

ISR(TIMER1_COMPA_vect) {             /* ISR for audio-rate Timer 1 */
  ANTENNA_DDR ^= (1 << ANTENNA);     /* toggle carrier on and off */
}

ISR(TIMER2_OVF_vect){
  nms += 1;
  if (nms >= lengths[notei]){
    // reached end of note, update
    notei = (notei + 1) % nnotes; // Increment, start over if we reach the end
    playNote(notes[notei]);
    nms = 0;  // restart counter
  }
}

int main(void) {
  // -------- Inits --------- //
  initTimersInterrupts();

  // ------ Event loop ------ //
  while (1) {


  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}
