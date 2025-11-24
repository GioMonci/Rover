#include "Ultrasonic.hpp"

Ultrasonic::Ultrasonic(uint8_t trigPin, uint8_t echoPin)
: _trigPin(trigPin),
  _echoPin(echoPin),
  _initialized(false) {
}

float Ultrasonic::readCm() {
  // Configure the pins once, on first use.
  if (!_initialized) {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    _initialized = true;
  }

  // Make sure trigger is low for a short time
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 µs HIGH pulse on trigger to start a measurement
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Measure the length of the echo pulse in microseconds.
  // Use a timeout so the code doesn't block forever if there is no echo.
  // 30,000 µs ≈ max ~5 meters for HC-SR04, more than enough.
  unsigned long duration = pulseIn(_echoPin, HIGH, 30000UL);

  // If duration == 0, pulseIn timed out → no echo
  if (duration == 0) {
    return -1.0f;  // indicate "no reading"
  }

  // Speed of sound ≈ 343 m/s.
  // In air: distance (cm) = (duration_us * 0.0343) / 2
  // Divide by 2 because the pulse travels to the object and back.
  float distanceCm = (duration * 0.0343f) / 2.0f;

  return distanceCm;
}
