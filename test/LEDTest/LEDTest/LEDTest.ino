void setup() {

  pinMode(9, OUTPUT);      // Set pin 13 to output

}


void loop() {

  digitalWrite(9, HIGH);   // Turn on the LED

  delay(2000);              // Wait for two seconds

  digitalWrite(9, LOW);    // Turn off the LED

  delay(2000);              // Wait for two seconds

}

