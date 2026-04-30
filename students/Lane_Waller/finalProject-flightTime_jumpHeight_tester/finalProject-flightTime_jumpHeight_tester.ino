//IR Sensor Pin declaration    //Pin 2 has hardware interrupt capability thus will use this pin for sensor reading input
const int IR_sensor = 2;       //Output of Infrared break beam laser sensor on pin 2

//Volatile variables can change inside interrupts
volatile bool jump_complete = false;         //jump recorded status variable
volatile unsigned long toeOff_time = 0;      //start time: beginning of jumo (beam goes from broken to intact)
volatile unsigned long return_time = 0;      //end time: end of sensed jump (beam returns to broken state)

void setup()
{
  Serial.begin(9600);
  pinMode(IR_sensor, INPUT_PULLUP);
  
  /*Attach interrupt setup: 
        which pin to attach the intterupt to, what ISR will be called, when will it be called*/
  attachInterrupt(digitalPinToInterrupt(IR_sensor), beamChange, CHANGE); //may need to be triggered on rising?
}

void beamChange()
{
  //ISR has been activated, read the sensor and time when beam is not broken
  if (digitalRead(IR_sensor) == HIGH) {
    toeOff_time = micros();
  }
  else {
    return_time = micros();   //record time when beam returns to broken state
    jump_complete = true;     //switch jump variable to mark a complete jump
  }
}

void loop()
{
  if(jump_complete == true){
  //output flight time reading and Jump height:
  float flightTime = (return_time - toeOff_time) / 1000000.0;          //convert microseconds to seconds
  float jumpHeight_meters = (9.80665*flightTime*flightTime) / 8.0;   //Bosco Protocol formula outputs jump height (in m)
  float jumpHeight_inches = jumpHeight_meters*39.37007874;          //meters to inches conversion
  Serial.print("Flight time: ");
  Serial.print(flightTime);
  Serial.println(" seconds");
  Serial.print("Jump height: ");
  Serial.print(jumpHeight_inches);
  Serial.println(" inches");
  jump_complete = false;                //return variable to false so another jump may be tested
  toeOff_time = 0;
  return_time = 0;
  delay(200);
  }

  else { }
}

