


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

String in_bytes;
String song_name;
String prev_song;

void ScanDMD() { 
  dmd.scanDisplayBySPI();
}


long start = millis();
long timer = start;


void setup(void) {
  Serial.begin(9600);
  Timer1.initialize(1000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);   

  // Other fonts
  //dmd.selectFont(Arial_Black_16_ISO_8859_1);
  // dmd.selectFont(Arial_Black_16);
  // dmd.selectFont(Arial_14);
  dmd.selectFont(SystemFont5x7);
  dmd.drawMarquee(in_bytes,in_bytes.length(),(32*DISPLAYS_ACROSS)-1,4);

}

void loop(void) {

  if(Serial.available() > 0) {
    in_bytes = Serial.readStringUntil('\n');
    song_name = in_bytes;

    if(prev_song != in_bytes){
      Serial.print(song_name); //this prints in visual studio terminal  
      song_name = "";
      dmd.clearScreen(true);
      
    }

    prev_song = in_bytes;
  }


  //-----------------------------------------------------------By using "millis()"

  

  boolean ret = false;
  int interval = 100;

    if ((timer+interval) < millis()) {
      ret = dmd.stepMarquee(-1,0);
      if (ret){
        dmd.drawMarquee(in_bytes,in_bytes.length(),(32*DISPLAYS_ACROSS)-1,4);
      }
      timer=millis();
      // Serial.println(ret);
    }
}