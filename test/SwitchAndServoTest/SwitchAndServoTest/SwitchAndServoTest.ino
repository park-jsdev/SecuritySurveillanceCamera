#include <Servo.h>          // include the servo library

Servo myservo;              // create a servo object
int pos = 20;                // variable to store the servo position
int switchPin = 2;          // the pin the switch is connected to

void setup() {
  myservo.attach(5);        // tell the servo object that its servo is plugged into pin 1
  pinMode(switchPin, INPUT_PULLUP); // set the switch pin as an input with internal pull-up resistor
}

void loop() {
  if (digitalRead(switchPin) == LOW) { // check if the switch is pressed (switchPin is connected to ground when pressed)
    for (pos = 20; pos <= 160; pos += 1) {  // rotate the servo from 20 to 160 degrees
      myservo.write(pos);                  // move the servo to the specified position
      delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
    }
    for (pos = 160; pos >= 20; pos -= 1) {  // rotate the servo from 160 to 20 degrees
      myservo.write(pos);                  // move the servo to the specified position
      delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
    }
  }
  else {
    myservo.write(20); // if the switch is not pressed, set the servo position to 20 degrees
  }
}
