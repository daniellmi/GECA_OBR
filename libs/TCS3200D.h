#ifndef TCS3200D_H
#define TCS3200D_H

class TCS3200D {

public:

  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int white;
  unsigned int color_error;


  int pinS0;
  int pinS1;
  int pinS2;
  int pinS3;
  int pinOut;
  int pinLED;

  TCS3200D(int s0, int s1, int s2, int s3, int out, int led);
  void detectColor();
  void readColor();
};
#endif