/*
File:    test-wifi.ino
Author:  Corban Pendrak
Date:    12Sep2023
Purpose: Test ESP32 Arduino connection and print Wifi Mac Address  
*/

#include "WiFi.h"
 
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
  Serial.println("I work!");
}
 
void loop()
{

}