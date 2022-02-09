/*
 * Simple sketch to demonstrate reading
 * an analog sensor. Here we are using a
 * TMP36:
 * https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf
 * We would like to read the value off an
 * analog input pin, convert the value to
 * a voltage, then convert to temperature,
 * and finally send the temp value over
 * the serial port.
 */

const int apin=0;
int val=0;
// Add variables to convert to temp


void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(apin);

  // Convert binary value to voltage
  // Convert voltage to temperature
  
  // Update this to print temperature
  Serial.println(val);
  
  delay(1000);
}
