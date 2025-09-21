#ifndef INFRARED_H
#define INFRARED_H

class InfraRed {
  
public:
  int IR1;
  int IR2;
  int IR3;
  int IR4;

  int IR1_value = 0;
  int IR2_value = 0;
  int IR3_value = 0;
  int IR4_value = 0;

  InfraRed();
  void readIRS();

};

#endif