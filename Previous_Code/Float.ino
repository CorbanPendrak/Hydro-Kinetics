#include "Arduino.h"
#include "uRTCLib.h"
#include <SoftwareSerial.h>//declares neccesary libraries 

static const int RXPin = 4, TXPin = 3;
SoftwareSerial ss(RXPin, TXPin);
char data = 0;

//------------------------------------------------------------------------------
//below is HBridge startup
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENA 10
#define ENB 5
 

//--------------------------------------------------------end of HBridge startup start of clock start up
uRTCLib rtc(0x68);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



void setup()
{
Serial.begin(9600);  // baud rate for serial data transmission
URTCLIB_WIRE.begin();
}



void loop()
{
  if(Serial.available() > 0) // checks if any data is received
  {
    data = Serial.read(); //Reading any receiving data and storing it into variable named data*/
    Serial.print(data);  //displaying the data
    Serial.print("\n");  //adding space by giving a New line
        
    if(data == '1')      // when the value  is equal to 1
    { 
      Serial.println("granting UTC and Special MATE number");
      Serial.print("UTC: ");
      rtc.refresh();

      Serial.print(rtc.year());
      Serial.print('/');
      Serial.print(rtc.month());
      Serial.print('/');
      Serial.print(rtc.day());

      Serial.print(" (");
      Serial.print(daysOfTheWeek[rtc.dayOfWeek()-1]);
      Serial.print(") ");

      Serial.print(rtc.hour());
      Serial.print(':');
      Serial.print(rtc.minute());
      Serial.print(':');
      Serial.println(rtc.second());
      Serial.print("Special MATE code: yeet?");//needs to be changed later
      delay(1000);
    }
    else
    {
      Serial.print(F(" "));
    }
      
  }


  if(data == '0')  // when the value  is equal to 0
    {  
      Serial.print("starting descent"); 

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
 
        
      analogWrite(ENB, 255);
      analogWrite(ENA, 0);
      analogWrite(ENA, 255);//turns on IN pump making float sink
        //motorAccel();
      delay(8000);//leaves IN pump on for a while
      analogWrite(ENA, 0);//turns IN pump off and turns OUT pump on
      analogWrite(ENB, 255);//this make the float start rising
        //motorDecel();
      while(data == 0)
      {
        Serial.println("test");
      }
      delay(30000);
      analogWrite(ENB, 0);// at this point the float must have attained + bouyancy
    }     
}  
