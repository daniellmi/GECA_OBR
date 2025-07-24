#ifndef SENSOR_H
#define SENSOR_H

#include <Ultrasonic.h>

class Sensor : public Ultrasonic {

int distance;

public:

  Sensor(const int trigger, const int echo): Ultrasonic(trigger,echo) {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
  }

  int getDistance() {
    distance = read(CM);
    return distance;
  }
};
#endif
