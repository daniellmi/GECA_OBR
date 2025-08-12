#include <Arduino.h>
#include "TCS3200.h"

TCS3200::TCS3200() {
  color = "";
  color_error = 30;

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
void TCS3200::detectColor() {
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

  unsigned int avg = (red + green + blue) / 3;

  if (abs(red - blue) < 40 && abs(red - green) < 40 && abs(green - blue) < 40 && white > 50 && avg > 100)
    color = "GRAY";

  else if ((red + color_error < green) && (red < blue) && (white < 100)) color = "RED";

  else if ((blue + color_error < green) && (blue < red) && (white < 100)) color = "BLUE";

  else if ((green < red) && (green < blue) && (white < 100)) color = "GREEN";

  else color = "WHITE";
}

void TCS3200::readColor() {
  Serial.print("blue: ");
  Serial.println(blue);

  Serial.print("red: ");
  Serial.println(red);

  Serial.print("green: ");
  Serial.println(green);

  Serial.print("white: ");
  Serial.println(white);
}

String TCS3200::getColor() {
  return color;
}