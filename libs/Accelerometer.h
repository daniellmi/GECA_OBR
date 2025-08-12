#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU6050.h>

class Accelerometer : MPU6050 {

private:
  float g;

public:

  void begin();
  float getY();

};
#endif