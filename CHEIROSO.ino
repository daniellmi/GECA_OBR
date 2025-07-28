#include "Motor.h"
#include "Sensor.h"
#include "Leds.h"
#include "Path.h"
#include "Lcd.h"

int IR1 = A0;
int IR2 = A1;
int IR3 = A2;
int IR4 = A3;

const int trigPin = 24;
const int echoPin = 22;

Motor motor;
Leds leds;
Path path;
Sensor sensor(trigPin,echoPin);
Lcd lcd(0x27, 16,2);

void setup() { 
  Serial.begin(9600);

  lcd.begin();
  leds.calibratingLeds();
  delay(100);
  leds.calibratingLeds();
}

void loop() {

     lcd.displayColor("WHITE", "WHITE");
  //  |---------- *** **** ******* *** ----------| //


 //  |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
      if(sensor.getDistance() < 12) 
        path.redirectObstacle();
//  |---------- ------ -- ----- ----------- ----------| //


  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if(analogRead(IR1) > 600 && analogRead(IR4) > 600) {

      motor.stop();
      delay(200);
      motor.back(40, 40);

      leds.ReadLdrOnGreen();
      delay(200);
      leds.ReadLdrOnGreen();  
      lcd.displayColor(leds.colorRight, leds.colorLeft);

      if(leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();
    
      else if(leds.colorLeft.equals("GREEN")) path.turnOnLeft90();
      
      else if(leds.colorRight.equals("GREEN")) path.turnOnRight90();
     
      // CASO NÃO HAJA FITA VERDE, O ROBÔ CONTINUA ANDANDO NUM DELAY ATÉ DEIXAR O CRUZAMENTO
     else {
     motor.go(100,100);
     delay(300);
     }
  } 
    //  |---------- ------ -- --------- ----------| //


  //     |---------- LÓGICA DAS CURVAS DE 90 GRAUS ----------| //

     else if (analogRead(IR1) > 600 && analogRead(IR2) > 600 && analogRead(IR4) < 450) {

//      ***VERIFICA SE É INTERSEÇÂO***     //
      path.intersection(350);
      
      if(max(path.max_IR2,path.max_IR3) > 500) {    
       motor.right(250,250);
       motor.go(65,65);

       path.max_IR2 = 0; 
       path.max_IR3 = 0; 
      }

      else 
      path.turnOnLeft90();
      
    }

     else if(analogRead(IR3) > 600 && analogRead(IR4) > 600 && analogRead(IR1) < 450) {

//      ***VERIFICA SE É INTERSEÇÂO***     //
      path.intersection(350);

      if(max(path.max_IR2, path.max_IR3) > 500) {
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
   else if (analogRead(IR1) > 500 || analogRead(IR2) > 500) {
    motor.left90(100);
    delay(150);
  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (analogRead(IR3) > 500 || analogRead(IR4) > 500) {
    motor.right90(100);
    delay(150);
  } 

  else 
  motor.go(70,70);

 }