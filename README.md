This repository contains the code for a Rescue Robot, developed in C++ for Arduino. The robot is capable of following a black line, detecting colors with an RGB sensor, avoiding obstacles, rescuing objects with a claw, and responding to ramps or seesaws using an accelerometer.

🏆 Prêmio Inovação– This robot won the Innovation Prize in the OBR (Olímpíada Brasileira de Robótica).

Project Structure

Motor.h → Controls the motors (forward, backward, curves, 90° turns).

Path.h → Navigation logic, handling crossings and turns.

InfraRed.h → Reads infrared sensors for line tracking.

Leds.h → Controls LEDs and reads LDRs to detect colors.

Sensor.h → Handles ultrasonic sensors for obstacle detection.

Accelerometer.h → Reads accelerometer data for ramp or tilt detection.

TCS3200D.h → Interface for the TCS3200 RGB color sensor.

Button.h → Handles push-button inputs (e.g., claw or obstacle trigger).

Servo.h → Controls the main claw servo and auxiliary servo.

Features

Line Following: Uses IR sensors to follow black tape on the floor.

Color Detection: Detects green markers to handle crossings and turning logic.

Obstacle Avoidance: Uses ultrasonic sensors to detect obstacles in front or laterally.

Rescue Mechanism: Operates a claw to pick up and release objects.

Ramp/Seesaw Handling: Adjusts speed based on accelerometer readings to avoid errors on slopes.

Setup

Connect all sensors and actuators according to the pin definitions in main.cpp.

Upload the code to your Arduino board.

Calibrate LDRs and accelerometer before starting the robot.
