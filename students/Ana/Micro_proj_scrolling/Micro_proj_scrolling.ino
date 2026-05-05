// Microprocessors: Phys 333 Final Project
// Created as supplemental project to Electronics Final project Lyte Audio Visualizer
// Github: https://github.com/freetronics/DMD/tree/master
// Drawn from sample code -> adjusted for use
// Adjusted library file DMD.h and DMD.cpp 
// Changed drawMarquee from char to string
// void DMD::drawMarquee(String bChars, byte length, int left, int top)
// void drawMarquee( String bChars, byte length, int left, int top);
// Display: P10 Red LED Panel Display Large Size 32cm X 16cm
// Arduino Uno 
// Ana S. Micro Final Project due 5/7/2026


#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "Arial_black_16.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial14.h"
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1 //Number of P10 panels vertically
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

String song_name = "";
String prev_song = "";
boolean lastButton = LOW;
boolean currentButton = LOW;
const int BUTTON = 2;


void ScanDMD() { 
  dmd.scanDisplayBySPI();
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if(last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}


long start = millis();
long timer = start;


void setup(void) {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);

  Timer1.initialize(1000);          
  Timer1.attachInterrupt(ScanDMD);   

  // Other fonts
  //dmd.selectFont(Arial_Black_16_ISO_8859_1);
  // dmd.selectFont(Arial_Black_16);
  // dmd.selectFont(Arial_14);
  dmd.selectFont(SystemFont5x7);
  dmd.drawMarquee(song_name,song_name.length(),(32*DISPLAYS_ACROSS)-1,4);

}

void loop(void) {

  currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH) {
    Serial.println("skip");
  }
  lastButton = currentButton;


  if(Serial.available() > 0) {
    song_name = Serial.readStringUntil('\n');
    dmd.clearScreen(true);
    
  }

  boolean ret = false;
  int interval = 25;

    if ((timer+interval) < millis()) {
      ret = dmd.stepMarquee(-1,0);
      if (ret){
        dmd.drawMarquee(song_name,song_name.length(),(32*DISPLAYS_ACROSS)-1,4);
      }
      timer = millis();
    }
    prev_song = song_name;
}