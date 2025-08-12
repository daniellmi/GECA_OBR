#ifndef LEDS_H
#define LEDS_H

#define RIGHT_LDR A14
#define LEFT_LDR A15

class Leds {

private:

  int LEFT_GREEN;
  int LEFT_RED;
  int LEFT_BLUE;

  int RIGHT_RED;
  int RIGHT_GREEN;
  int RIGHT_BLUE;

  // |--- VALORES DAS LEDS ESQUERDAS NO BRANCO ---|
  int LEFT_RED_WHITE_VALUE;
  int LEFT_GREEN_WHITE_VALUE;
  int LEFT_BLUE_WHITE_VALUE;

  // |--- VALORES DAS LEDS DIREITAS NO BRANCO ---|
  int RIGHT_RED_WHITE_VALUE;
  int RIGHT_GREEN_WHITE_VALUE;
  int RIGHT_BLUE_WHITE_VALUE;

public:

  String colorRight;
  String colorLeft;

  Leds();
  void calibratingLeds();
  void ReadLdrOnGreen();
};
#endif