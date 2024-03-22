// Turn on an LED using PWM
// Turn on another LED using our own
// PWM function

const int yLED = 9; // constant for my yellow LED
const int bLED = 8; // constant for my blue LED

/*
function: pwm

Practice writing functions and understanding
PWM by explicitly setting output high/low
according to input parameters.
Sets pin to HIGH, delays, sets to LOW, delays.

@param pin: Pin number to execute PWM on
@param brightness: How bright the LED should be.
                   0 is off, 255 is maximum.
@param period: period of pulse in microseconds
*/
void pwm(int pin, double brightness, double period) {
    // Calculate Ton and Toff
    double Ton; // using double precision to avoid overflow
    double Toff;
    Ton = (brightness * period) / 255;
    Toff = period - Ton;

    // Turn on
    digitalWrite(pin, HIGH);
    // delay for Ton
    delayMicroseconds(Ton);
    // Turn off
    digitalWrite(pin, LOW);
    // delay for Toff
    delayMicroseconds(Toff);
}

void loop() {
    // Example of setting brightness and period
    double brightness = 100;
    double period = 2040;

    // Create a ramping effect on yLED
    for (int i = 0; i <= 255; i++) {
        analogWrite(yLED, i); // Incrementally increase the brightness of yLED
        delayMicroseconds(10000); // Wait for 10000 microseconds
    }

    // Set yLED brightness to a specific value
    // analogWrite(yLED, brightness);
    // Alternatively, call self-made PWM function
    // pwm(bLED, brightness, period);
}
void setup() {
    pinMode(yLED, OUTPUT);
   // pinMode(bLED, OUTPUT);
}
