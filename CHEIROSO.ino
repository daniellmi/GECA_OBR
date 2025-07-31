#include "Motor.h"
#include "Sensor.h"
#include "Leds.h"
#include "Path.h"
#include "Lcd.h"
#include "Accelerometer.h"
#include <Wire.h>

#define pinLed 45

int IR1 = A0;
int IR2 = A1;
int IR3 = A2;
int IR4 = A3;

const int trigPin = 24;
const int echoPin = 22;

unsigned int speed = 60;
unsigned int speed_2 = 100;
unsigned int black_tape = 500;

Motor motor;
Leds leds;
Path path;
Sensor sensor(trigPin,echoPin);
// Lcd lcd(0x27, 16,2);
Accelerometer acc;

void setup() { 
  Serial.begin(9600);
  Wire.begin();
  acc.begin(); // calibra acelerometro
  
  leds.calibratingLeds();
  delay(100);
  leds.calibratingLeds();

  }

void loop() {
// Serial.println(leds.getSensorColor());
//  delay(600);
//   lcd.displayColor("WHITE", "WHITE");

  leds.TCS3200();

  // *** CASO O ACELERÔMETRO CALCULE UMA VARIAÇÂO NO EIXO Y ( GANGORRA OU RAMPA) *** //
  speed = acc.getY() > 0.20 ? 180 : 70;
  speed_2 = acc.getY() > 0.20 ? 130 : 100;

  // *** |-----------------------------------------------------------------------| *** //

 //  |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
      if(sensor.available()) { 
        
      if(sensor.getDistance() < 12)
      path.redirectObstacle();
      }
      
//  |---------- ------ -- ----- ----------- ----------| //


  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
    if(isCrossing()) {

      motor.stop();
      delay(200);
      motor.back(70, 70);

      leds.ReadLdrOnGreen();
 
      // lcd.displayColor(leds.colorRight, leds.colorLeft);

      if(leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();
    
      else if(leds.colorLeft.equals("GREEN")) path.turnOnLeft90();
      
      else if(leds.colorRight.equals("GREEN")) path.turnOnRight90();
     
      // CASO NÃO HAJA FITA VERDE, O ROBÔ CONTINUA ANDANDO NUM DELAY ATÉ DEIXAR O CRUZAMENTO
     else {
     motor.go(120,120);
     delay(500);
     }
  } 
    //  |---------- ------ -- --------- ----------| //


  //     |---------- LÓGICA DAS CURVAS DE 90 GRAUS ----------| //

     else if (analogRead(IR1) > 400 && analogRead(IR2) > 400) {

//      ***VERIFICA SE É INTERSEÇÂO***     //
       path.intersection(350);
      
      if(max(path.max_IR2,path.max_IR3) > black_tape) {    
       motor.right(250,250);
       motor.go(65,65);

       path.max_IR2 = 0; 
       path.max_IR3 = 0; 
      }

      else 
      path.turnOnLeft90();

    }

     else if(analogRead(IR3) > 500 && analogRead(IR4) > 500) {

//      ***VERIFICA SE É INTERSEÇÂO***     //
      path.intersection(350);

      if(max(path.max_IR2, path.max_IR3) > black_tape) {
       motor.left(250,250);
       motor.go(65,65);

       path.max_IR2 = 0; 
       path.max_IR3 = 0; 
      }

     else 
     path.turnOnRight90();
  
      
     }
 //     |---------- ------ --- ----- -- -- ----- ----------| //
    
  // ****CURVA LEVE PARA  A ESQUERDA**** //
   else if (analogRead(IR1) > black_tape || analogRead(IR2) > black_tape) {
    motor.left90(speed_2);
    delay(150);
  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (analogRead(IR3) > black_tape || analogRead(IR4) > black_tape) {
    motor.right90(speed_2);
    delay(150);
  } 

  else  
  motor.go(speed,speed);

 }

 bool isCrossing() {
  return analogRead(IR1) > black_tape - 100 && analogRead(IR4) > black_tape; 
 }

 void readIRS() {
  Serial.print("IR1: ");
  Serial.println(analogRead(IR1));

  Serial.print("IR2: ");
  Serial.println(analogRead(IR2));

  Serial.print("IR3: ");
  Serial.println(analogRead(IR3));

  Serial.print("IR4: ");
  Serial.println(analogRead(IR4));
  delay(500);
  }