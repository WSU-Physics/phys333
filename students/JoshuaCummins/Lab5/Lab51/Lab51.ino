
#include <math.h>
//#define A0 SP;

void setup() {
  Serial.begin(9600);
}

int d = 0;
int dc = 0;

void loop() {
  int a = Serial.read();
  
 // if (Serial.read() >= 0) {
 //   Serial.println("reading");
 // }

  int t = Serial.read();

  if (t >= 0){
    t = ~t;
    Serial.write(t);
  }


 // if (a >= 0){
 //   for(int i = 7; i>= 0; i--){
 //     Serial.print((a >> i) & 1);
 //   }
 //   Serial.println();
 // }

  //char c = (char)a;
  //if (c == "R"){
  //  d = 0;
  //  dc = 0;
  //}

  //else if (c >= '0' && c <= '9'){
  //  d = d * 10 + (c - '0');
  //  dc++;
  //}

  //else if(c == '\r' && dc == 3){
  //  Serial.print("Dist =");
  //  Serial.print(d);
  //  Serial.print(" in");
  //}

}
