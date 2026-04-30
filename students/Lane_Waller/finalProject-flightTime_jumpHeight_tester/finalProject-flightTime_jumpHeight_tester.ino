//Use a Hardware-Debounced Switch to Control an Interrupt

//Button pins             //Pin 2 has hardware interrupt capability thus will use this pin for sensor reading input
const int IR_sensor = 2;  //Output of Infrared break beam laser sensor on pin 2


//Volatile variables can change inside interrupts
volatile bool jump_complete = false;
volatile unsigned long toeOff_time = 0;
volatile unsigned long return_time = 0;

void setup()
{
  pinMode(IR_sensor, INPUT_PULLUP);
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(digitalPinToInterrupt(IR_sensor), beamChange, CHANGE); //which pin to attach the intterupt to, what ISR will be called, when will it be called
}

void beamChange()
{
  
  //ISR has been activated, read the sensor and time when beam is not broken
  if (digitalRead(IR_sensor) == LOW) {
    toeOff_time = micros();
  }
  else {
    return_time = micros();   //record time when beam returns to broken state
    jump_complete = true;     //switch jump variable to mark a complete jump
  }
    
}

void loop()
{
  if(jump_complete = true){
  //output flight time reading:
  unsigned long flightTime = (return_time - toeOff_time)/1000000; //convert microseconds to seconds
  Serial.print("Flight time: ");
  Serial.print(flightTime);
  Serial.println(" seconds");
  jump_complete = false;                    //return variable to false so another jump may be tested
  }

  else { }
}

