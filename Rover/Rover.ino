/********************************
*   Names: Giovanni M & Simon M
*  Course: Embedded Systems
*    Date: 11/19/25
* Purpose: Move Rover
*********************************/

// Includes
#include "Motor.h"

//INIT L&R motors
Motor leftMotor = Motor(4, 5, 6, 7, false, 1.f);
Motor rightMotor = Motor(A0, A1, A2, A3, true, 1.f);

//consts
int speed = 600;
bool moving = false;
int next = 1;


void setup() {
  Serial.begin(115200);
  turnLeft360();

}

void loop() {
    
  if(!moving){
    switch(next){
      case 1:
        turnLeft360();
        moving=true;
        next+=1;
        break;
      case 2:
        turnRight360();
        moving=true;
        next-=1;
        break;
    }
  }
  if(moving){
    leftMotor.runSpeedToPosition();
    rightMotor.runSpeedToPosition();

    bool atTargetLeft = leftMotor.distanceToGo() == 0;
    bool atTargetRight = rightMotor.distanceToGo() == 0;

    moving = !(atTargetLeft && atTargetRight);
  }
}

void turnLeft360(){
  leftMotor.reverse(speed, 1.09f);
  rightMotor.forward(speed, 1.09f);
}

void turnRight360(){
  leftMotor.forward(speed, 1.09f);
  rightMotor.reverse(speed, 1.09f);
}

void turnLeft180(){
  leftMotor.reverse(speed, 0.545f);
  rightMotor.forward(speed, 0.545f);
}

void turnLeft90(){
  leftMotor.reverse(speed, 0.2725f);
  rightMotor.forward(speed, 0.2725f);
}
