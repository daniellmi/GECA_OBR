#include <Arduino.h>
#include "Path.h"

Path::Path() {
  IR2ValueForIntersection = 0;
  IR3ValueForIntersection = 0;
  max_IR2 = 0;
  max_IR3 = 0;
}

void Path::intersection(int d) {

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

void Path::redirectObstacle() {

  back(100, 100);
  delay(700);

  right(120, 120);
  delay(1900);

  go(100, 100);
  delay(2000);

  left(120, 120);
  delay(2100);

  go(120, 120);
  delay(3600);

  left(120, 120);
  delay(2100);

  while (true) {
    go(80, 80);

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

void Path::turnOnRight90(int d) {
  go(120, 120);
  delay(d);

  while (true) {
    right(100, 100);
    if (analogRead(IR3) > 500) break;
  }

  back(100, 100);
  delay(350);
}

void Path::turnOnLeft90(int d) {
  go(120, 120);
  delay(d);

  while (true) {
    left(100, 100);
    if (analogRead(IR2) > 500) break;
  }

  back(100, 100);
  delay(350);
}
void Path::fullTurn() {
  right(120, 120);
  delay(1000);

  while (true) {
    right(110, 110);
    if (analogRead(IR3) > 500) break;
  }
}

void Path::moveBackToReadColor() {
    stop();
    delay(200);
    back(80, 80);
    delay(200);
}
