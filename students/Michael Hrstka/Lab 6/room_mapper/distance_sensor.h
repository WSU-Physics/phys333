#ifndef DistanceSensor_h
#define DistanceSensor_h
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"

class DistanceSensor {
  public:
  DistanceSensor() {
    initUSART();
  }


  char getDistance() {
    char serialArray[6]; // Should never actually get this long, but C++ is complaining about not allocating space, so I'll give it gets space

    int i = 0;
    while (1) {
      char serialCharacter = receiveByte();
      if(serialCharacter == 'R') return serialArray;
      else serialArray[i++] = serialCharacter;
    }
  }
};
#endif