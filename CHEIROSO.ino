#include <Motor.h>
#include <Path.h>
#include <InfraRed.h>
#include <Leds.h>
#include <Sensor.h>
#include <Accelerometer.h>
#include <TCS3200D.h>
#include <Button.h>
#include <Servo.h>
#include <Wire.h>


#define IR4 A3
#define IR1 A0
#define IR2 A1
#define IR3 A2

#define IR5_CLAW A8

// const int trigPin = 24;
// const int echoPin = 22;

// const int lateralTrigPin = 33;
// const int lateralEchoPin = 35;

unsigned int speed = 0;
unsigned int speed_2 = 0;

unsigned int black_tape = 500;
unsigned int black_tape_2 = 550;
float standard_acc_value = 0.06;


// ++ VÁRIÁVEIS DO RESGATE ++ //rgb
bool rescue = false;
int seconds = 0;
int interval = 1000;  // 1 segundo
unsigned long lastM = 0;

Motor motor;
InfraRed infra;
Leds leds;
Path path;
Accelerometer acc;
TCS3200D rgb(47, 43, 39, 37, 41, 45);
// TCS3200D rescue_rgb(36, 38, 44, 42, 46, 40);
// Servo servo;
// Servo miniServo;
// Sensor ultra(trigPin, echoPin);
Button button(28);                 // garra
TurnDirection currentTurn = NONE;  // enum

bool turning = false;
unsigned long turnStart = 0;
int turnDuration = 0;

void startTurn(TurnDirection direction, int duration, int speed) {
  turning = true;
  turnStart = millis();
  turnDuration = duration;
  currentTurn = direction;

  switch (direction) {
    case LEFT:
      motor.left90(speed);
      break;
    case RIGHT:
      motor.right90(speed);
      break;
    case EXLEFT:
      motor.left(speed, speed);
      break;
    case EXRIGHT:
      motor.right(speed, speed);
  }
}

void updateTurn(int speed, int speed2) {
  if (turning && millis() - turnStart >= turnDuration) {
    turning = false;
    currentTurn = NONE;
    motor.go(speed, speed2);
  }
}
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  acc.begin();  // calibragem do acelerômetro
  // servo.attach(3);
  // miniServo.attach(5);

  pinMode(rgb.pinS0, OUTPUT);
  pinMode(rgb.pinS1, OUTPUT);
  pinMode(rgb.pinS2, OUTPUT);
  pinMode(rgb.pinS3, OUTPUT);
  pinMode(rgb.pinLED, OUTPUT);
  pinMode(rgb.pinOut, INPUT);
  digitalWrite(rgb.pinS0, HIGH);
  digitalWrite(rgb.pinS1, LOW);

  delay(100);
  digitalWrite(rgb.pinLED, LOW);
  delay(200);

  // ** CALIBRAGEM DOS LDR's ** //
  leds.calibratingLeds();
  delay(100);
  leds.calibratingLeds();
  delay(200);

  lastMillis = millis();
}

