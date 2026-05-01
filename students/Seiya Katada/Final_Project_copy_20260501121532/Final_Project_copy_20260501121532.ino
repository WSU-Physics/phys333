#define L1 9 
#define L2 8 
#define L3 7 
#define L4 6 
//Lines

#define C1 5 
#define C2 4 
#define C3 3 
#define C4 2 
//Columns

const int LED_Green=10; //if the password is correct, this LED will be on.
const int LED_Red=11; //if the password is incorrect, this LED will be on.

String input = "";
// to store some input numbers.
String password = "37C#";
// to set password
char lastKey = '\0'; 
//this code is to ignore the number if it is exactly the same as the one entered immediately before. 
//Needed only one number that is why char is used.

void setup ( ) { 
  Serial.begin ( 9600 ); 
  pinMode(L1, OUTPUT); 
  pinMode(L2, OUTPUT); 
  pinMode(L3, OUTPUT); 
  pinMode(L4, OUTPUT); 
  pinMode(C1, INPUT_PULLUP); 
  pinMode(C2, INPUT_PULLUP); 
  pinMode(C3, INPUT_PULLUP ); 
  pinMode(C4, INPUT_PULLUP); 
  digitalWrite(L1, HIGH); 
  digitalWrite(L2, HIGH); 
  digitalWrite(L3, HIGH); 
  digitalWrite(L4, HIGH); 
  pinMode (LED_Green, OUTPUT);
  pinMode (LED_Red, OUTPUT);
} 

void loop () { 
  readLine(L1, "123A" ); 
  readLine(L2, "456B" ); 
  readLine(L3, "789C" ); 
  readLine(L4, "*0#D" );
  
  if (input.length() == 4) { 
    //to set the input number as 4 digit number
    if (input == password) { 
      // once the input is same as password, the serial monitor will say "Correct". otherwise wrong
      Serial.println("Correct");
      digitalWrite(LED_Green, HIGH);
      digitalWrite(LED_Red, LOW);
    } else {
      Serial.println("Incorrect");
      digitalWrite(LED_Green, LOW);
      digitalWrite(LED_Red, HIGH);
    }
    input = ""; 
  }

  delay(500);
  //0.5 seconds between pushing the button
}

void readLine (int line, String characters) { 
  digitalWrite(line, LOW); 
  //When the line is LOW, the keypad will detect and read it.

  char key ='\0';
    if (digitalRead(C1) == LOW) key = characters.charAt(0);
    else if (digitalRead(C2) == LOW) key = characters.charAt(1);
    else if (digitalRead(C3) == LOW) key = characters.charAt(2);
    else if (digitalRead(C4) == LOW) key = characters.charAt(3);

    if(key !='\0' && key != lastKey) {
      Serial.println(key);
      input += key;
      //to add number in input
      lastKey = key;
    } 

    if (key == '\0') {
    lastKey = '\0';
    }

    digitalWrite(line, HIGH); 
}   
