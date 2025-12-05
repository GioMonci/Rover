/********************************
*   Names: Gio M & Simon M
*  Course: Embedded Systems
*   Start: 11/19/25
*     End: 12/xx/25
* Purpose: Move Rover
*********************************/

// Includes
#include "Rover.hpp"

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  servoPos = 85;
   myServo.write(servoPos);
}

void loop() {  
  if(!moving){
    switch(state){
      case FORWARD:{
        float frontWall = sensor.readCm();
        if(frontWall < 0){frontWall = 400;}
        if(frontWall > WALL_DISTANCE_CM){queueForwardStep(); moving = true;}
        // hit wall, nod servo, to look like head nod
        if(frontWall <= WALL_DISTANCE_CM){servoPos = 90; myServo.write(servoPos); delay(1000);servoPos = 85; myServo.write(servoPos); delay(1000); headNodCount++;}
        if(headNodCount == 5){state = TURNING; headNodCount = 0; readLeftWall = false; readRightWall = false; movedLeft = false; movedRight = false; movedBack = false;}
        // states
        readLeftWall = false;
        readRightWall = false;
        movedLeft = false;
        movedRight = false;
        movedBack = false;
        break;
      }
      case TURNING:{
        Serial.println("in turning"); 
        if(!readLeftWall  && !readRightWall){
          turnLeft(regSpeed, _90);
          moving = true;
            if(movedLeft){
              // read left wall
              leftWall = sensor.readCm();
              readLeftWall = true;
              movedLeft = false;
              moving = false;
          }
          movedLeft = true;
        }
        if(readLeftWall && !readRightWall){
          turnRight(regSpeed, _180);
          moving = true;
          if(movedRight){
            // read right wall
            rightWall = sensor.readCm();
            readRightWall = true;
            movedRight = false;
            moving = false;
          }
          movedRight = true;
        }
        if(readLeftWall && readRightWall){
          turnLeft(regSpeed, _90);
          moving = true;
          if(movedBack){
            servoPos = 93;myServo.write(servoPos); delay(1000);servoPos = 90; myServo.write(servoPos); delay(1000);
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
            else{state=FORWARD;}
          }
          movedBack = true;
        }
        break;
      }
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

