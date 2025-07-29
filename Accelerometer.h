#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU6050.h>

class Accelerometer : private MPU6050 {

float g;

public: 
   void begin() {
    g = 16834.0;
    initialize();
    CalibrateAccel();
    CalibrateGyro();
  }

float getY() {
  return getAccelerationY() / g;
}
};
#endif