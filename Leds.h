#ifndef LEDS_H
#define LEDS_H

#define RIGHT_LDR A14
#define LEFT_LDR A15

class Leds {

public: 

int LEFT_GREEN = 51;
int LEFT_RED = 49;
int LEFT_BLUE = 53;

int RIGHT_RED = 48;
int RIGHT_GREEN = 52;
int RIGHT_BLUE = 50;

private:

// int S0;
// int S1;
// int S2;
// int S3;
// int pinOut;
// int pinLed;

// int TCS3200Red;
// int TCS3200Green;
// int TCS3200Blue;
// int TCS3200White;

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

  Leds() {
    colorLeft = "WHITE";
    colorRight = "WHITE";

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

    //***** SENSOR TCS3200 ***** //
      // TCS3200Red = 0;
      // TCS3200Green = 0;
      // TCS3200Blue = 0;
      // TCS3200White = 0;

      // pinMode(S0, OUTPUT);
      // pinMode(S1, OUTPUT);
      // pinMode(S2, OUTPUT);
      // pinMode(S3, OUTPUT);
      // pinMode(pinLed, OUTPUT);
      // pinMode(pinOut, INPUT);

      // digitalWrite(S0, HIGH);
      // digitalWrite(S1, LOW);

      // digitalWrite(pinLed, HIGH);
    //***** ****** ******* ***** //
  }

void calibratingLeds() {

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
        // ****************************** *************************** // 
  }


// void TCS3200() {
//   int pulse = digitalRead(pinOut) == HIGH ? LOW : HIGH;
//   //Vermelho
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, LOW);
//   TCS3200Red = pulseIn(pinOut, pulse);

//   //Branco
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, LOW);
//   TCS3200White = pulseIn(pinOut, pulse);

//   // Azul
//   digitalWrite(S2, LOW);
//   digitalWrite(S3, HIGH);
//   TCS3200Blue = pulseIn(pinOut, pulse);

//   //Verde
//   digitalWrite(S2, HIGH);
//   digitalWrite(S3, HIGH);
//   TCS3200Green = pulseIn(pinOut, pulse);

// }

// String getSensorColor() {

//   if(TCS3200Red < TCS3200Green && TCS3200Red < TCS3200Blue && TCS3200White < 100 ) return "RED";

//   else if(TCS3200Green < TCS3200Red && TCS3200Green < TCS3200Blue && TCS3200White < 100 ) return "GREEN";
  
//   else if(TCS3200Blue < TCS3200Red && TCS3200Blue < TCS3200Green && TCS3200White < 100 ) return "BLUE";

//   return "white";
  
// }
  
};

#endif