void loop() {
  digitalWrite(rgb.pinLED, HIGH);
  rgb.detectColor();


  // if (rescue) {
  //   // motor.back(100, 100);
  //   // delay(2000);

  //   while (true) {
  //     // AQUI A LÓGICA PARA LER A COR CASO SEJA UM TRIÂNGULO
  //     digitalWrite(rescue_rgb.pinLED, HIGH);
  //     rescue_rgb.detectColor();
  //     motor.go(110, 110);

  //     if (claw_button.isPressed()) {
  //       motor.back(100, 100);
  //       delay(1000);

  //       int startAngle = servo.read();   //armazena ultimo valor enviado pelo servo.write();
  //       for (int i = startAngle; i <= 140; i++) {
  //         servo.write(i);
  //         delay(15);
  //       }

  //       // motor.go(80, 80);
  //       delay(500);

  //       startAngle = servo.read();
  //       int safeTop = 20;
  //       for (int i = startAngle; i >= safeTop; i--){
  //         servo.write(i);
  //         delay(15);
  //       }
  //       motor.go(80, 80);
  //       delay(1500);
  //     }
  //       //  LÊ A COR ( CASO SEJA TRIANGULO )
  //       if (rescue_rgb.red + 100 < rescue_rgb.green && rescue_rgb.red + 100 < rescue_rgb.blue) {

  //           motor.back(100, 100);
  //           delay(2000);

  //           motor.left(120, 120);
  //           delay(2400);

  //           miniServo.write(0);
  //           delay(500);

  //           motor.stop();
  //           delay(3000);
  //         }
  //     else {
  //       servo.write(20);
  //     }
  //   }
  // }

  // -- LóGICA DO GAP / ÁREA DE RESGATE -- //
  if (analogRead(IR1) < 300 && analogRead(IR2) < 300 && analogRead(IR3) < 550) {

    if ((rgb.red + rgb.color_error < rgb.green) && (rgb.red + rgb.color_error < rgb.blue) && (rgb.white < 100)) {
      motor.stop();
      delay(5500);
    }
  }

  // -----------------------------------------------------------------------
  // *** CASO O ACELERÔMETRO CALCULE UMA VARIAÇÂO NO EIXO Y ( GANGORRA OU RAMPA) *** //
  speed = acc.getY() > 0.23 ? 200 : 130;
  speed_2 = acc.getY() > 0.23 ? 220 : 100;

  // ROBÔ DÁ UM IMPULSO AO FIM DA GANGORRA, EVITANDO LEITURAS INDESEJADAS
  if (analogRead(IR2) > black_tape && analogRead(IR3) > black_tape && acc.getY() > 0.22) {
    motor.go(120, 120);
    delay(700);
  }
  // *** |-----------------------------------------------------------------------| *** //

  // |---------- LÓGICA DO SENSOR ULTRASÔNICO ----------| //
  if (button.isPressed()) {
    path.redirectObstacle();
    button.pressed = false;
  }

  //  |---------- ------ -- ----- ----------- ----------| //


  //  |---------- LÓGICA DO CRUZAMENTO ----------| //
  if (analogRead(IR1) > black_tape_2 && analogRead(IR4) > black_tape_2 + 300 && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) {
      motor.left90(150);
      delay(800);
      path.turnOn90(LEFT90, 100);
    }

    else if (leds.colorRight.equals("GREEN")) {
      motor.right90(150);
      delay(800);
      path.turnOn90(RIGHT90, 100);
    }

    // CASO NÃO HAJA FITA VERDE, O ROBÔ CONTINUA ANDANDO ATÉ DEIXAR O CRUZAMENTO
    else {
      motor.go(100, 100);
      delay(600);
    }
    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }
  //  |---------- ------ -- --------- ----------| //

  //     |---------- LÓGICA DAS CURVAS DE 90 GRAUS ----------| //

  else if (analogRead(IR1) > black_tape_2 && analogRead(IR2) > black_tape && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();
    else if (leds.colorLeft.equals("GREEN")) {
      motor.left90(150);
      delay(1100);
      path.turnOn90(LEFT90, 100);
    }

    else if (leds.colorRight.equals("GREEN")) {
      motor.right90(150);
      delay(1100);
      path.turnOn90(RIGHT90, 100);
    }

    else {
      motor.go(80, 80);
      delay(400);
      path.turnOn90(LEFT90, 800);
    }
    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }

  else if (analogRead(IR3) > black_tape_2 + 200 && analogRead(IR4) > black_tape_2 + 300 && acc.getY() < standard_acc_value) {

    path.moveBackToReadColor();
    leds.ReadLdrOnGreen();

    if (leds.colorLeft.equals("GREEN") && leds.colorRight.equals("GREEN")) path.fullTurn();

    else if (leds.colorLeft.equals("GREEN")) {
      motor.left90(150);
      delay(1100);
      path.turnOn90(LEFT90, 100);
    }

    else if (leds.colorRight.equals("GREEN")) {
      motor.right90(150);
      delay(1100);
      path.turnOn90(RIGHT90, 100);
    }

    else {
      motor.go(80, 80);
      delay(400);
      path.turnOn90(RIGHT90, 800);
    }

    leds.colorLeft = "WHITE";
    leds.colorRight = "WHITE";
  }
  //     |---------- ------ --- ----- -- -- ----- ----------| //


  // ****CURVA LEVE PARA  A ESQUERDA**** //
  else if (!turning && analogRead(IR1) > black_tape && acc.getY() <= standard_acc_value) {
    startTurn(EXLEFT, 300, speed_2);
  }

  else if (!turning && analogRead(IR2) > black_tape - 150) {
    startTurn(LEFT, 300, speed_2 + 40);
  }

  // ****CURVA LEVE PARA  A DIREITA****  //
  else if (!turning && analogRead(IR3) > black_tape_2) {
    startTurn(RIGHT, 300, speed_2 + 40);
  }

  else if (!turning && analogRead(IR4) > black_tape_2 + 250 && acc.getY() <= standard_acc_value) {
    startTurn(EXRIGHT, 300, speed_2);
  }

  else if (!turning) {
    motor.go(speed + 20, speed);
  }

  updateTurn(speed + 20, speed);
}

void readLDRS() {
  Serial.print("LDR 1: ");
  Serial.println(analogRead(A15));
  Serial.print("LDR 2: ");
  Serial.println(analogRead(A14));
  delay(500);
}
