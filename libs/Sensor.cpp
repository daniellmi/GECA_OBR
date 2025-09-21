#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(const int trigger, const int echo) : Ultrasonic(trigger, echo) {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  isAvailable = true;  // usando essa condicao para depois desativar o ultrassonico na hora do resgate
}

int Sensor::getDistance() {

  distance = read(CM);
  if(distance <= 0) return -1;

  return distance;
}

void Sensor::availability(bool av) {
  isAvailable = av;
}

bool Sensor::available() {
  if (isAvailable) return true;

  return false;
}