#include <Motor.h>
#include <Path.h>
#include <InfraRed.h>
#include <Leds.h>
#include <Sensor.h>
#include <Accelerometer.h>
#include <TCS3200.h>
#include <Button.h>
#include <Servo.h>
#include <Wire.h>

const int trigPin = 24;
const int echoPin = 22;

unsigned int speed = 0;
unsigned int speed_2 = 0;

unsigned int black_tape = 45;    // valor mapeado dos infravermelhos esquerdos na linha preta
unsigned int black_tape_2 = 55;  // valor mapeado dos infravermelhos direitos na linha preta

// -- CALCULA O TEMPO PARA CURVAS LEVES NA LINHA -- //
unsigned long lastTime_right = 0;
unsigned long lastTime_right_300 = 0;
unsigned long lastTime_left = 0;
unsigned long lastTime_left_300 = 0;

bool rescue = false;
float standard_acc_value = 0.04;

Motor motor;
InfraRed infra;
Leds leds;
Path path;
Accelerometer acc;
TCS3200 rgb;
Servo servo;
Sensor ultra(trigPin, echoPin);
Button led_button(26);   // LED
Button claw_button(28);  // garra

void setup() {
  Serial.begin(9600);
  Wire.begin();
  servo.attach(30);
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

  infra.mapInfraRed();
  if (!rescue) servo.write(100);

  // *** -- LÓGICA DO BOTÃO PARA ACENDER TCS3200-- *** //
  if (led_button.isPressed()) {

    digitalWrite(rgb.pinLED, HIGH);
    rgb.detectColor();

    if (rgb.getColor().equals("RED")) {
      motor.stop();
      delay(7000);
    }
  }

  else
    digitalWrite(rgb.pinLED, LOW);
  // *** -- ****** ** ***** -- *** //

  // COLOCAR AQUI A LÓGICA DO RESGATE (ACHAR PARÂMETRO PARA DETECTAR ARENA)
  if (claw_button.isPressed() && rescue) {
    servo.write(100);
    motor.back(100, 100);
    delay(3000);
    motor.left(100, 100);
    delay(3000);
    // button_2.pressed = false;
  }

  else if (!claw_button.isPressed() && rescue) servo.write(0);
  // -----------------------------------------------------------------------

  // *** CASO O ACELERÔMETRO CALCULE UMA VARIAÇÂO NO EIXO Y ( GANGORRA OU RAMPA) *** //
  speed = acc.getY() > 0.22 ? 160 : 60;
  speed_2 = acc.getY() > 0.22 ? 120 : 100;

  // ROBÔ DÁ UM IMPULSO AO FIM DA GANGORRA, EVITANDO LEITURAS INDESEJADAS
  if (infra.IR2_value > black_tape && infra.IR3_value > black_tape_2 && acc.getY() > 0.22) {
    motor.go(120, 120);
    delay(700);
  }
  // *** |-----------------------------------------------------------------------| *** //

  // |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
  if (ultra.available())
    if (ultra.getDistance() < 5) path.redirectObstacle();

  //  |---------- ------ -- ----- ----------- ----------| //

  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if (infra.IR1_value > black_tape && infra.IR4_value > black_tape_2 + 15 && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(1200);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(1200);

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

  else if (infra.IR1_value > black_tape && infra.IR2_value > black_tape && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(1200);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(1200);

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

  else if (infra.IR3_value > black_tape_2 + 15 && infra.IR4_value > black_tape_2 + 15 && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) path.turnOnLeft90(1200);

    else if (leds.colorRight.equals("GREEN")) path.turnOnRight90(1200);

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
  else if (infra.IR1_value > black_tape - 10 && acc.getY() < standard_acc_value) {

    unsigned long m = millis();

    if (m - lastTime_left_300 >= 450) {
      motor.left90(speed_2);
      lastTime_left_300 = m;
    }
  }

  else if (infra.IR2_value > black_tape) {

    unsigned long m = millis();

    if (m - lastTime_left >= 150) {
      motor.left90(speed_2);
      lastTime_left = m;
    }

  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (infra.IR3_value > black_tape_2) {

    unsigned long m = millis();

    if (m - lastTime_right >= 150) {
      motor.right90(speed_2);
      lastTime_right = m;
    }

  }

  else if (infra.IR4_value > black_tape_2 && acc.getY() < standard_acc_value) {
    unsigned long m = millis();

    if (m - lastTime_right_300 >= 450) {
      motor.right90(speed_2);
      lastTime_right_300 = m;
    }
  }

  else
    motor.go(speed, speed);
}

void readColor() {
  digitalWrite(rgb.pinLED, HIGH);
  rgb.detectColor();
  Serial.println(rgb.getColor());
  delay(400);
}

void readLDRS() {
  Serial.print("LDR 1: ");
  Serial.println(analogRead(A14));
  Serial.print("LDR 2: ");
  Serial.println(analogRead(A15));
  delay(500);
}