const int apin = 0;
const float aref = 5.0; //test voltage output ie.. 5.13
const int adc_max = 1023;
const float temp_slope = 100;
int val = 0;
const int LED = 9;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //analogReference(EXTERNAL); - then set const float aref to 3.37 or whatever aref value 
  //is outputting when using the micrometer to measure the output voltage
 
}

void loop() {
  // put your main code here, to run repeatedly:

  // Read Sensor
  val = analogRead(apin);

  // Convert to voltage
  float voltage = val * aref / adc_max;
  //float voltage = map(val, 0, adc_max, 0, aref);
  //Serial.println(voltage);

  // Convert to temperature
  float temp = voltage * temp_slope;

  //Print to serial
  //Serial.println(temp);
  if (temp > 0 )
  {
      pinMode (LED, OUTPUT); // Set the LED pin as an output
      digitalWrite(LED, HIGH); // Set the LED pin high
  }
}