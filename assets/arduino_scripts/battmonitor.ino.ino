/*
  Battmonitor

  Measures the voltage of a battery and activates a buzzer if the voltage drops below a certain voltage.

  A0  seria -5       A1 seria -4        A2 seria -3      A3 seria -2         A4 seria -1
  A5 seria -0       A6 seria 1          A7 seria 2
*/

#include <avr/io.h>
int val = 610;  //validated value: 610

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(9, OUTPUT);
  pinMode(-4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {

  // read the input on analog pin 1:
  int sensorValue = analogRead(-4);

  if(sensorValue < val) {

    analogWrite(9, 300);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
    analogWrite(9, 127);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    analogWrite(9, 0);
    digitalWrite(LED_BUILTIN, LOW);
  }

  
  delay(3000);
  
}

