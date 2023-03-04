/*
Buzzer Test
*/

const int buzzerPin = 8;         // pin that will drive the buzzer

void setup()
{
  pinMode(buzzerPin, OUTPUT);   // set the buzzer pin to output
}

void loop() {

  // beeps the buzzer
    tone(buzzerPin, 272);         // buzz the buzzer pin
    delay(100);                   // wait 100 milliseconds

    noTone(buzzerPin);            // turn the buzzer off
    delay(100);                   // wait 100 milliseconds
    
}
