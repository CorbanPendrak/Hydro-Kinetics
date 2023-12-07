/*
  File: calibrate_time.ino
  Author: Corban Pendrak
  Purpose: Calibrate the date/time module
  Date Created: 20Nov23
  Modified: 05Dec23
*/

#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  // Open Serial Monitor
  Serial.begin(9600);

  // Pause for console to open
  delay(3000); 
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //Serial.flush();
    while (1);
  }

  // Automatically set RTC to date & time of computer
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now= rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.dayOfTheWeek());
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  delay(1000);
}