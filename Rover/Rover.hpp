// Rover.hpp
// Gio M
// Holds includes, consts, declarations, etc
// Clean up Rover.ion
// ----------------------------------------------------------

#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "Motor.hpp"
#include "Ultrasonic.hpp"


// Constants for Rover.ino
int regSpeed = 600; uint8_t servoPin = 9; int servoPos = 0;

// turns
float _360 = 1.09f; float _180 = 0.545f; float _90 =  0.2725f; float _45 = 0.13625;

const float WALL_DISTANCE_CM   = 30.0f;  // how close we get to a wall before stop and turn
const float FORWARD_STEP_SCALE = 0.010f;  // one "chunk" of forward motion

/****Objects*****/
//INIT L&R motors objects for Rover.ino
Motor leftMotor(4, 5, 6, 7, false, 1.f); Motor rightMotor(A0, A1, A2, A3, true, 1.f);
// Ultrasonic sensor
Ultrasonic sensor(A4, A5);
//Servo
Servo myServo;

// states
bool moving = false;
bool readLeftWall = false;
bool readRightWall = false;
bool movedLeft = false;
bool movedRight = false;

int headNodCount = 0;
float leftWall = 0, rightWall = 0;

// Helper Funct to turn left or right, specify speed and degree. ex: turnleft(regSpeed, _360), turnleft(300.0f, 0.545f)
// I know its a scale but for turning we can just simplify it to certain scale = a degree turn
void turnLeft(float turnSpeed, float deg){leftMotor.reverse(turnSpeed, deg);rightMotor.forward(turnSpeed,deg);}
void turnRight(float turnSpeed, float deg){leftMotor.forward(turnSpeed, deg);rightMotor.reverse(turnSpeed,deg);}
// Move forward a bit
void queueForwardStep(){leftMotor.forward(regSpeed, FORWARD_STEP_SCALE);rightMotor.forward(regSpeed, FORWARD_STEP_SCALE);}