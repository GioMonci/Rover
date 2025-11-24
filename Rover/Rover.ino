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
}

void loop() {
    
  if(!moving){
    float frontwall = sensor.readCm();
    if(frontwall < 0){frontwall = 400;}
    if(frontwall > WALL_DISTANCE_CM){queueForwardStep();moving = true;}
    // hit wall, nod servo, to look like head nod
    else{servoPos = 95;myServo.write(servoPos); delay(1000);servoPos = 90; myServo.write(servoPos); delay(1000);}
  }
  if(moving){

    leftMotor.runSpeedToPosition();
    rightMotor.runSpeedToPosition();

    bool atTargetLeft = leftMotor.distanceToGo() == 0;
    bool atTargetRight = rightMotor.distanceToGo() == 0;

    moving = !(atTargetLeft && atTargetRight);
  }
}

