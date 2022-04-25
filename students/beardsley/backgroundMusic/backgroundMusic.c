/*
 * Use timeAudio from Williams as a starting point,
 * But extend it to play a song completely in the background.
 * 
 * I did this using timer/counter0 to count the number
 * of ms since the note started. I interrupt on an overflow,
 * and increment the ms count. Once the time reaches the
 * note length, the next note is played.
 * 
 * I use the same trick as millis() to approximate the
 * 8-bit timer overflow as 1ms (except I don't do any
 * corrections because it's close enough for me).
 */

// ------- Preamble -------- //
#include <avr/io.h>         /* Defines pins, ports, etc */
#include "scale_16MHz.h"    /* Map notes to number of clock cycles */
#include <avr/interrupt.h>
#include "songs.h"

#define SPEAKER                 PB3 /* OC2A */
#define SPEAKER_PORT            PORTB
#define SPEAKER_PIN             PINB
#define SPEAKER_DDR             DDRB

// Define song up here (tones and durations)
//       Needs to be global so interrupts can use
int notes[] = MARIONOTES;
int lengths[] = MARIOLENGTHS;
int notei=0; // Note we are currently playing
int nms=0; // Number of ms since started playing note
int nnotes = sizeof(notes) / sizeof(notes[0]);

static inline void initTimers(void) {
  // User Timer/Counter0 to track ms
  TCCR0B |= (1 << CS00) | (1 << CS01); /* CPU clock / 64 */
  TIMSK0 |= (1 << TOIE0); // enable overflow interrupt
  sei();  // global interrupt enable

  // Timer/Counter2 has larger range for prescalar,
  // so it can handle wider range of pitches
  TCCR2A |= (1 << WGM21);   /* CTC mode */
  TCCR2A |= (1 << COM2A0);  /* Toggles pin each cycle through */
  TCCR2B |= (1 << CS22) | (1 << CS20);    /* CPU / 128. */
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT2 = 0;         /* reset the counter */
  OCR2A = period;    /* set pitch */

  if (period == REST){
    // Disable if rest
    SPEAKER_DDR &= ~(1 << SPEAKER);
  } else{
    // Otherwise enable
    SPEAKER_DDR |= (1 << SPEAKER);
  }
}



ISR(TIMER0_OVF_vect){
  nms += 1;
  if (nms >= lengths[notei]){
    // Reached end of note, update
    notei = (notei + 1) % nnotes; // Increment, start over if we reach the end
    playNote(notes[notei], lengths[notei]);
    nms = 0;  // restart counter
  }
}

int main(void) {
  initTimers();

  while (1){
    // Here is where we do stuff.
  }
}
