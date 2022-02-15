/*
 * Have fun with this RGB LED nightlight!
 */

const int RLED=11;  //red LED cathode set to pin 11
const int GLED=10;  //green LED cathode set to pin 10
const int BLED=9;   //blue LED cathode set to pin 9
const int BTN=2;    //button is connected to pin 2

boolean lBtn = LOW; //last button state
boolean cBtn = LOW; //current button state
int ledMode = 0;    //cycle between LED states

/*unsigned long t0 = 0;
unsigned long t = millis();*/

void setup()
{
  pinMode (RLED, OUTPUT); //red LED designated output
  pinMode (GLED, OUTPUT); //green LED designated output
  pinMode (BLED, OUTPUT); //blue LED designated output
  pinMode (BTN, INPUT);   //button designated input
}

/*
 * Debounce Function
 * pass it previous button state
 * retrieve current debounced state
 */
 boolean debounce(boolean last)
 {
  boolean current = digitalRead(BTN); //read the button state
  if (last != current)                //if different
  {
    delay(5);                         //wait 5ms
    current = digitalRead(BTN);       //read button again
  }
  return current;                     //return the current value
 }

 /*
  * LED Mode Selection
  * pass a number for the LED state and set it
  * due to RGB LED being COMMON CATHODE
  * pin must be set to HIGH for a color to turn ON
  */
  void setMode(int mode)
  {
    //BLINKING WHITE
    if (mode == 1)
    {
      digitalWrite(RLED, HIGH); //turn on
      digitalWrite(GLED, HIGH);
      digitalWrite(BLED, HIGH);
      /*while (t < t0 + 1000)
      {
        checkbtn(t0, t);
      }*/
      delay(1000);
      digitalWrite(RLED, LOW);  //turn off
      digitalWrite(GLED, LOW);
      digitalWrite(BLED, LOW);
      delay(1000);
      }
   
  
    //PURPLE HAZE
    else if (mode == 2)
    {
      for (int i=0; i<256; i++)   //starting from i=0 increase i by 1 as long as the value is under 256
      {
        analogWrite(RLED, i);     //red+blue have the value i while green is kept off
        analogWrite(GLED, LOW);
        analogWrite(BLED, i);
        delay(15);                //delay 10 ms
      }
      for (int i=255; i>=0; i--)  //when i=255, start decreasing i by 1 until i=0, then i will start increasing again
      {
        analogWrite(RLED, i);
        analogWrite(GLED, LOW);
        analogWrite(BLED, i);
        delay(15);
      }
    }
    //RED TO BLUE AND BACK AGAIN
    else if (mode == 3)
    {
      for (int r=255; r>=0; r--)
      {
        analogWrite(RLED, r);
        analogWrite(GLED, LOW);
        analogWrite(BLED, LOW);
        delay(10);
      }
      for (int b=0; b<256; b++)
      {
        analogWrite(RLED, LOW);
        analogWrite(GLED, LOW);
        analogWrite(BLED, b);
        delay(10);
      }
      for (int b=255; b>=0; b--)
      {
        analogWrite(RLED, LOW);
        analogWrite(GLED, LOW);
        analogWrite(BLED, b);
        delay(10);
      }
      for (int r=0; r<256; r++)
      {
        analogWrite(RLED, r);
        analogWrite(GLED, LOW);
        analogWrite(BLED, LOW);
        delay(10);
      }
    }
    //CHAOS
    else if (mode == 4)
    {
      analogWrite(RLED, random(0, 256));
      analogWrite(GLED, random(0, 256));
      analogWrite(BLED, random(0, 256));
      delay(random(125, 501));
    }
  /*  //TEAL
    else if (mode == 5)
    {
      analogWrite(RLED, 0);
      analogWrite(GLED, 255);
      analogWrite(BLED, 102);
    }
    //PURPLE
    else if (mode == 6)
    {
      analogWrite(RLED, 255);
      analogWrite(GLED, 0);
      analogWrite(BLED, 255);
    }
    //WHITE
    else if (mode == 7)
    {
      analogWrite(RLED, 255);
      analogWrite(GLED, 255);
      analogWrite(BLED, 255);
    }*/
    //OFF
    else if (mode == 0)
    {
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
    }
  }
  
void loop()
{
  cBtn = debounce(lBtn);            //read debounced state
  if (lBtn == LOW && cBtn == HIGH)  //if button was pressed
  {
    ledMode++;                      //increase mode value by 1
  }
  lBtn = cBtn;                      //reset button value
  if (ledMode == 5) ledMode = 0;    //after mode X (X=highest mode+1), return mode value to 0
  setMode(ledMode);                 //change the LED state
}


void checkbtn()
{
  cBtn = debounce(lBtn);            //read debounced state
  if (lBtn == LOW && cBtn == HIGH)  //if button was pressed
  {
    ledMode++;                      //increase mode value by 1
  }
  lBtn = cBtn;                      //reset button value
  if (ledMode == 5) ledMode = 0;    //after mode X (X=highest mode+1), return mode value to 0
}
