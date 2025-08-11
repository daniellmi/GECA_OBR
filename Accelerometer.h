#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU6050.h>

class Accelerometer : private MPU6050 {

private:
  float g;

public:
  void begin() {
    g = 16834.0;
    initialize();
    CalibrateAccel();
    // CalibrateGyro(); 
  }

  float getY() {
    return getAccelerationY() / g;
  }

  bool isInclined() {
    if(this->getY() >= 0.12) return true;
    return false;
  }
};
#endif