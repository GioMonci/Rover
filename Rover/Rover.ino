/********************************
*   Names: Gio M & Simon M
*  Course: Embedded Systems
*   Start: 11/19/25
*     End: 12/xx/25
* Purpose: Move Rover
*********************************/

// Includes
#include "Rover.hpp"

enum roverStates {
  FORWARD = 0,
  TURNING = 1
};

roverStates state = FORWARD;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
    
  if(!moving){
    switch(state){
      case FORWARD:
        float frontWall = sensor.readCm();
        if(frontWall < 0){frontWall = 400;}
        if(frontWall >= WALL_DISTANCE_CM){queueForwardStep();moving = true;}
        // hit wall, nod servo, to look like head nod
        else{servoPos = 95;myServo.write(servoPos); delay(1000);servoPos = 90; myServo.write(servoPos); delay(1000); headNodCount++;}
        if(headNodCount >= 3){state = TURNING;}
        break;
      case TURNING:
        if(!readLeftWall  && !readRightWall){
          turnLeft(regSpeed, _90);
          moving = true;
            if(movedLeft){
              // read left wall
              leftWall = sensor.readCm();
              readLeftWall = true;
              movedLeft = false;
          }
          movedLeft = true;
        }
        if(readLeftWall && !readRightWall){
          turnRight(regSpeed, _180);
          moving = true;
          if(movedRight){
            rightWall = sensor.readCm();
            readRightWall = true;
            movedRight = false;
          }
          movedRight = true;
        }
        if(readLeftWall && readRightWall){
          turnLeft(regSpeed, _90);
          servoPos = 95;myServo.write(servoPos); delay(1000);servoPos = 90; myServo.write(servoPos); delay(1000);
          //compare wall dist
          if(leftWall > rightWall){
            // turn left
            turnLeft(regSpeed, _90);
            moving = true;
            state = FORWARD;
          }
          if(rightWall > leftWall){
            // turn right
            turnRight(regSpeed, _90);
            moving = true;
            state = FORWARD;
          }
        }
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

