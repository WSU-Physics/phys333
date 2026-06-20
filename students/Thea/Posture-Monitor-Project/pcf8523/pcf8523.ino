// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(57600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC is NOT initialized, let's set the time!");

    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2026, 5, 5, 10, 11, 0));
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  rtc.start();


  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  // float drift_unit = 4.069; //For corrections every min the drift_unit is 4.069 ppm (use with offset mode PCF8523_OneMinute)
  int offset = round(deviation_ppm / drift_unit);
  // rtc.calibrate(PCF8523_TwoHours, offset); // Un-comment to perform calibration once drift (seconds) and observation period (seconds) are correct
  // rtc.calibrate(PCF8523_TwoHours, 0); // Un-comment to cancel previous calibration

  Serial.print("Offset is "); Serial.println(offset); // Print to control offset

}

void loop () {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    //Serial.print(" since midnight 1/1/1970 = ");
    //Serial.print(now.unixtime());
    //Serial.print("s = ");
    //Serial.print(now.unixtime() / 86400L);
    //Serial.println("d");

    // calculate a date which is 7 days, 12 hours and 30 seconds into the future
    //DateTime future (now + TimeSpan(7,12,30,6));

    //Serial.print(" now + 7d + 12h + 30m + 6s: ");
    //Serial.print(future.year(), DEC);
    //Serial.print('/');
    //Serial.print(future.month(), DEC);
    //Serial.print('/');
    //Serial.print(future.day(), DEC);
    //Serial.print(' ');
    //Serial.print(future.hour(), DEC);
    //Serial.print(':');
    //Serial.print(future.minute(), DEC);
    //Serial.print(':');
    //Serial.print(future.second(), DEC);
    //Serial.println();

    Serial.println();
    delay(3000);
}
