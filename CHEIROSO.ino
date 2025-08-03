#include "Motor.h"
#include "Sensor.h"
#include "Leds.h"
#include "Path.h"
#include "Lcd.h"
#include "Accelerometer.h"
#include "TCS3200.h"
#include <Wire.h>

int IR1 = A0;
int IR2 = A1;
int IR3 = A2;
int IR4 = A3;

const int trigPin = 24;
const int echoPin = 22;

unsigned int speed = 50;
unsigned int speed_2 = 100;

unsigned int black_tape = 20;
unsigned int black_tape_2 = 40;
unsigned int color_error = 30;

Motor motor;
Leds leds;
Path path;
Accelerometer acc;
TCS3200 rgb;
Sensor sensor(trigPin, echoPin);
// Lcd lcd(0x27, 16,2);

const int button = 26;
bool pressed = false;
bool lastState = HIGH;

int IR1_value = 0;
int IR2_value = 0;
int IR3_value = 0;
int IR4_value = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  acc.begin();  // calibragem do acelerômetro

  pinMode(button, INPUT_PULLUP);

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

  int state = digitalRead(button);

  if (state == LOW) pressed = !pressed;

  lastState = state;

  if (pressed) {
    digitalWrite(rgb.pinLED, HIGH);

    rgb.detectColor();
    if ((rgb.red + color_error < rgb.green) && (rgb.red < rgb.green) && (rgb.white < 100)) {

      Serial.println("Vermelho"); 
      motor.stop();
      delay(6000);
    }
  } else
    digitalWrite(rgb.pinLED, LOW);

  // *** CASO O ACELERÔMETRO CALCULE UMA VARIAÇÂO NO EIXO Y ( GANGORRA OU RAMPA) *** //
  speed = acc.getY() > 0.20 ? 180 : 60;
  speed_2 = acc.getY() > 0.20 ? 200 : 100;

  // *** |-----------------------------------------------------------------------| *** //

  // |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
  if (sensor.available()) {

    if (sensor.getDistance() <= 5) path.redirectObstacle();
  }

  //  |---------- ------ -- ----- ----------- ----------| //


  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if (isCrossing()) {
    motor.stop();
    delay(200);
    motor.back(80, 80);
    delay(250);

    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(900);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(900);

    // CASO NÃO HAJA FITA VERDE, O ROBÔ CONTINUA ANDANDO NUM DELAY ATÉ DEIXAR O CRUZAMENTO
    else {
      motor.go(100, 100);
      delay(500);
    }
  }
  //  |---------- ------ -- --------- ----------| //


  //     |---------- LÓGICA DAS CURVAS DE 90 GRAUS ----------| //

  else if (IR1_value > black_tape && IR2_value > black_tape) {

    //      ***VERIFICA SE É INTERSEÇÂO***     //
    path.intersection(350);

    if (max(path.max_IR2, path.max_IR3) > 500) {
      motor.right(250, 250);
      motor.go(65, 65);

      path.max_IR2 = 0;
      path.max_IR3 = 0;
    }

    else
      path.turnOnLeft90(500);
  }

  else if (IR3_value > black_tape_2 && IR4_value > black_tape_2) {
    //
    //      ***VERIFICA SE É INTERSEÇÂO***     //
    path.intersection(350);

    if (max(path.max_IR2, path.max_IR3) > 500) {
      motor.left(250, 250);
      motor.go(65, 65);

      path.max_IR2 = 0;
      path.max_IR3 = 0;
    }

    else
      path.turnOnRight90(500);
  }
  //     |---------- ------ --- ----- -- -- ----- ----------| //

  // ****CURVA LEVE PARA  A ESQUERDA**** //
  else if (IR1_value > black_tape) {
    motor.left90(speed_2);
    delay(250);
  }

  else if (IR2_value > black_tape) {
    motor.left90(speed_2);
    delay(120);
  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (IR3_value > black_tape_2) {
    motor.right90(speed_2);
    delay(120);
  }

  else if (IR4_value > black_tape_2) {
    motor.right90(speed_2);
    delay(250);
  }

  else
    motor.go(speed, speed);
}

bool isCrossing() {
  return IR1_value > 20 && IR4_value > 40;
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

void readLDRS() {
  Serial.print("LDR 1: ");
  Serial.println(analogRead(A14));
  Serial.print("LDR 2: ");
  Serial.println(analogRead(A15));
  delay(500);
}
