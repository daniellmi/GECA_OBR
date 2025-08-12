#ifndef TCS3200_H
#define TCS3200_H

class TCS3200 {

private:

  String color;
  unsigned int color_error;

  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int white;

  unsigned int total;

public:

  int pinS0;
  int pinS1;
  int pinS2;
  int pinS3;
  int pinOut;
  int pinLED;

  TCS3200();
  void detectColor();
  void readColor();
  String getColor();

};
#endif