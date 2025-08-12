#include <Arduino.h>
#include "Leds.h"

Leds::Leds() {

  colorLeft = "WHITE";
  colorRight = "WHITE";

  LEFT_GREEN = 51;
  LEFT_RED = 49;
  LEFT_BLUE = 53;

  RIGHT_RED = 48;
  RIGHT_GREEN = 52;
  RIGHT_BLUE = 50;


  LEFT_RED_WHITE_VALUE = 0;
  LEFT_GREEN_WHITE_VALUE = 0;
  LEFT_BLUE_WHITE_VALUE = 0;

  RIGHT_RED_WHITE_VALUE = 0;
  RIGHT_GREEN_WHITE_VALUE = 0;
  RIGHT_BLUE_WHITE_VALUE = 0;

  pinMode(RIGHT_RED, OUTPUT);
  pinMode(RIGHT_GREEN, OUTPUT);
  pinMode(RIGHT_BLUE, OUTPUT);

  pinMode(LEFT_RED, OUTPUT);
  pinMode(LEFT_GREEN, OUTPUT);
  pinMode(LEFT_BLUE, OUTPUT);

  digitalWrite(RIGHT_LDR, HIGH);
  digitalWrite(LEFT_LDR, HIGH);

  //desligar leds inicialmente
  digitalWrite(RIGHT_RED, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);
  digitalWrite(RIGHT_BLUE, HIGH);
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(LEFT_BLUE, HIGH);
}
void Leds::calibratingLeds() {

  digitalWrite(LEFT_RED, LOW);
  digitalWrite(RIGHT_RED, LOW);
  delay(100);
  LEFT_RED_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_RED_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(10);
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(RIGHT_RED, HIGH);

  digitalWrite(LEFT_GREEN, LOW);
  digitalWrite(RIGHT_GREEN, LOW);
  delay(100);
  LEFT_GREEN_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_GREEN_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(10);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);

  digitalWrite(LEFT_BLUE, LOW);
  digitalWrite(RIGHT_BLUE, LOW);
  delay(100);
  LEFT_BLUE_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_BLUE_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(10);
  digitalWrite(LEFT_BLUE, HIGH);
  digitalWrite(RIGHT_BLUE, HIGH);
}

void Leds::ReadLdrOnGreen() {
  digitalWrite(LEFT_RED, LOW);
  digitalWrite(RIGHT_RED, LOW);
  delay(100);
  int valueLED1RC = analogRead(RIGHT_LDR);
  int valueLED2RC = analogRead(LEFT_LDR);
  delay(10);
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(RIGHT_RED, HIGH);

  digitalWrite(LEFT_GREEN, LOW);
  digitalWrite(RIGHT_GREEN, LOW);
  delay(100);
  int valueLED1GC = analogRead(RIGHT_LDR);
  int valueLED2GC = analogRead(LEFT_LDR);
  delay(10);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);

  digitalWrite(LEFT_BLUE, LOW);
  digitalWrite(RIGHT_BLUE, LOW);
  delay(100);
  int valueLED1BC = analogRead(RIGHT_LDR);
  int valueLED2BC = analogRead(LEFT_LDR);
  delay(10);
  digitalWrite(LEFT_BLUE, HIGH);
  digitalWrite(RIGHT_BLUE, HIGH);

  //**************************COMPARANDO VALORES DO LED1**********************
  int valueSubtractionLED1R = valueLED1RC - RIGHT_RED_WHITE_VALUE;
  int valueSubtractionLED1G = valueLED1GC - RIGHT_GREEN_WHITE_VALUE;
  int valueSubtractionLED1B = valueLED1BC - RIGHT_BLUE_WHITE_VALUE;
  //**************************COMPARANDO VALORES DO LED2**********************
  int valueSubtractionLED2R = valueLED2RC - LEFT_RED_WHITE_VALUE;
  int valueSubtractionLED2G = valueLED2GC - LEFT_GREEN_WHITE_VALUE;
  int valueSubtractionLED2B = valueLED2BC - LEFT_BLUE_WHITE_VALUE;


  // **************************FITA VERDE********************** //
  if (valueSubtractionLED1G < valueSubtractionLED1R && valueSubtractionLED1G < valueSubtractionLED1B) {

    //**************************COMPARANDO VALORES DOS VALORES DO LED1**********************
    int Subtraction_Subtraction1D = valueSubtractionLED1R - valueSubtractionLED1G;
    int Subtraction_Subtraction2D = valueSubtractionLED1B - valueSubtractionLED1G;
    int average = (Subtraction_Subtraction1D + Subtraction_Subtraction2D) / 2;

    colorRight = average > 20 ? "GREEN" : "WHITE";
  }

  if (valueSubtractionLED2G < valueSubtractionLED2R && valueSubtractionLED2G < valueSubtractionLED2B) {

    //**************************COMPARANDO VALORES DO LED2**********************
    int Subtraction_Subtraction1E = valueSubtractionLED2R - valueSubtractionLED2G;
    int Subtraction_Subtraction2E = valueSubtractionLED2B - valueSubtractionLED2G;
    int average = (Subtraction_Subtraction1E + Subtraction_Subtraction2E) / 2;

    colorLeft = average > 20 ? "GREEN" : "WHITE";
  }

  // **************************FITA VERMELHA********************** //
  if (valueSubtractionLED1R < valueSubtractionLED1G && valueSubtractionLED1R < valueSubtractionLED1B) {
    colorRight = "RED";
  }

  if (valueSubtractionLED2R < valueSubtractionLED2G && valueSubtractionLED2R < valueSubtractionLED2B) {
    colorLeft = "RED";
  }
  // ****************************** *************************** //
}
