// Motor.hpp
// Creator: Prof. Allen
// FGCU Computing & Software Engineering
//
// Abstraction of a single 4-pin stepper motor such as the 28BYJ-48 using
// the AccelStepper library to support control of mutliple instances
// of this class.
//
// The motor can be inverted to invert directional control for motors installed in
// reverse or on the other side of a robot or car, and supports a gear ratio that is
// defaulted to 1.0. Forward and reverse movements make whole rotations by default, but
// can be scaled to make for fractional rotations such as quarter 0.25, or half 0.5, etc.
// Speed is expressed in steps-per-second and should be limited to 2000.
// --------------------------------------------------------------------------------

#pragma once

#include <AccelStepper.h>

class Motor : public AccelStepper {
public:
  static const float MAX_SPEED;
  static const float FULL_STEP;

  Motor(uint8_t in1, uint8_t in2,uint8_t in3,uint8_t in4,bool invert = false, float ratio = 1.0f);
  // Move one (scaled) revolution forward
  void forward(float speed, float scale = 1.0f);
  // Move one (scaled) revolution backward
  void reverse(float speed, float scale = 1.0f);

private:
  bool  _inverted;
  float _ratio;
};

