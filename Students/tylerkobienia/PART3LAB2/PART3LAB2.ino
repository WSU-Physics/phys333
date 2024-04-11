
#define RED 13
#define BLUE  12
#define Temp_Sensor A0
#define MAXTEMP 75 // define the threshold temperature
#define MIN_TEMP 32 // define the range of temperature values
#define MAX_TEMP 212
#define BLINK_INTERVAL 500 // define the blink interval in milliseconds

void setup() {
  // Set the LED pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pinMode(Temp_Sensor, INPUT);  // Set the sensor pin as input
}

void loop() {
  int sensorValue = analogRead(Temp_Sensor); //read in temperature
  float voltage = sensorValue * (5.0 / 1023.0); // convert the sensor value to voltage
  float temperature = voltage * 100.0;  // convert the voltage to temperature in Fahrenheit
  if (temperature < MIN_TEMP || temperature > MAX_TEMP) {   // check if the temperature is out of range
    // do nothing when goes over range
  }
  
  
  else if (temperature >= MAXTEMP) { // check if the temperature is above the threshold
    digitalWrite(RED, HIGH);
    delay(BLINK_INTERVAL);
    digitalWrite(RED, LOW);
    delay(BLINK_INTERVAL);
    digitalWrite(BLUE, LOW);//turn off
  }
  else { // check if the temperature is below the threshold
    digitalWrite(BLUE, HIGH); //turn on 
    digitalWrite(RED, LOW); //turn off
  }
}