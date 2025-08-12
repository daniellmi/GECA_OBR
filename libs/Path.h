#ifndef PATH_H
#define PATH_H

#include "Motor.h"
#include "InfraRed.h"

extern unsigned int black_tape;
extern unsigned int black_tape_2;

class Path : protected Motor, protected InfraRed {

private:

  int IR2ValueForIntersection;  // valor do IR2 na fita durante a interseção
  int IR3ValueForIntersection;  // valor do IR3 na fita durante a interseção

public:
  // valores máximos encontrado pelos infravermelhos centrais
  int max_IR2;
  int max_IR3;

  Path();

  void intersection(int d);
  void redirectObstacle();

  void turnOnRight90(int d);
  void turnOnLeft90(int d);

  void fullTurn();
  void moveBackToReadColor();
};
#endif