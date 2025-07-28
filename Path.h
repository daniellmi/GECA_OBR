#ifndef PATH_H
#define PATH_H

#include "Motor.h"

extern int IR1;
extern int IR2;
extern int IR3;
extern int IR4;

class Path : protected Motor {

int IR2ValueForIntersection; // valor do IR2 na fita durante a interseção
int IR3ValueForIntersection; // valor do IR3 na fita durante a interseção

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

        go(100,100);
        delay(400);

        stop();
        delay(200);

    do{
          left(100,100);
          delay(d); 

          right(100,100);
          delay(d); 

          IR3ValueForIntersection = analogRead(IR3);
          IR2ValueForIntersection = analogRead(IR2);

          if(max_IR3 < IR3ValueForIntersection ) max_IR3 = IR3ValueForIntersection;
          if(max_IR2 < IR2ValueForIntersection) max_IR2 = IR2ValueForIntersection;
          ++count;
        }
        while(count <= 4);
}

void redirectObstacle() {
  right(100,100);
  delay(1600);

  go(100,100);
  delay(4000);
  
  left(150,150);
  delay(2900);

  while(true) {
  go(120,120);

  if(analogRead(IR2) > 500 || analogRead(IR3) > 500) {
    stop();
    delay(500);
    go(100, 100);
    delay(300);

    this->turnOnRight90();
    back(140,140);
    delay(200);
    break;
  } }
}

void turnOnRight90() {
        go(100,100);
        delay(900);

        while(true) {
          right(100, 100);
          if(analogRead(IR3) > 500) break;
        }

        back(100,100);
        delay(250);
}

  void turnOnLeft90() {
        go(100,100);
        delay(900);

        while(true) {
          left(100, 100);
          if(analogRead(IR2) > 500) break;
        }

        back(100,100);
        delay(250);
}

void fullTurn() {
      right(120, 120);
      delay(1000);

        while(true) {
          right(180, 180);
          if(analogRead(IR3) > 500) break;
        }
}

};
#endif