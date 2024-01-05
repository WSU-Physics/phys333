/*
 * Test the precision of different variable types.
 * Prints value of i, then increases by one.
 * We can determine the maximum value by seeing
 * when it overflows to a negative number.
*/
int i_now;
int i_last;

void setup() {
  Serial.begin(9600);
  i_now = 31000;
}

void loop() {
  
  i_last = i_now;
  i_now++;  // Increment i
  Serial.println(i_now);
  if (i_now < i_last){
    Serial.print("The highest value is ");
    Serial.println(i_last);
    Serial.print("The lowest value is ");
    Serial.println(i_now);
  }
}
