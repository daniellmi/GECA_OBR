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

    left(120, 120);
    delay(d);

    right(120, 120);
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
  delay(2200);

  go(140, 140);
  delay(2200);

  left(130, 130);
  delay(2450);

  go(120, 120);
  delay(4200);

  left(140, 140);
  delay(1800);

  while (true) {
    go(80, 80);

    if (analogRead(IR2) > 500 || analogRead(IR3) > 500) {
      stop();
      delay(500);
      go(100, 100);
      delay(300);

      this->turnOn90(RIGHT90, 900);

      back(140, 120);
      delay(250);
      break;
    }
  }
}

void Path::turnOn90(Direction90 direction, int d) {
  go(120, 120);
  delay(d);

  while (true) {
   if(direction == RIGHT90) right(130, 130);
   else if(direction == LEFT90) left(130,130);

    if (analogRead(IR1) > 500 || analogRead(IR3) > 500) break;
  }

 back(100, 100);
  delay(350);
}

void Path::fullTurn() {
  right(120, 120);
  delay(1000);

  while (true) {
    right(180, 180);
    if (analogRead(IR3) > 500) break;
  }
}

void Path::moveBackToReadColor() {
    stop();
    delay(200);
    back(80, 80);
    delay(200);
}
