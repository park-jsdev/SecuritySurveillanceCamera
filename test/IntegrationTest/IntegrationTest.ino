/*
Integration Test for High Fidelity Prototype #1
Unit Tests included:
- SwitchAndServoTest
- LEDTest
- BuzzerTest
- SonicSensorTest
*/

#include <Servo.h>          // include the servo library

// Declare variables and functions used by the tests
Servo myservo;              // create a servo object
int servoPos = 20;                // variable to store the servo position
int switchPin = 2;          // the pin the switch is connected to
const int buzzerPin = 8;    // pin that will drive the buzzer
const int trigPin = 6;      // connects to the trigger pin on the distance sensor
const int echoPin = 7;      // connects to the echo pin on the distance sensor
const int redPin = 9;       // pin to control the red LED inside the RGB LED
float distance = 0;               // stores the distance measured by the distance sensor
void servoTest();
void LEDTest();
void buzzerTest();
void sonicSensorTest();
float getDistance();

void setup() {
  myservo.attach(5);        // tell the servo object that its servo is plugged into pin 5
  pinMode(switchPin, INPUT_PULLUP); // set the switch pin as an input with internal pull-up resistor
  pinMode(9, OUTPUT);      // Set pin 9 to output for LED
  pinMode(buzzerPin, OUTPUT);   // set the buzzer pin to output
  Serial.begin(9600);       // set up a serial connection with the computer
  pinMode(trigPin, OUTPUT);   // the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    // the echo pin will measure the duration of pulses coming back from the distance sensor

}

void loop() {
  // Repeat each test 3 times then wait 3 seconds
  switchAndServoTest();
  switchAndServoTest();
  switchAndServoTest();
  delay(3000);
  LEDTest();
  LEDTest();
  LEDTest();
  delay(3000);
  buzzerTest();
  buzzerTest();
  buzzerTest();
  delay(3000);
  sonicSensorTest();
  sonicSensorTest();
  sonicSensorTest();
  delay(3000);
}

void switchAndServoTest(){
  Serial.println("Testing Switch and Servo...");
  if (digitalRead(switchPin) == LOW) { // check if the switch is pressed (switchPin is connected to ground when pressed)
    for (servoPos = 20; servoPos <= 160; servoPos += 1) {  // rotate the servo from 20 to 160 degrees
      myservo.write(servoPos);                  // move the servo to the specified position
      delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
    }
    for (servoPos = 160; servoPos >= 20; servoPos -= 1) {  // rotate the servo from 160 to 20 degrees
      myservo.write(servoPos);                  // move the servo to the specified position
      delay(15);                           // wait for 15 milliseconds to allow the servo to reach the position
    }
  }
  else {
    myservo.write(20); // if the switch is not pressed, set the servo position to 20 degrees
  }
}

void LEDTest(){
  Serial.println("Testing LED...");
  digitalWrite(9, HIGH);   // Turn on the LED
  delay(2000);              // Wait for two seconds
  digitalWrite(9, LOW);    // Turn off the LED
  delay(2000);              // Wait for two seconds
}

void buzzerTest(){
  Serial.println("Testing Buzzer...");
  // beeps the buzzer
  tone(buzzerPin, 272);         // buzz the buzzer pin
  delay(100);                   // wait 100 milliseconds
  noTone(buzzerPin);            // turn the buzzer off
  delay(100);                   // wait 100 milliseconds
}

void sonicSensorTest(){
  Serial.println("Testing Sonic Sensor...");
  distance = getDistance();   // variable to store the distance measured by the sensor

  Serial.print(distance);     // print the distance that was measured
  Serial.println(" in");      // print units after the distance

  if (distance <= 10) {                       // if the object is close

    // make the LED red
    digitalWrite(redPin, 255);
    delay(100);                   // wait 100 milliseconds
    digitalWrite(redPin, 0);
    delay(100);                   // wait 100 milliseconds

  } else {                                    // if the object is far away
    // turn the LED off
    digitalWrite(redPin, 0);
  }
  delay(50);      // delay 50ms between each reading
}


// RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   // variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         // variable to store the distance calculated from the echo time

  // send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      // use the pulsein command to see how long it takes for the
                                          // pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  // calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              // send back the distance that was calculated
}

