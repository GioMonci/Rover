#include "Motor.hpp"

// Define static constants
const float Motor::MAX_SPEED = 2000.0f;
const float Motor::FULL_STEP = 2048.0f;

Motor::Motor(uint8_t in1, uint8_t in2,uint8_t in3,uint8_t in4,bool invert,float ratio)
: AccelStepper(AccelStepper::MotorInterfaceType::FULL4WIRE, in1, in3, in2, in4),
_inverted(invert), _ratio(ratio) {setMaxSpeed(MAX_SPEED);}

void Motor::forward(float speed, float scale){
  setCurrentPosition(0);
  float target = FULL_STEP * _ratio;
  if (_inverted) {target *= -1.0f;}
  target *= scale;
  move(target);
  setSpeed(speed);
}

void Motor::reverse(float speed, float scale){
  setCurrentPosition(0);
  float target = -FULL_STEP * _ratio;
  if (_inverted) {target *= -1.0f;}
  target *= scale;
  move(target);
  setSpeed(speed);
}