// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON1_PIN PB0
#define LED1_PIN    PB1
#define BUTTON2_PIN PB2
#define LED2_PIN    PB3

#define DEBOUNCE_US 1000

// Debounce function for any button pin
uint8_t debounce(uint8_t buttonPin) {
    if (bit_is_clear(PINB, buttonPin)) {   // Button pressed (active low)
        _delay_us(DEBOUNCE_US);
        if (bit_is_clear(PINB, buttonPin)) {
            return 1;
        }
    }
    return 0;
}

int main(void) {

    // -------- Inits --------- //

    // PORTD = LED sequence output
    DDRD = 0xFF;

    // Buttons as input with pull‑ups
    DDRB &= ~(1 << BUTTON1_PIN);
    PORTB |=  (1 << BUTTON1_PIN);

    DDRB &= ~(1 << BUTTON2_PIN);
    PORTB |=  (1 << BUTTON2_PIN);

    // LEDs on PORTB as output
    DDRB |= (1 << LED1_PIN);
    DDRB |= (1 << LED2_PIN);

    PORTB &= ~(1 << LED1_PIN);
    PORTB &= ~(1 << LED2_PIN);

    uint8_t button1State = 0;
    uint8_t button2State = 0;

    // ------ Event loop ------ //
    while (1) {

        PORTD = 0b00000000;
        _delay_ms(100);

        PORTD = 0b00010000;
        _delay_ms(100);

        PORTD = 0b00110000;
        _delay_ms(100);

        PORTD = 0b01110000;
        _delay_ms(100);

        PORTD = 0b11110000;
        _delay_ms(100);

        if (debounce(BUTTON1_PIN)) {
            if (button1State == 0) {
                PORTB ^= (1 << LED1_PIN);
                button1State = 1;
            }
        } else {
            button1State = 0;
        }

        PORTD = 0b00000000;   // All LEDs off
        _delay_ms(100);

        PORTD = 0b00001000;   // Turn on LEDs from left to right
        _delay_ms(100);

        PORTD = 0b00001100;
        _delay_ms(100);

        PORTD = 0b00001110;
        _delay_ms(100);

        PORTD = 0b00001111;
        _delay_ms(100);
        
        if (debounce(BUTTON2_PIN)) {
            if (button2State == 0) {
                PORTB ^= (1 << LED2_PIN);
                button2State = 1;
            }
        } else {
            button2State = 0;
        }
    }

    return 0;
}

