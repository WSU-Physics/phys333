const int BLED=10; //Blue LED on pin 10
const int RLED=9; //Red LED on pin 9
const int TEMP=0; //Temp Sensor is on pin A0
int val = 0; //Variable to hold analog reading
void setup()
{
  pinMode (BLED, OUTPUT); //Set Blue LED as Output
  pinMode (RLED, OUTPUT); //Set Red LED as Output
  Serial.begin(9600);

}
void loop()
{
  val = analogRead(TEMP);
 
if (val<165){         //if val is < 165 it increases brightess as it decreases 
 int brightnessblue = map(val, 145, 165, 200, 0);
  analogWrite(BLED, brightnessblue);
  analogWrite(RLED, 0);
}

else{         //if val is > 165 it increases brightess as it increases 
 int brightnessred = map(val, 165, 180, 0, 200);
 analogWrite(RLED, brightnessred);
 analogWrite(BLED, 0);
}

 
 Serial.println(val);
 
}
