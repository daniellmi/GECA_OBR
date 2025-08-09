#ifndef PATH_H
#define PATH_H

#include "Motor.h"

extern int IR1;
extern int IR2;
extern int IR3;
extern int IR4;

class Path : protected Motor {

private:
  int IR2ValueForIntersection;  // valor do IR2 na fita durante a interseção
  int IR3ValueForIntersection;  // valor do IR3 na fita durante a interseção

public:
  // valores máximos encontrado pelos infravermelhos centrais
  int max_IR2;
  int max_IR3;

  Path() {
    IR2ValueForIntersection = 0;
    IR3ValueForIntersection = 0;
    max_IR2 = 0;
    max_IR3 = 0;
  }

  void intersection(int d) {

    int count = 1;

    stop();
    delay(200);
    go(80, 80);
    delay(400);

    do {

      left(100, 100);
      delay(d);

      right(100, 100);
      delay(d);

      IR3ValueForIntersection = analogRead(IR3);
      IR2ValueForIntersection = analogRead(IR2);

      if (max_IR3 < IR3ValueForIntersection) max_IR3 = IR3ValueForIntersection;
      if (max_IR2 < IR2ValueForIntersection) max_IR2 = IR2ValueForIntersection;
      ++count;
    } while (count <= 4);
  }

  void redirectObstacle() {
    back(100, 100);
    delay(650);
    right(100, 100);
    delay(850);

    go(100, 100);
    delay(3580);

    left(160, 130);
    delay(1850);

    while (true) {
      go(140, 120);

      if (analogRead(IR2) > 500 || analogRead(IR3) > 500) {
        stop();
        delay(500);
        go(100, 100);
        delay(300);

        this->turnOnRight90(900);

        back(140, 120);
        delay(250);
        break;
      }
    }
  }

  void turnOnRight90(int d) {
    go(120, 120);
    delay(d);

    while (true) {
      right(100, 100);
      if (analogRead(IR3) > 500) break;
    }

    back(100, 100);
    delay(350);
  }

  void turnOnLeft90(int d) {
    go(120, 120);
    delay(d);

    while (true) {
      left(100, 100);
      if (analogRead(IR2) > 500) break;
    }

    back(100, 100);
    delay(350);
  }

  void fullTurn() {
    right(120, 120);
    delay(1000);

    while (true) {
      right(110, 110);
      if (analogRead(IR3) > 500) break;
    }
  }

  void moveBackToReadColor() {
    stop();
    delay(200);
    back(80,80);
    delay(200);
  }
};
#endif