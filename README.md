# Rover

Embedded-systems rover project using Arduino, dual stepper motors, a servo-mounted ultrasonic sensor, and obstacle-course completion logic.

![Rover](Documentation/images/rover.png)

## Overview

This project implements a small autonomous rover that can drive through a course while avoiding obstacles.  
The rover uses:

- Two 4-wire stepper motors for differential drive.
- One HC-SR04-style ultrasonic distance sensor mounted on a servo.

The code is written in the Arduino IDE as part of an embedded-systems course.

## Hardware

Typical hardware setup:

- **Microcontroller:** Arduino Uno
- **Drive motors:** Two stepper motors.
- **Ultrasonic sensor:** HC-SR04 or equivalent (TRIG / ECHO).
- **Servo:** Standard hobby servo used to rotate the ultrasonic sensor to scan the environment.

## Software / Libraries

- **Arduino IDE**
- **AccelStepper** library
- **Servo** library

## Project Structure

- `Rover.ino`  
   AAAAA
- `Motor.h` / `Motor.cpp`  
   AAA

- `Ultrasonic.h` / `Ultrasonic.cpp`  
   AAA



