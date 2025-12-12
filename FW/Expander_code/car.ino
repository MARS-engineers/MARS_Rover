
Motor MotorLeftFront(MOT_1_E, MOT_1_A, MOT_1_B);
Motor MotorLeftBack(MOT_2_E, MOT_2_A, MOT_2_B);
Motor MotorRightFront(MOT_3_E, MOT_3_A, MOT_3_B);
Motor MotorRightBack(MOT_4_E, MOT_4_A, MOT_4_B);

void carSetup() {
  MotorLeftFront.setup();
  MotorLeftBack.setup();
  MotorRightFront.setup();
  MotorRightBack.setup();

  pinMode(MOT_STBY, OUTPUT);
}

void disableMotors() {
  digitalWrite(MOT_STBY, LOW);
}
void enableMotors() {
  digitalWrite(MOT_STBY, HIGH);
}

void STOPall() {
  MotorLeftFront.stop();
  MotorLeftBack.stop();
  MotorRightFront.stop();
  MotorRightBack.stop();
}

void carStop() {
  disableMotors();
  STOPall();
}

void setMotorsSpeed(int8_t a, int8_t b, int8_t c, int8_t d) {
  MotorLeftFront.SetSpeed(a);
  MotorLeftBack.SetSpeed(b);
  MotorRightFront.SetSpeed(c);
  MotorRightBack.SetSpeed(d);
}

void carMoveDir(directions2 d, int8_t speed) {
  switch (d) {
    case STRAIGHT:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, speed);
      break;

    case SLIDE:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed * -1);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed * -1);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, speed);
      break;

    case TURN_AROUND:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, speed * -1);
      break;

    case TURN_REAR:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(0);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(0);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, 0);
      break;

    case TURN_FRONT:
      MotorLeftFront.SetSpeed(0);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(0);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, speed * -1);
      break;

    case DIAG_LEFT:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(0);
      MotorRightFront.SetSpeed(0);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, speed);
      break;

    case DIAG_RIGHT:
      MotorLeftFront.SetSpeed(0);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(0);

      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, 0);
      break;
  }
}

void carMoveAB(int8_t motors12, int8_t motors34) {
  MotorLeftFront.SetSpeed(motors12);
  MotorLeftBack.SetSpeed(motors12);
  MotorRightFront.SetSpeed(motors34);
  MotorRightBack.SetSpeed(motors34);

  setMotorSpeed(L1, motors12);
  setMotorSpeed(L2, motors12);
  setMotorSpeed(R1, motors34);
  setMotorSpeed(R2, motors34);
}

void moveInDirection(CarMoveDirections d, int8_t speed) {
  switch (d) {
    case STOP:
      MotorLeftFront.SetSpeed(0);
      MotorLeftBack.SetSpeed(0);
      MotorRightFront.SetSpeed(0);
      MotorRightBack.SetSpeed(0);

      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, 0);
      break;
    // Straight
    case FORWARD:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, speed);
      break;
    case BACKWARD:
      MotorLeftFront.SetSpeed(speed * -1);
      MotorLeftBack.SetSpeed(speed * -1);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, speed * -1);
      setMotorSpeed(L2, speed * -1);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, speed * -1);
      break;
    // Slide
    case SLIDE_RIGHT:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed * -1);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed * -1);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, speed);
      break;
    case SLIDE_LEFT:
      MotorLeftFront.SetSpeed(speed * -1);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, speed * -1);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, speed * -1);
      break;
      // Diagonal forward
    case DIAG_FWD_LEFT:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(0);
      MotorRightFront.SetSpeed(0);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, speed);
      break;
    case DIAG_FWD_RIGHT:
      MotorLeftFront.SetSpeed(0);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(0);

      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, 0);
      break;
    // Diagonal backward
    case DIAG_BACK_LEFT:
      MotorLeftFront.SetSpeed(speed * -1);
      MotorLeftBack.SetSpeed(0);
      MotorRightFront.SetSpeed(0);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, speed * -1);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, speed * -1);
      break;
    case DIAG_BACK_RIGHT:
      MotorLeftFront.SetSpeed(0);
      MotorLeftBack.SetSpeed(speed * -1);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(0);

      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, speed * -1);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, 0);
      break;
    // Rotate
    case ROTATE_LEFT:
      MotorLeftFront.SetSpeed(speed);
      MotorLeftBack.SetSpeed(speed);
      MotorRightFront.SetSpeed(speed * -1);
      MotorRightBack.SetSpeed(speed * -1);

      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, speed * -1);
      break;
    case ROTATE_RIGHT:
      MotorLeftFront.SetSpeed(speed * -1);
      MotorLeftBack.SetSpeed(speed * -1);
      MotorRightFront.SetSpeed(speed);
      MotorRightBack.SetSpeed(speed);

      setMotorSpeed(L1, speed * -1);
      setMotorSpeed(L2, speed * -1);
      setMotorSpeed(R1, speed);
      setMotorSpeed(R2, speed);
      break;
      /*
    case TURN_REAR:
      setMotorSpeed(L1, speed);
      setMotorSpeed(L2, 0);
      setMotorSpeed(R1, speed * -1);
      setMotorSpeed(R2, 0);
      break;
    case TURN_FRONT:
      setMotorSpeed(L1, 0);
      setMotorSpeed(L2, speed);
      setMotorSpeed(R1, 0);
      setMotorSpeed(R2, speed * -1);
      break;*/
  }
}