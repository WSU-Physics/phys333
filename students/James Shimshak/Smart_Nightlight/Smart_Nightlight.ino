
const int RLED=9; //Red LED on pin 9 (PWM)
const int LIGHT=0; //Lght Sensor on analog pin 0
const int MIN_LIGHT=200; //Minimum expected light value
const int MAX_LIGHT=900; //Maximum Expected Light value
int valA = 0; //variable to hold the analog reading

void setup()
{
 pinMode(RLED, OUTPUT); //Set LED pin as output
 Serial.begin(9600);
}
void loop()
{
 valA = analogRead(LIGHT); //Read the light sensor
 valA = map(valA, MIN_LIGHT, MAX_LIGHT, 255, 0); //Map the light reading
 valA = constrain(valA, 0, 255); //Constrain light value
 analogWrite(RLED, valA); //Control the LED
 Serial.println(valA);
}

//NOTE: the code does not work as intended. The sensor does convert light measured into a # 0-255 and this number does get printed. 
//      However, the sensor does change values based on brightness of the room and does not effectively change the brightness. 