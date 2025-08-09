#include "Motor.h"
#include "Sensor.h"
#include "Leds.h"
#include "Path.h"
#include "Lcd.h"
#include "Accelerometer.h"
#include "TCS3200.h"
#include "Button.h"

#include <Servo.h>
#include <Wire.h>

int IR1 = A0;
int IR2 = A1;
int IR3 = A2;
int IR4 = A3;

const int trigPin = 24;
const int echoPin = 22;

unsigned int speed = 0;
unsigned int speed_2 = 0;

unsigned int black_tape = 45;    // valor mapeado dos infravermelhos esquerdos na linha preta
unsigned int black_tape_2 = 45;  /// valor mapeado dos infravermelhos direitos na linha preta
unsigned int color_error = 30;

// -- CALCULA O TEMPO PARA CURVAS LEVES NA LINHA -- //
unsigned long lastTime_right = 0;
unsigned long lastTime_right_300 = 0;

unsigned long lastTime_left = 0;
unsigned long lastTime_left_300 = 0;

// ** VALORES DOS IR'S A SEREM MAPEADOS ** //
int IR1_value = 0;
int IR2_value = 0;
int IR3_value = 0;
int IR4_value = 0;

bool rescue = false;

Motor motor;
Leds leds;
Path path;
Accelerometer acc;
TCS3200 rgb;
Servo servo;
Sensor sensor(trigPin, echoPin);
Button button_1(26);  // LED
Button button_2(30);  // garra
// Lcd lcd(0x27, 16,2);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  servo.attach(28);
  acc.begin();  // calibragem do acelerômetro

  pinMode(rgb.pinS0, OUTPUT);
  pinMode(rgb.pinS1, OUTPUT);
  pinMode(rgb.pinS2, OUTPUT);
  pinMode(rgb.pinS3, OUTPUT);
  pinMode(rgb.pinLED, OUTPUT);
  pinMode(rgb.pinOut, INPUT);

  digitalWrite(rgb.pinS0, HIGH);
  digitalWrite(rgb.pinS1, LOW);

  delay(1000);
  digitalWrite(rgb.pinLED, LOW);
  delay(200);

  // ** CALIBRAGEM DOS LDR's ** //
  leds.calibratingLeds();
  delay(100);
  leds.calibratingLeds();
  delay(200);
}

void loop() {

  IR1_value = map(analogRead(IR1), 0, 1023, 0, 100);
  IR2_value = map(analogRead(IR2), 0, 1023, 0, 100);
  IR3_value = map(analogRead(IR3), 0, 1023, 0, 100);
  IR4_value = map(analogRead(IR4), 0, 1023, 0, 100);

  if (!rescue) servo.write(100);

  sensor.availability(false);
  if (millis() > 15000) sensor.availability(true);

  // COLOCAR AQUI A LÓGICA DO RESGATE (ACHAR PARÂMETRO PARA DETECTAR ARENA)
  if (button_2.isPressed() && rescue) {
    servo.write(100);
    motor.back(100, 100);
    delay(3000);
    motor.left(100, 100);
    delay(3000);

    button_2.pressed = false;

  } else if (!button_2.isPressed() && rescue)
    servo.write(0);

  // *** -- LÓGICA DO BOTÃO -- *** //

  if (button_1.isPressed()) {
    digitalWrite(rgb.pinLED, HIGH);

    rgb.detectColor();
    if ((rgb.red + color_error < rgb.green) && (rgb.red < rgb.green) && (rgb.white < 100)) {

      Serial.println("Red");
      motor.stop();
      delay(6000);
    }
  } else
    digitalWrite(rgb.pinLED, LOW);
  // *** -- ****** ** ***** -- *** //

  // *** CASO O ACELERÔMETRO CALCULE UMA VARIAÇÂO NO EIXO Y ( GANGORRA OU RAMPA) *** //
  speed = acc.getY() > 0.22 ? 190 : 60;
  speed_2 = acc.getY() > 0.22 ? 130 : 100;

  // *** |-----------------------------------------------------------------------| *** //

  // |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
  if (sensor.available())
    if (sensor.getDistance() <= 5) path.redirectObstacle();

  //  |---------- ------ -- ----- ----------- ----------| //

  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if (analogRead(IR1) > 450 && analogRead(IR4) > 600) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(900);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(900);

    // CASO NÃO HAJA FITA VERDE, O ROBÔ CONTINUA ANDANDO ATÉ DEIXAR O CRUZAMENTO
    else {
      motor.go(100, 100);
      delay(500);
    }
    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }
  //  |---------- ------ -- --------- ----------| //


  //     |---------- LÓGICA DAS CURVAS DE 90 GRAUS ----------| //

  else if (analogRead(IR1) > 600 && analogRead(IR2) > 600 && analogRead(IR4) < 450) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(900);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(900);

    else {
      motor.go(80, 80);
      delay(250);
      //      ***VERIFICA SE É INTERSEÇÂO***     //
      path.intersection(350);

      if (max(path.max_IR2, path.max_IR3) > 500) {
        motor.right(250, 250);
        motor.go(65, 65);

        path.max_IR2 = 0;
        path.max_IR3 = 0;
      }

      else
        path.turnOnLeft90(900);
    }
    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }

  else if (analogRead(IR3) > 600 && analogRead(IR4) > 600) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(900);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(900);

    else {
      motor.go(80, 80);
      delay(250);
      //      ***VERIFICA SE É INTERSEÇÂO***     //
      path.intersection(350);

      if (max(path.max_IR2, path.max_IR3) > 500) {
        motor.left(250, 250);
        motor.go(65, 65);

        path.max_IR2 = 0;
        path.max_IR3 = 0;
      }

      else
        path.turnOnRight90(900);
    }
    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }
  //     |---------- ------ --- ----- -- -- ----- ----------| //

  // ****CURVA LEVE PARA  A ESQUERDA**** //
  else if (IR1_value > black_tape) {

    unsigned long m = millis();

    if (m - lastTime_left_300 >= 500) {
      motor.left90(speed_2);
      lastTime_left_300 = m;
    }
  }

  else if (IR2_value > black_tape) {

    unsigned long m = millis();

    if (m - lastTime_left >= 150) {
      motor.left90(speed_2);
      lastTime_left = m;
    }
  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (IR3_value > black_tape_2) {

    unsigned long m = millis();

    if (m - lastTime_right >= 150) {
      motor.right90(speed_2);
      lastTime_right = m;
    }

  }

  else if (IR4_value > black_tape_2) {
    unsigned long m = millis();

    if (m - lastTime_right_300 >= 500) {
      motor.right90(speed_2);
      lastTime_right_300 = m;
    }
  }

  else
    motor.go(speed, speed);
}

void readIRS() {
  Serial.print("IR1: ");
  Serial.println(IR1_value);

  Serial.print("IR2: ");
  Serial.println(IR2_value);

  Serial.print("IR3: ");
  Serial.println(IR3_value);

  Serial.print("IR4: ");
  Serial.println(IR4_value);
  delay(500);
}

void readLDRS() {
  Serial.print("LDR 1: ");
  Serial.println(analogRead(A14));
  Serial.print("LDR 2: ");
  Serial.println(analogRead(A15));
  delay(500);
}