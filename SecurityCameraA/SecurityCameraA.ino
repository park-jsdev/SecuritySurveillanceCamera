/*
  Basic Security Camera  

   Controlled by a switch to turn on and off.
   The system will rotate using a servo motor based on a open loop to scan the area.
   The system will use an ultrasonic sensor to detect movement and objects which are in range (up to 4 meters).
   If an object is in range, the camera will stop rotating.
   The system will turn on an LED to warn intruders.
   If a human-sized object or human-like motion is detected within a critical range (1-2m) a piezo buzzer will activate to warn the area.
  
*/

#include <Servo.h>                // include the servo library

// Change the distance variables to desired values.
int warningDistance = 30;
int alarmDistance = 5;

// Declare variables and functions used by the tests
Servo myservo;              // create a servo object
int servoPos = 20;                // variable to store the servo position
int switchPin = 2;          // the pin the switch is connected to
const int buzzerPin = 8;    // pin that will drive the buzzer
const int trigPin = 6;      // connects to the trigger pin on the distance sensor
const int echoPin = 7;      // connects to the echo pin on the distance sensor
const int redPin = 9;       // pin to control the red LED inside the RGB LED

float distance = 0;               //stores the distance measured by the distance sensor
float getDistance();

bool isRotating = true;
bool humanDetectedInWarningDistance = false;
bool humanDetectedInAlarmDistance = false;

void setup()
{
  myservo.attach(5);        // tell the servo object that its servo is plugged into pin 5
  pinMode(switchPin, INPUT_PULLUP); // set the switch pin as an input with internal pull-up resistor
  pinMode(9, OUTPUT);      // Set pin 9 to output for LED
  pinMode(buzzerPin, OUTPUT);   // set the buzzer pin to output
  Serial.begin(9600);       // set up a serial connection with the computer
  pinMode(trigPin, OUTPUT);   // the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    // the echo pin will measure the duration of pulses coming back from the distance sensor
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {

    // if the switch is on, rotate the servo
    isRotating = true;

    while (isRotating && digitalRead(switchPin) == HIGH){

      // rotate the servo
      myservo.write(20);
      getData();
      delay(500);
      myservo.write(40);
      getData();
      delay(500);
      myservo.write(60);
      getData();
      delay(500);
      myservo.write(80);
      getData();
      delay(500);
      myservo.write(100);
      getData();
      delay(500);
      myservo.write(120);
      getData();
      delay(500);
      myservo.write(140);
      getData();
      delay(500);
      myservo.write(160);
      getData();
      delay(500);
      myservo.write(140);
      getData();
      delay(500);
      myservo.write(120);
      getData();
      delay(500);
      myservo.write(100);
      getData();
      delay(500);
      myservo.write(80);
      getData();
      delay(500);
      myservo.write(60);
      getData();
      delay(500);
      myservo.write(40);
      getData();
      delay(500);
    }
  } else {
    // if the switch is off, stop rotating the servo
    isRotating = false;
    myservo.write(90); // move the servo to the center position
  }
}

//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 58.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

void getData(){
  if (digitalRead(switchPin) == HIGH) {
    distance = getDistance();
    Serial.print(distance);
    Serial.println(" cm");
    
    if (distance <= warningDistance) { // if an object is within range of the ultrasonic sensor
      // stop rotating the servo
      isRotating = false;

      while (!isRotating && digitalRead(switchPin) == HIGH){
        // The camera should be able to be turned off even during the loop

        // get the current position of the servo again and update servoPos
        servoPos = myservo.read();
        // set the servo position at the current position in order to stop the rotation.
        myservo.write(servoPos);

        if (distance <= alarmDistance && digitalRead(switchPin) == HIGH) { // if the object is within critical range
          // activate the piezo buzzer
          tone(buzzerPin, 272);
          // turn on the warning LED
          digitalWrite(redPin, HIGH);
          delay(300);
          noTone(buzzerPin);
          digitalWrite(redPin, LOW);
          delay(300);
          Serial.println("Human detected in critical range...");
        } else { // the object is within warning distance but not critical range
          Serial.println("Object detected within 4m. Warning...");

          // turn on the warning LED
          digitalWrite(redPin, HIGH);
          delay(300);
          // turn off the warning LED
          digitalWrite(redPin, LOW);
          delay(300);
        }
        delay(25);
        // Check the distance again at the end of the while loop to update conditions
        distance = getDistance();
        Serial.print(distance);
        Serial.println(" cm");
        // exit the loop if the distance is no longer within the warning range or if the switch is turned off
        if (distance > warningDistance || digitalRead(switchPin) == LOW) {
          isRotating = true;
        }
      } // end of while loop
    } else { // if the distance is not or no longer within warning range
      isRotating = true;
    }
    isRotating = true;
  } // end of switch check if 
}
