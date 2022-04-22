/*
 * Use timeAudio from Williams as a starting point,
 * But extend it to play a song completely in the background.
 * 
 * I did this using timer/counter2 to count the number
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

#define SPEAKER                 PD6 /* OC0A */
#define SPEAKER_PORT            PORTD
#define SPEAKER_PIN             PIND
#define SPEAKER_DDR             DDRD

// Define song up here (tones and durations)
//       Needs to be global so interrupts can use
int notes[] = {E5, D5, C5, D5, E5, E5, E5, REST,
               D5, D5, D5, REST, E5, G5, G5, REST,
               E5, D5, C5, D5, E5, E5, E5, E5,
               D5, D5, E5, D5, C5, REST};
int lengths[] = {500, 500, 500, 500, 500, 500, 500, 500,
                 500, 500, 500, 500, 500, 500, 500, 500,
                 500, 500, 500, 500, 500, 500, 500, 500,
                 500, 500, 500, 500, 1000, 1000};
int notei=0; // Note we are currently playing
int nms=0; // Number of ms since started playing song
int nnotes = sizeof(notes) / sizeof(notes[0]);

static inline void initTimers(void) {
  TCCR0A |= (1 << WGM01);              /* CTC mode */
  TCCR0A |= (1 << COM0A0);             /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS00) | (1 << CS01); /* CPU clock / 64 */

  // Timer/Counter2. Defaults to Normal mode
  TCCR2B |= (1 << CS22); // CPU / 64. Can go up to 1024 if needed
  TIMSK2 |= (1 << TOIE2); // enable overflow interrupt
  sei();  // global interrupt enable
}

static inline void playNote(uint8_t period, uint16_t duration) {
  TCNT0 = 0;         /* reset the counter */
  OCR0A = period;    /* set pitch */

  if (period == REST){
    // Disable if rest
    SPEAKER_DDR &= ~(1 << SPEAKER);
  } else{
    // Otherwise enable
    SPEAKER_DDR |= (1 << SPEAKER);
  }
}



ISR(TIMER2_OVF_vect){
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
