#ifndef TCS3200_H
#define TCS3200_H

class TCS3200 {

public:

  int pinS0;
  int pinS1;
  int pinS2;
  int pinS3;
  int pinOut;
  int pinLED;

  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int white;

  TCS3200() {
    red = 0;
    green = 0;
    blue = 0;
    white = 0;

    pinS0 = 47;
    pinS1 = 43;
    pinS2 = 39;
    pinS3 = 37;
    pinOut = 41;
    pinLED = 45;
  }

  void detectColor() {
    //Vermelho
    digitalWrite(pinS2, LOW);
    digitalWrite(pinS3, LOW);
    red = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

    //Sem filtro
    digitalWrite(pinS2, HIGH);
    white = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

    //Azul
    digitalWrite(pinS2, LOW);
    digitalWrite(pinS3, HIGH);
    blue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

    //Verde
    digitalWrite(pinS2, HIGH);
    green = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  }
};
#endif