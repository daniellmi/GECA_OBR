#include <Arduino.h>
#include "Accelerometer.h" 

void Accelerometer::begin() {
  g = 16834.0;
  initialize();
  CalibrateAccel();
}

float Accelerometer::getY() {
  return getAccelerationY() / g;
}