#ifndef MOTOR_H
#define MOTOR_H

class Motor {

 int ENA = 2; // LOW HIGH
 int IN1 = 3; 
 int IN2 = 4;
 int IN3 = 5;
 int IN4 = 6;
 int ENB = 7;

 int ENAL= 13;
 int IN1L = 11;
 int IN2L = 12;
 int ENBL = 8; //LOW HIGH
 int IN3L = 9;
 int IN4L = 10;

public:

  Motor() {

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(IN1L, OUTPUT);
    pinMode(IN2L, OUTPUT);
    pinMode(IN3L, OUTPUT);
    pinMode(IN4L, OUTPUT);
    pinMode(ENAL, OUTPUT);
    pinMode(ENBL, OUTPUT);
  }
  
  void go(int right_speed, int left_speed) {

    //primeiro da direita 
    analogWrite(ENA, right_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    //segundo da direita 
    analogWrite(ENB, right_speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

   // primeiro da esquerda
    analogWrite(ENAL, left_speed);
    digitalWrite(IN1L, HIGH);
    digitalWrite(IN2L, LOW);

    //segundo da esquerda
    analogWrite(ENBL, left_speed);
    digitalWrite(IN3L, LOW);
    digitalWrite(IN4L, HIGH);
  }

  void stop() {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);

    digitalWrite(IN1L, HIGH);
    digitalWrite(IN2L, HIGH);

    digitalWrite(IN3L, HIGH);
    digitalWrite(IN4L, HIGH);
  }

  void right(int right_speed, int left_speed) {

    analogWrite(ENAL, left_speed);
    digitalWrite(IN1L, HIGH);
    digitalWrite(IN2L, LOW);

    analogWrite(ENBL, left_speed);
    digitalWrite(IN3L, LOW);
    digitalWrite(IN4L, HIGH);

     // motores da direita giram pra tras
    analogWrite(ENA, right_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    analogWrite(ENB, right_speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  void left(int right_speed, int left_speed) {

    analogWrite(ENA, right_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, right_speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    //motores da esquerda giram para tras
    analogWrite(ENAL, left_speed);
    digitalWrite(IN1L, LOW);
    digitalWrite(IN2L, HIGH);

    analogWrite(ENBL, left_speed);
    digitalWrite(IN3L, HIGH);
    digitalWrite(IN4L, LOW);

  }
   void right90(int left_speed) {

    analogWrite(ENAL, left_speed);
    digitalWrite(IN1L, HIGH);
    digitalWrite(IN2L, LOW);

    analogWrite(ENBL, left_speed);
    digitalWrite(IN3L, LOW);
    digitalWrite(IN4L, HIGH);

     // motores da direita param
    analogWrite(ENA, 0);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    
    analogWrite(ENB, 0);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
  }

  void left90(int right_speed) {

    analogWrite(ENA, right_speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, right_speed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    //motores da esquerda param
    analogWrite(ENAL, 0);
    digitalWrite(IN1L, HIGH);
    digitalWrite(IN2L, HIGH);

    analogWrite(ENBL, 0);
    digitalWrite(IN3L, HIGH);
    digitalWrite(IN4L, HIGH);

  }
  void back(int right_speed, int left_speed) {

    analogWrite(ENA, right_speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, right_speed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    analogWrite(ENAL, left_speed);
    digitalWrite(IN1L, LOW);
    digitalWrite(IN2L, HIGH);

    analogWrite(ENBL, left_speed);
    digitalWrite(IN3L, HIGH);
    digitalWrite(IN4L, LOW);
  }
};

#endif
