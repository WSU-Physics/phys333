 #include<LiquidCrystal.h>

int sensorPin = A1;


LiquidCrystal lcd(12,11,5,4,3,2);



void setup(){
  analogReference(EXTERNAL);
  
  Serial.begin(9600);
  lcd.begin(16,12);
  pinMode(sensorPin,INPUT);

}

void loop (){

  int temp = analogRead(sensorPin);
  
  float to_mV= temp*(5.0/1024.0);
 
  float to_C= (to_mV - 0.5)*100;


  Serial.println(temp);
  
  lcd.setCursor(0,0);
  //lcd.print("Temp mV is = ");
  lcd.print(to_mV);
  lcd.print(" mV ");
  lcd.setCursor(0,1);
  //lcd.print("Tem in C is =");
  lcd.print(to_C);
  lcd.print(" Celsius");
  Serial.println(to_C);

  delay(1000);
}
