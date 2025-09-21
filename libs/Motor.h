#ifndef MOTOR_H
#define MOTOR_H

class Motor {

private:

  int ENA = 2;  // LOW HIGH
  int IN1 = 32;
  int IN2 = 34;
  int IN3 = 5;
  int IN4 = 6;
  int ENB = 7;

  int ENAL = 13;
  int IN1L = 11;
  int IN2L = 12;
  int ENBL = 8;  //LOW HIGH
  int IN3L = 9;
  int IN4L = 10;

public:

  Motor();

  void go(int right_speed, int left_speed);
  void stop();

  void right(int right_speed, int left_speed);
  void left(int right_speed, int left_speed);

  void right90(int left_speed);
  void left90(int right_speed);

  void back(int right_speed, int left_speed);
};

#endif