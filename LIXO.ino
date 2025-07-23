#include "Motor.h"
#include "Sensor.h"
#include "Leds.h"
#include "Functions.h"

#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3

const int trigPin = 22;
const int echoPin = 24;

int IR2ValueForIntersection = 0; // valor do IR2 na fita durante a interseção
int IR3ValueForIntersection = 0; // valor do IR3 na fita durante a interseção

// valores máximos encontrado pelos infravermelhos centrais 
int max = 0; 
int max2 = 0;

Motor motor;
Leds leds;
Sensor sensor(trigPin,echoPin);
Functions functions;

void Functions::intersection(int d) {
        int count = 1;

        motor.go(100,100);
        delay(400);
        motor.stop();
        delay(200);

    do{
          motor.left(100,100);
          delay(d); 
          motor.right(100,100);
          delay(d); 

          IR3ValueForIntersection = analogRead(IR3);
          IR2ValueForIntersection = analogRead(IR2);

          if(max < IR3ValueForIntersection ) max = IR3ValueForIntersection;
          if(max2 < IR2ValueForIntersection) max2 = IR2ValueForIntersection;
        ++count;
        }
        while(count <= 3);
}

void Functions::redirectObstacle() {
  motor.right(100,100);
  delay(1000);
  motor.go(100,100);
  delay(5000);
  motor.left(120,120);
  delay(2750);
  motor.go(120,120);
  delay(3200);
  motor.right(100,100);
  delay(1400);
  motor.back(100,100);
  delay(600);
}

void Functions::turOnRight90() {
        motor.go(100,100);
        delay(1200);

        while(true) {
          motor.right(100, 100);
          if(analogRead(IR3) > 500) break;
        }

        motor.back(100,100);
        delay(250);
}

void Functions::turnOnLeft90() {
        motor.go(100,100);
        delay(1200);

        while(true) {
          motor.left(100, 100);
          if(analogRead(IR2) > 500) break;
        }

        motor.back(100,100);
        delay(250);
}

void Functions::fullTurn() {
      motor.right(120, 100);
      delay(1000);

        while(true) {
          motor.right(200, 140);
          if(analogRead(IR3) > 500) break;
        }
}

void setup() { 
  Serial.begin(9600);
  
  leds.calibratingLeds();
  delay(100);
  leds.calibratingLeds();
}



void loop() {

 //  |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
      if(sensor.readtSensor() <= 6) 
        functions.redirectObstacle();
//  |---------- ------ -- ----- ----------- ----------| //

  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if(analogRead(IR1) > 600 && analogRead(IR4) > 600) {

      motor.stop();
      delay(200);
      motor.back(40, 40);
      leds.ReadLdrOnGreen();
      delay(200);
      leds.ReadLdrOnGreen();  
      delay(200);
      leds.ReadLdrOnGreen();      

      if(leds.colorLeft == 'G' && leds.colorRight == 'G') functions.fullTurn();
    
      else if(leds.colorLeft == 'G') functions.turnOnLeft90();
      
      else if(leds.colorRight == 'G') functions.turOnRight90();
     
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
    functions.intersection(350);
      
      if(max > 500 || max2 > 500) {
       motor.right(250,250);
       motor.go(65,65);
       max = 0; 
       max2 = 0; 
      }

      else 
      functions.turnOnLeft90();
      
    }


     else if(analogRead(IR3) > 600 && analogRead(IR4) > 600 && analogRead(IR1) < 450) {

//      ***VERIFICA SE É INTERSEÇÂO***     //
     functions.intersection(350);

      if(max > 500 || max2 > 500) {
       motor.left(250,250);
       motor.go(65,65);
       max = 0; 
       max2 = 0; 
      }

     else 
     functions.turOnRight90();

      
     }
 //     |---------- ------ --- ----- -- -- ----- ----------| //

  // ****CURVA LEVE PARA  A ESQUERDA****
   else if (analogRead(IR1) > 500 || analogRead(IR2) > 500) {
    motor.left90(100);
    delay(150);
  }

  // ****CURVA LEVE PARA  A DIREITA****
  else if (analogRead(IR3) > 500 || analogRead(IR4) > 500) {
    motor.right90(100);
    delay(150);
  }

  else 
  motor.go(80, 80);

 }

