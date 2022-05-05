#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(String("Fan Status:") + String(5));
  lcd.setCursor(0, 1);
  lcd.print("Light Status:");
}
