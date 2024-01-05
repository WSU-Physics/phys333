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
float voltage;
float temp;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL); // Use 3.3V connected to AREF
}

void loop() {
  val = analogRead(apin);

  // Convert binary value to voltage
  voltage = val * 3.36 / 1023;  // 3.36 V per 1023 binary values
  // Convert voltage to temperature
  // scale factor of 10 mV / deg celsius
  // 750 mV at 25 deg celsius
  temp = 0.1 * voltage * 1000 - 50;
  temp = temp * 9 / 5 + 32;
  
  // Update this to print temperature
  Serial.print("Temp (F)");
  Serial.print('\t');
  Serial.println(temp);
  
  delay(1000);
}
