#ifndef SENSOR_H
#define SENSOR_H
#include <Ultrasonic.h>

#define trigger 24
#define echo 22

class Sensor{

  Ultrasonic ultra;
  int distance;

public:

  Sensor(): ultra(trigger, echo) {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  int readtSensor() {
    distance = ultra.read(CM);
    return distance;
  }
};
#endif
