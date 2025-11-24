// Ultrasonic.hpp
// Gio M
// Holds includes, consts, declarations, etc
// Clean up Rover.ion
// ----------------------------------------------------------

#pragma once
#include <Arduino.h>

// Super simple wrapper around an HC-SR04 ultrasonic sensor.
// Usage:
//   Ultrasonic sensor(A4, A5);
//   float d = sensor.readCm();  // distance in centimeters
class Ultrasonic {
public:
  Ultrasonic(uint8_t trigPin, uint8_t echoPin);

  // Returns distance in centimeters.
  // Returns < 0 if no echo was received (timeout).
  float readCm();

private:
  uint8_t _trigPin;
  uint8_t _echoPin;
  bool _initialized;
};
