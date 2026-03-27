#include <avr/io.h>
#include <util/delay.h>

void turnSignal(uint8_t side) {
    for (uint8_t i = 1; i <= 4; i++) {
        if (side == 0) {
            PORTD = ((1 << i) - 1) << (4 - i); // LEFT
        } else {
            PORTD = ((1 << i) - 1) << 4;       // RIGHT
        }
        _delay_ms(200);
    }
}

int main(void) {
    DDRD = 0xff;   // set LEDs as output

    while (1) {
        turnSignal(0);   
        _delay_ms(500);

        turnSignal(1);  
        _delay_ms(500);
    }

    return 0;
}