#include <Arduino.h>
#include <AutoPID.h>
#include "PicoEncoder.h"

class PositionControl {

private:
  // Motor Pin Configuration
  uint8_t pwmPin;
  uint8_t dirPin;
  uint8_t encA;
  uint8_t encB;
  bool polarity_reverse = false;

  // Motor Related Parameters

  float motorRadius = 1;  // in metres
  float maxSpeed = 2.0;   // Rotation Per Second

  // PID Control Related Parameter
  double outputMin = -50;
  double outputMax = 50;
  float kP = 0.1;
  float kI = 0.03;
  float kD = 0.02;

public:
  // Velocity control related parameters
  double currentPosition;
  long CPR = 36124;
  double setPoint = 0;
  double outputPWM = 0;
  double tolerance = 0.1;

  // double * position;
  AutoPID pid{ &currentPosition, &setPoint, &outputPWM, outputMin, outputMax, kP, kI, kD };
  PicoEncoder encoder;

  void initialSetup(int pin) {
    // variables for velocity calculation
    setPoint = 0.0;
    currentPosition = 0;
    outputPWM = 0;

    encoder.begin(MOT_1_EA);
  }

  PositionControl() {
    // params:  direction pin , pwm pin , encoder A , encoder B
  }

  ~PositionControl() {
    // destructor for the class
    //delete encoder;
  }

  void setReversePolarity(bool polarity) {
    polarity_reverse = polarity;
  }

  void setTolerance(float delta) {
    tolerance = delta;
  }

  void setMotorPWM(int PWM) {
    if (polarity_reverse)
      PWM = PWM * -1;
    // Changing the motor direction based on the PWM value
    if (PWM < 0)
      setMotorDirection(R1, F, abs(PWM));
    else
      setMotorDirection(R1, B, abs(PWM));
  }

  void setPIDValue(float p, float i, float d) {
    kP = p;
    kI = i;
    kD = d;
    pid.setGains(kP, kI, kD);
  }

  void setPIDOutput(int min, int max) {
    outputMin = min;
    outputMax = max;
    pid.setOutputRange(outputMin, outputMax);
  }

  void setCPR(long cpr) {
    CPR = cpr;
    Serial.println("CPR");
    Serial.println(CPR);
  }

  void setMotorMaxSpeed(float speed) {
    maxSpeed = speed;
  }

  void setAngle(float theta) {
    // input: motor speed in rotation per second
    setPoint = long((theta * CPR) / 360);
    Serial.println("Set angle: ");
    Serial.println(theta);
  }

  float getAngle() {
    encoder.update();
    return ((encoder.step * 360) / double(CPR));
  }

  void controlLoop() {
    encoder.update();
    currentPosition = encoder.step;
    pid.run();
    if (setPoint < 0) {
      if (((setPoint + (tolerance * CPR)) > currentPosition) && ((setPoint - (tolerance * CPR))) < currentPosition) {
        outputPWM = 0;
        setPoint = encoder.step;
        pid.stop();
        Serial.println("Reached the target");
      }

      setMotorPWM(outputPWM);
    } else {
      if (((setPoint - (tolerance * CPR)) < currentPosition) && ((setPoint + (tolerance * CPR)) > currentPosition)) {
        outputPWM = 0;
        setPoint = encoder.step;
        pid.stop();
        Serial.println("Reached the target");
      }

      setMotorPWM(outputPWM);
    }
  }
};
