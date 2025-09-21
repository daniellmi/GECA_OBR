#include <Arduino.h>
#include "InfraRed.h"

InfraRed::InfraRed() {
  IR1 = A0;
  IR2 = A1;
  IR3 = A2;
  IR4 = A3;
}

void InfraRed::readIRS() {
 
  Serial.print("IR1: ");
  Serial.println(analogRead(IR1));

  Serial.print("IR2: ");
  Serial.println(analogRead(IR2));

  Serial.print("IR3: ");
  Serial.println(analogRead(IR3));

  Serial.print("IR4: ");
  Serial.println(analogRead(IR4));
  delay(500);
}
