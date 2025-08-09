#ifndef SENSOR_H
#define SENSOR_H

#include <Ultrasonic.h>

class Sensor : protected Ultrasonic {

private:

  int distance;
  bool isAvailable;

public:

  Sensor(const int trigger, const int echo) : Ultrasonic(trigger, echo) {
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    isAvailable = true;  // usando essa condicao para depois desativar o ultrassonico na hora do resgate
  }

  int getDistance() {
    distance = read(CM);
    return distance;
  }

  void availability(bool av) {
    isAvailable = av;
  }

  bool available() {
    if (isAvailable) return true;

    return false;
  }
};
#endif
