#ifndef LEDS_H
#define LEDS_H

#define LEFT_GREEN 51
#define LEFT_RED 49 
#define LEFT_BLUE 53

#define RIGHT_RED 48
#define RIGHT_GREEN 52
#define RIGHT_BLUE 50

#define RIGHT_LDR A14
#define LEFT_LDR A15

class Leds {

// |--- VALORES DAS LEDS ESQUERDAS NO BRANCO ---|
int LEFT_RED_WHITE_VALUE; 
int LEFT_GREEN_WHITE_VALUE; 
int LEFT_BLUE_WHITE_VALUE;

// |--- VALORES DAS LEDS DIREITAS NO BRANCO ---|
int RIGHT_RED_WHITE_VALUE;
int RIGHT_GREEN_WHITE_VALUE; 
int RIGHT_BLUE_WHITE_VALUE; 

public: 
char colorRight;
char colorLeft;

  Leds() {
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

void calibratingLeds() {

  digitalWrite(LEFT_RED, LOW);
  digitalWrite(RIGHT_RED, LOW);
  delay(100);
  LEFT_RED_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_RED_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(1000);
  digitalWrite(LEFT_RED, HIGH);
  digitalWrite(RIGHT_RED, HIGH);

  digitalWrite(LEFT_GREEN, LOW);
  digitalWrite(RIGHT_GREEN, LOW);
  delay(100);
  LEFT_GREEN_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_GREEN_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(1000);
  digitalWrite(LEFT_GREEN, HIGH);
  digitalWrite(RIGHT_GREEN, HIGH);

  digitalWrite(LEFT_BLUE, LOW);
  digitalWrite(RIGHT_BLUE, LOW);
  delay(100);
  LEFT_BLUE_WHITE_VALUE = analogRead(LEFT_LDR);
  RIGHT_BLUE_WHITE_VALUE = analogRead(RIGHT_LDR);
  delay(1000);
  digitalWrite(LEFT_BLUE, HIGH);
  digitalWrite(RIGHT_BLUE, HIGH);
}

void ReadLdrOnGreen() {
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

  if (valueSubtractionLED1G < valueSubtractionLED1R && valueSubtractionLED1G < valueSubtractionLED1B) {

    //**************************COMPARANDO VALORES DOS VALORES DO LED1**********************
   int Subtraction_Subtraction1D = valueSubtractionLED1R - valueSubtractionLED1G;
   int Subtraction_Subtraction2D = valueSubtractionLED1B - valueSubtractionLED1G;
   int average1 = (Subtraction_Subtraction1D + Subtraction_Subtraction2D) / 2;

    if (average1 > 20)
      colorRight = 'G';
    
  else 
    colorRight = 'W';
  
  }
  if (valueSubtractionLED2G < valueSubtractionLED2R && valueSubtractionLED2G < valueSubtractionLED2B) {

    //**************************COMPARANDO VALORES DO LED2**********************
   int Subtraction_Subtraction1E = valueSubtractionLED2R - valueSubtractionLED2G;
   int Subtraction_Subtraction2E = valueSubtractionLED2B - valueSubtractionLED2G;
   int average2 = (Subtraction_Subtraction1E + Subtraction_Subtraction2E) / 2;

    if (average2 > 20) 
      colorLeft = 'G';
   
  else 
    colorLeft = 'W';

}
  }
};

#endif