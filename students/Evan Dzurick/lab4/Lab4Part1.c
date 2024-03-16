#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT        PORTB
#define LED_DDR         DDRB
#define LED1            PB0
#define LED2            PB1
#define LED3            PB2
#define LED4            PB3
#define LED5            PD4
#define LED6            PD5
#define LED7            PD6
#define LED8            PD7

#define BUTTON_PORT     PORTD
#define BUTTON_PIN      PIND
#define BUTTON_DDR      DDRD
#define BUTTON1         PD2
#define BUTTON2         PD3

#define BUTTON_HOLD_DELAY    50

void init() {
    // Set LED pins as output
    LED_DDR |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
    DDRD |= (1 << LED5) | (1 << LED6) | (1 << LED7) | (1 << LED8); 

    
    BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2));
    BUTTON_PORT |= (1 << BUTTON1) | (1 << BUTTON2);
}

int main(void) {
    init();
    uint8_t currentLED = 0;
    uint8_t currentLED2 = 4;

    while (1) {
        if ((BUTTON_PIN & (1 << BUTTON1))) { // Button1 is held
            // Sequentially turn on 4 different LEDs
            for (int i = 0; i < 4; i++) {
                // Turn off the previous LED
                LED_PORT &= ~(1 << currentLED);

                // Move to the next LED (cycling from LED0 to LED3)
                currentLED = (currentLED + 1) % 4;

                // Turn on the current LED
                LED_PORT |= (1 << currentLED);

                // Delay for some time 
                _delay_ms(200);
            }
        } else {
            // Turn off all LEDs 
            LED_PORT &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4));
        }

        if ((BUTTON_PIN & (1 << BUTTON2))) {
          
          
            for (int i = 0; i < 4; i++) {
                // Turn off the previous LED
                PORTD &= ~(1 << currentLED2);

                // Move to the next LED (cycling from LED5 to LED8)
                currentLED2 = (currentLED2 - PD4 + 1) % 4 + PD4;

                // Turn on the current LED
                PORTD |= (1 << currentLED2);

                // Delay for some time 
                _delay_ms(200);
            }
        } else {
            // Turn off all LEDs 
            PORTD &= ~((1 << LED5) | (1 << LED6) | (1 << LED7) | (1 << LED8));
        }





      

        _delay_ms(BUTTON_HOLD_DELAY);
    }

    return 0;
}