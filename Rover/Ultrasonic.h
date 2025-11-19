

class Ultrasonic { // triggers and reads data, echo and trig
public:
  Ultrasonic(uint8_t trigPin, uint8_t echoPin) {
    setTrigger(trigPin);
    setEcho(echoPin);
  }

  void setTrigger(uint8_t trigPin) {
    _trigPin = trigPin;
    pinMode(_trigPin, OUTPUT);
    digitalWrite(_trigPin, LOW);
  }
  
  void setEcho(uint8_t echoPin) {
    _echoPin = echoPin;
    pinMode(_echoPin, INPUT);
  }
  
  float centimeters() { // measures and returns centimeters
    unsigned long roundTripUs = measureDuration();
    if (roundTripUs == 0) {
      return -1.0f;
    }
    float oneWayUs = roundTripUs / 2.0f;
    float cm = oneWayUs * 0.0343f;
    return cm;
  }

  float inches() {
    float cm = centimeters();
    if (cm < 0) {
      return -1.0f;
    }
    return cm / 2.54f;
  }

private:
  uint8_t _trigPin;
  uint8_t _echoPin;

  unsigned long measureDuration() {	// sends a trigger and measures echo duration
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    unsigned long pulseLen = pulseIn(_echoPin, HIGH, 25000UL);
    return pulseLen;
  }
};


