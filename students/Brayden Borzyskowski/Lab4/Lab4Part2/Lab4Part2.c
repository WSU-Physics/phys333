  #include <avr/io.h>
  #include <util/delay.h>

  #define LED_PORT        PORTB
  #define LED_DDR         DDRB

  #define LED0            PB0
  #define LED1            PB1
  #define LED2            PB2
  #define LED3            PB3
  #define LED4            PB4

  #define BUTTON_PORT     PORTD
  #define BUTTON_PIN      PIND
  #define BUTTON_DDR      DDRD
  #define BUTTON          PD0
  //#define BUTTON2         PD1
  

  #define DEBOUNCE_TIME   1000

  uint8_t debounce(void) {
      if (bit_is_clear(BUTTON_PIN, BUTTON)) {
          _delay_us(DEBOUNCE_TIME);
          if (bit_is_clear(BUTTON_PIN, BUTTON)) {
              return (1);
          }
      }
      return (0);
  }

  int main(void) {
      // -------- Inits --------- //
      uint8_t buttonWasPressed = 0;
      uint8_t currentLED = 0;  // Variable to track the current LED

      BUTTON_PORT |= (1 << BUTTON);
      LED_DDR |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);  // Set LED pins as output

      // ------ Event loop ------ //
      while (1) {
          if (debounce()) {
              if (buttonWasPressed == 0) {
                  // Turn off all LEDs
                  LED_PORT &= ~((1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4));

                  buttonWasPressed = 1;
              }
          }
          else {
              buttonWasPressed = 0;

              // Turn off the previous LED
              LED_PORT &= ~(1 << currentLED);

              // Move to the next LED (cycling from LED0 to LED4)
              currentLED = (currentLED + 1) % 5;

              // Turn on the current LED
              LED_PORT |= (1 << currentLED);

              // Delay for some time to make the LED change visible
              _delay_ms(200);

              // Reset everything when LED4 is reached
              if (currentLED == 5) {
                  currentLED = 0;
              }
          }
      }
      return(0);
  }
