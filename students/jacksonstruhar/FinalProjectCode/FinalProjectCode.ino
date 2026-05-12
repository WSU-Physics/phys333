/*
Gym repetition counter designed for PHY 333 final project
  - Uses distance sensor to detece number of repetitions and displays on 16x2 LCD
  - 4 buttons allows user to select an exercise, amount of reps, and reset the menus
*/

#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
const int btnLeft = 5; //button pins
const int btnRight = 4;
const int btnSelect = 3;
const int btnReset = 2;
const int motorPin = 6; //motor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //LCD pinouts

enum State { EXERCISE, REPS, CONFIRM, COUNTING, COMPLETE };
State currentState = EXERCISE;

int exerciseIndex = 0; // 0 = Bench, 1 = Squat
String exercises[2] = {"Bench", "Squat"}; //exercise menu

int repOptions[3] = {8, 10, 12}; //rep select
int repIndex = 0;
int selectedReps = 0;

int topThreshold = 0; //thresholds initialize
int bottomThreshold = 0;

int currentReps = 0; //rep motion
bool wentDown = false;

char dist[4]; //distance sensor

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(btnLeft, INPUT);
  pinMode(btnRight, INPUT);
  pinMode(btnSelect, INPUT);
  pinMode(btnReset, INPUT);
  pinMode(motorPin, OUTPUT);
  showExerciseMenu();
}

void loop() {

  if (digitalRead(btnReset) == LOW) { //reset menu
    resetSystem();
    delay(250);
  }

  switch (currentState) {

    case EXERCISE:
      handleExerciseMenu();
      break;

    case REPS:
      handleRepMenu();
      break;

    case CONFIRM:
      handleConfirm();
      break;

    case COUNTING:
      countReps();
      break;

    case COMPLETE:
      showComplete();
      break;
  }
}

void showExerciseMenu() { //exercise menu
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercise:");

  lcd.setCursor(0, 1); //sets cursor location for exercise
  for (int i = 0; i < 2; i++) {
    if (i == exerciseIndex) lcd.print(">");
    else lcd.print(" ");
    lcd.print(exercises[i]);
    lcd.print(" ");
  }
}

void handleExerciseMenu() {
  if (digitalRead(btnLeft) == LOW || digitalRead(btnRight) == LOW) { //updates excercise when L or R button
    exerciseIndex = !exerciseIndex;
    showExerciseMenu();
    delay(200);
  }

  if (digitalRead(btnSelect) == LOW) {
    currentState = REPS;
    showRepMenu();
    delay(250);
  }
}

void showRepMenu() { //repetition menu
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Reps");

  lcd.setCursor(0, 1); //sets cursor for repetition
  for (int i = 0; i < 3; i++) {
    if (i == repIndex) lcd.print(">");
    else lcd.print(" ");
    lcd.print(repOptions[i]);
    lcd.print(" ");
  }
}

void handleRepMenu() {
  if (digitalRead(btnLeft) == LOW) { //L button for repetition
    repIndex--;
    if (repIndex < 0) repIndex = 2;
    showRepMenu();
    delay(200);
  }

  if (digitalRead(btnRight) == LOW) { //R button for repetiion
    repIndex++;
    if (repIndex > 2) repIndex = 0;
    showRepMenu();
    delay(200);
  }

  if (digitalRead(btnSelect) == LOW) { //select button for repetition
    selectedReps = repOptions[repIndex];
    setThresholds();
    currentState = CONFIRM;
    showConfirm();
    delay(250);
  }
}

void setThresholds() { //exercise thresholds inches
  if (exerciseIndex == 0) { // Bench
    topThreshold = 33;
    bottomThreshold = 20;
  } else { // Squat
    topThreshold = 50;
    bottomThreshold = 22;
  }
}

int confirmIndex = 0;

void showConfirm() { 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(exercises[exerciseIndex]);
  lcd.print(" ");
  lcd.print(selectedReps);

  lcd.setCursor(0, 1);
  lcd.print("Start? Yes No"); //yes or no menu 
  updateConfirmCursor();
}

void handleConfirm() {
  if (digitalRead(btnLeft) == LOW || digitalRead(btnRight) == LOW) {
    confirmIndex = !confirmIndex;
    updateConfirmCursor();
    delay(200);
  }

  if (digitalRead(btnSelect) == LOW) { 
    if (confirmIndex == 0) {
      currentReps = 0;
      currentState = COUNTING;
      lcd.clear();
    } else {
      currentState = EXERCISE;
      showExerciseMenu();
    }
    delay(250);
  }
}

void updateConfirmCursor() {
  if (confirmIndex == 0) lcd.setCursor(7, 1);
  else lcd.setCursor(11, 1);
  lcd.cursor();
}

void countReps() { //rep counter
  int distance = readDistance();

  lcd.setCursor(0, 0);
  lcd.print(currentReps);
  lcd.print("/");
  lcd.print(selectedReps);

  if (distance <= bottomThreshold && !wentDown) { //repetition logic
    wentDown = true;
  }

  if (distance >= topThreshold && wentDown) { //adds 1 to rep count
    currentReps++;
    wentDown = false;
  }

  if (currentReps >= selectedReps) { //set completed
    currentState = COMPLETE;
  }
}

void showComplete() { //set completed
  lcd.clear();
  lcd.print("Set Completed!");

  digitalWrite(motorPin, HIGH); //motor turns on when set is complete
  delay(1000);
  digitalWrite(motorPin, LOW);
  delay(10000); //longer delay so it gives the user time to reset the system
}

int readDistance() { //distance sensor
  while (Serial.available()) Serial.read();
  while (Serial.read() != 82) {
    delayMicroseconds(1);
  }

  Serial.readBytes(dist, 3);
  return atoi(dist);
}

void resetSystem() { //reset system
  currentState = EXERCISE;
  exerciseIndex = 0;
  repIndex = 0;
  currentReps = 0;
  showExerciseMenu();
}