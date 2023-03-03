#include <Servo.h>          // include the servo library

Servo myservo;              // create a servo object
int pos = 20;                // variable to store the servo position

void setup() {
  myservo.attach(5);        // tell the servo object that its servo is plugged into pin 1
}

void loop() {
  for (pos = 20; pos <= 160; pos += 1) {  // rotate the servo from 20 to 160 degrees
    myservo.write(pos);                  // move the servo to the specified position
    delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
  }
  for (pos = 160; pos >= 20; pos -= 1) {  // rotate the servo from 160 to 20 degrees
    myservo.write(pos);                  // move the servo to the specified position
    delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
  }
}