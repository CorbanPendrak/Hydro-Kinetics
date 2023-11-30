#include <ESP32Servo.h>

byte servoPin = 13;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);

  servo.writeMicroseconds(1500); // Sends stop signal to ESC

  delay(7000); // Pause to allow ESC to recognize stopped signal
  Serial.println("\rEnter PWM signal value 1100 to 1900, 1500 to stop");
}

void loop() {
  int val = Serial.parseInt();

  if (val == 0) 
  {
    // do nothing if no input
  }
  else if(val < 1100 || val > 1900)
  {
    Serial.println("Error: Invalid input " + String(val) + ", choose a value between 1100 and 1900"); // send error message if out of range
  }
  else
  {
    servo.writeMicroseconds(val); // Send signal to ESC
  }
}
