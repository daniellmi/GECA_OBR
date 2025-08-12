#include <Arduino.h>
#include "InfraRed.h"

InfraRed::InfraRed() {
  IR1 = A0;
  IR2 = A1;
  IR3 = A2;
  IR4 = A3;
}

void InfraRed::mapInfraRed() {
  IR1_value = map(analogRead(IR1), 0, 1023, 0, 100);
  IR2_value = map(analogRead(IR2), 0, 1023, 0, 100);
  IR3_value = map(analogRead(IR3), 0, 1023, 0, 100);
  IR4_value = map(analogRead(IR4), 0, 1023, 0, 100);
}

void InfraRed::readIRS() {
  Serial.print("IR1: ");
  Serial.println(IR1_value);

  Serial.print("IR2: ");
  Serial.println(IR2_value);

  Serial.print("IR3: ");
  Serial.println(IR3_value);

  Serial.print("IR4: ");
  Serial.println(IR4_value);
  delay(500);
}

void InfraRed::readIRSwithNoMap() {

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
