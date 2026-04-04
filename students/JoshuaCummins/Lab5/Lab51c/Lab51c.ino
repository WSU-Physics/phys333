#include <math.h>

void setup() {
  Serial.begin(9600);
}

int d = 0;
int dc = 0;

void loop() {
  int a = Serial.read();

  if (a >= 0) {

    char c = (char)a;

    if (c == 'R') {
      d = 0;
      dc = 0;
    }

    else if (c >= '0' && c <= '9') {
      d = d * 10 + (c - '0');
      dc++;
    }

    else if (c == '\r' && dc == 3) {
      Serial.print("Dist = ");
      Serial.print(d);
      Serial.println(" in");
    }
  }
}