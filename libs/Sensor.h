#ifndef SENSOR_H
#define SENSOR_H

#include <Ultrasonic.h>

class Sensor : Ultrasonic {

private:

  int distance;
  bool isAvailable;

public:

  Sensor(const int trigger, const int echo);

  int getDistance();
  void availability(bool av);
  bool available();
};
#endif
