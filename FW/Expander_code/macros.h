
enum motors {
  L1,
  L2,
  R1,
  R2
};

enum directions2 {
  STRAIGHT,
  SLIDE,
  TURN_AROUND,
  TURN_REAR,
  TURN_FRONT,
  DIAG_LEFT,
  DIAG_RIGHT
};

enum CarMoveDirections {
  STOP = 0x00,
  FORWARD = 0x01,
  BACKWARD = 0x02,
  SLIDE_RIGHT = 0x03,
  SLIDE_LEFT = 0x04,
  DIAG_FWD_LEFT = 0x05,
  DIAG_FWD_RIGHT = 0x06,
  DIAG_BACK_LEFT = 0x07,
  DIAG_BACK_RIGHT = 0x08,
  ROTATE_LEFT = 0x09,
  ROTATE_RIGHT = 0x0A
};
