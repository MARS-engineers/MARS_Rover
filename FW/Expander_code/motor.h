#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
  int _pin_en;
  int _pin_a;
  int _pin_b;

public:
  Motor(int pin_en, int pin_a, int pin_b);
  void setup(void);
  void SetSpeed(int8_t s);
  void stop(void);
  void stopSlow(void);
};

#endif