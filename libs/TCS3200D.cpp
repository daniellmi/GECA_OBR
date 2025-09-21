#include <Arduino.h>
#include "TCS3200D.h"

TCS3200D::TCS3200D(int s0, int s1, int s2, int s3, int out, int led) {
  color_error = 45;

  red = 0;
  green = 0;
  blue = 0;
  white = 0;

  pinS0 = s0;
  pinS1 = s1;
  pinS2 = s2;
  pinS3 = s3;
  pinOut = out; 
  pinLED = led;
}
void TCS3200D::detectColor() {
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

void TCS3200D::readColor() {
  Serial.print("blue: ");
  Serial.println(blue);

  Serial.print("red: ");
  Serial.println(red);

  Serial.print("green: ");
  Serial.println(green);

  Serial.print("white: ");
  Serial.println(white);
  delay(500);
}
