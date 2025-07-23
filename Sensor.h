#ifndef SENSOR_H
#define SENSOR_H

#include <Ultrasonic.h>

class Sensor{

  Ultrasonic ultra;
  int distance;

public:

  Sensor(const int trigger, const int echo): ultra(trigger,echo) {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  int readtSensor() {
    distance = ultra.read(CM);
    return distance;
  }
};
#endif
