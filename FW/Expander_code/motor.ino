
void setMotorSpeed(motors m, int8_t s) {
  return;

  DEBUG_ERROR("Using old function");

  byte speed = map(abs(s), 0, 127, 0, 255);
  bool d = s < 0;
  //DEBUG_DEBUG("Set speed: %d, input %d", speed, s);
  switch (m) {
    case R1:
      analogWrite(MOT_1_E, speed);
      digitalWrite(MOT_1_A, d);
      digitalWrite(MOT_1_B, !d);
      break;
    case R2:
      analogWrite(MOT_2_E, speed);
      digitalWrite(MOT_2_A, d);
      digitalWrite(MOT_2_B, !d);
      break;
    case L2:
      analogWrite(MOT_3_E, speed);
      digitalWrite(MOT_3_A, d);
      digitalWrite(MOT_3_B, !d);
      break;
    case L1:
      analogWrite(MOT_4_E, speed);
      digitalWrite(MOT_4_A, d);
      digitalWrite(MOT_4_B, !d);
      break;
    default:
      DEBUG_ERROR("Set motor direction: Unknow motor: %d", m);
  }
}