const int gLED = 10;
const int rLED = 9;
const int sonarSensor = 0;

//need some sort of distance or bound for sensor to detect
//lower bound means the object is closer
//upper bound means the object is farther
const int lowerBound = 15; //cm
const int upperBound = 65; //cm

int val = 0;

void setup() 
{
  pinMode(gLED, OUTPUT);
  pinMode(rLED, OUTPUT);
}

void loop() 
{
  val = analogRead(sonarSensor);
  
  if (val <= lowerBound)
  {
    digitalWrite(gLED, LOW);
    digitalWrite(rLED, HIGH);
  }
  else if (val >= upperBound)
  {
    digitalWrite(gLED, HIGH);
    digitalWrite(rLED, LOW);
  } 
}
