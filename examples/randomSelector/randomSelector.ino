/*
  Random selector

  This fun sketch is meant to make a random selection between several choices,
  and to animate the selection with an RGB LED.
  Use the NCHOICE constant to set the number of choices (maximum 6)
    TODO: allow for a on-the-fly NCHOICE selection
  The selector will randomly show colors from the first NCHOICE options in the
  color array, and settle on one - the winner - which will then flash.
  Use the button to reset the selection.

  The circuit:
  - Use pins 9, 10, 11 for the RGB leads on a common-cathode RGB LED
  - Use resistors before each anode, and connect the cathode to ground
  - Use pin 2 for a reset button. An internal pull-up resistor is used.
*/

const int MAXCHOICE = 6;
// Number of choices - user sets this, do not exceed MAXCHOICE
const int NCHOICE = 6;

// Define pins
const int RLED = 9;
const int GLED = 10;
const int BLED = 11;
const int BUTTON = 2;

// Array to store colors
int colors[MAXCHOICE][3] = {
  // red, green, blue
  {255, 0, 0}, {0, 255, 0}, {0, 0, 255},
  // yellow, purple, white
  {255, 100, 0}, {255, 0, 255}, {255, 255, 255}
};
// Animation tuning
const int INTERVAL0 = 25;  // initial time (ms) between color flashes
const int INTERVALMAX = 1000; // final time (ms) before final selection
const int FLASH_DELAY = 500;  // Winner flashed with this interval
const float increment = 1.05;  // multiply interval by this factor to slow down
int ledState = 0;
unsigned long previousMillis = 0;

void setup() {
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  while (digitalRead(BUTTON)){
    // Wait for button to run selection
    delay(5);
  }

  // Button has been pushed - start the selection
  int interval = INTERVAL0;  // time between color flashes
  int colori = 0;  // color choice
  int prevcolori = 0;  // last color choice (avoid repeats)
  while (interval < INTERVALMAX){
    // Cycle through random colors, slowing down as we go
    colori = random(NCHOICE);
    // Don't want the same color 2x in a row.
    while (colori == prevcolori){
      colori = random(NCHOICE);
    }
    prevcolori = colori;
    analogWrite(RLED, colors[colori][0]);
    analogWrite(GLED, colors[colori][1]);
    analogWrite(BLED, colors[colori][2]);
    delay(interval);
    interval = increment * interval;
  }

  // At this point we've reached the final color.
  // Flash it until we get a button push
  while (digitalRead(BUTTON)){
    if (millis() > previousMillis + FLASH_DELAY){
      previousMillis = millis();
      ledState = !ledState;
      analogWrite(RLED, ledState * colors[colori][0]);
      analogWrite(GLED, ledState * colors[colori][1]);
      analogWrite(BLED, ledState * colors[colori][2]);
    }
  }
}
