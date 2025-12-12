#include <Wire.h>


void I2C_RxHandler(int numBytes);
void I2C_RX_REQ(int bytes);

byte I2cCmd, I2cSubCmd, I2cArg1, I2cArg2, I2cArg3;

// FIFO queue
//#define I2C_QUE_ENABLE
#define I2C_QUE_MAX 255     // How long que can be
#define I2C_QUE_DAT_LEN 10  // How much data store to que
#define I2C_QUE_DEL         // If delete used data or just move pointer
#define I2C_QUE_DEBUG
#define DEBUG_I2C

uint32_t queGetP, quePutP;
byte que[I2C_QUE_MAX][I2C_QUE_DAT_LEN];
bool queOverflow;

byte RxByte;
///////////////////////////////////////////////////////////////////////////////////////
void setupI2c() {
  Wire1.setSDA(PIN_WIRE1_SDA);
  Wire1.setSCL(PIN_WIRE1_SCL);
  Wire1.begin(I2C_ADRESS);  // Initialize I2C (Slave Mode: address=0x55 )
  Wire1.onReceive(I2C_RxHandler);

  //Wire.onRequest(I2C_RX_REQ);
  queGetP = 0;
  quePutP = 0;
  queOverflow = 0;
}


void loopI2c() {
#ifdef I2C_QUE_ENABLE
  handleQueue();  // Check for commands in queue and process them
#endif
}

void DebugI2C(uint8_t buffer[32], byte bytes) {
  Serial.printf("I2C Cmd: 0x%02x, SubCmd: 0x%02x, Arg1: 0x%02x, Arg2: 0x%02x, Arg3: 0x%02x", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

  Serial.printf("\tbytes: %i, data: ", bytes);
  for (byte i = 0; i <= bytes; i++) {
    Serial.printf(" %02x", buffer[i]);
  }
  Serial.println("");
}

void I2C_RxHandler(int bytes) {
  digitalWrite(EXP_LED, HIGH);

  //blink(1);

  if (bytes > 32) {
    Serial.println("E: bytes > 32.");
    return;
  }

  byte I2Cbuffer[32];
  Wire1.readBytes((byte*)&I2Cbuffer, bytes);  // Read data from I2C

#ifdef I2C_QUE_ENABLE
  quePut(I2Cbuffer, bytes);  // Put them to the que
#else
  handleCommands(I2Cbuffer, bytes);
#endif

  digitalWrite(EXP_LED, LOW);
}

bool quePut(byte data[32], byte len) {
  if (!len) return false;

  uint16_t next = (quePutP + 1) % I2C_QUE_MAX;
  if (next == queGetP) {
    // fronta plná
    return false;
  }

  for (byte i = 0; i < len && i < I2C_QUE_DAT_LEN; i++) {
    que[quePutP][i] = data[i];
  }

  quePutP = next;
#ifdef I2C_QUE_DEBUG
  Serial.printf("Que put lenght: %i\n", quePutP);
#endif
  return true;
}

bool handleQueue() {
  if (queGetP == quePutP) {
    // fronta prázdná
    return false;
  }

  handleCommands(que[queGetP], 10);

#ifdef I2C_QUE_DEL
  for (byte i = 0; i < I2C_QUE_DAT_LEN; i++) que[queGetP][i] = 0;
#endif

  queGetP = (queGetP + 1) % I2C_QUE_MAX;
#ifdef I2C_QUE_DEBUG
  Serial.printf("Que get lenght: %i\n", queGetP);
#endif
  return true;
}


void handleCommands(byte buffer[32], byte bytes) {

  I2cCmd = buffer[0];
  I2cSubCmd = buffer[1];
  I2cArg1 = buffer[2];
  I2cArg2 = buffer[3];
  I2cArg3 = buffer[4];
#ifdef DEBUG_I2C
  DebugI2C(buffer, bytes);
#endif

  switch (I2cCmd) {
      /////////////////////////////////// Nothing ///////////////////////////////////////////
    case 0x00:  // Nothing
      break;
      ///////////////////////////////////////////////////////////////////////////////////////

    case 0x01:  // Ping
      switch (I2cSubCmd) {
        case 0x0F:  // Request
          char buf_req[1] = { 0xff };
          Wire1.writeAsync(I2C_MCU, buf_req, 1);
          break;
      }
      break;

    case 0x02:  // Controll
      switch (I2cSubCmd) {
        case 0x01:  // Reset
          rp2040.reboot();
          break;
      }
      break;

    case 0x03:
      switch (I2cSubCmd) {
        case 0x01:  // Get FW version
          Wire1.writeAsync(I2C_MCU, vFW, sizeof(vFW));
          break;
        case 0x02:  // Get HW version
          Wire1.writeAsync(I2C_MCU, vHW, sizeof(vHW));
          break;
        case 0x03:       // Get board MEDI
          char buf[16];  // dostatečně velký buffer
          snprintf(buf, sizeof(buf), "%ld", MEDI);
          Wire1.writeAsync(I2C_MCU, buf, strlen(buf) + 1);
          break;
      }
      break;


    /*
      0x11ZZYY	Run motor ZZ at speed YY
          |  \----	Speed (-127 - 127)
            ------	Motor
      		          0x00	R1
      		          0x01	R2
      		          0x02	L1
      		          0x03	L2
          */
    case 0x11:
      int s;
      s = map((int8_t)I2cArg1, -127, 127, -255, 255);
      Serial.printf("Speed: %i input: %i\n", s, I2cArg1);
      setMotorSpeed((motors)I2cSubCmd, s);
      break;
      ///////////////////////////////////////////////////////////////////////////////////////

      //////////////////////////////// Set motors speed /////////////////////////////////////
      /*
      0x12XXXXXXXX	Set motors speed
          |  | | `--	R1	Speed (-127 - 127)
          |  |  ----	R2	Speed (-127 - 127)
          |   ------	L1	Speed (-127 - 127)
            ---------	L2	Speed (-127 - 127)
      */
    case 0x12:
      setMotorsSpeed(I2cSubCmd, I2cArg1, I2cArg2, I2cArg3);
      break;
      ///////////////////////////////////////////////////////////////////////////////////////

      ///////////////////////// Run car in direction at speed OLD ///////////////////////////////
      /*
        0x21ZZYY	Run car in direction at speed YY
            |  \----	Speed (-127 - 127)
              ------	Direction
                  0x00	Forward
                  0x01	Slide
                  0x02	Turn_round
                  0x03	Turn_rear
                  0x04	Turn_front
                  0x05	Diagonal_left
                  0x06	Diagonal_right
      */
    case 0x21:
      carMoveDir((directions2)I2cSubCmd, convertToInt(I2cArg1));
      break;
      ///////////////////////////////////////////////////////////////////////////////////////



      ///////////////////////// Run car motor 1 and 2 at speed ZZ and motor 3 and 4 at speed YY  ///////////////////////////////
      /*
        0x23ZZYY	Run car motor 1 and 2 at speed ZZ and motor 3 and 4 at speed YY 
            |  \----	Speed1,2 (-127 - 127)
              ------	Speed3,4 (-127 - 127)
      */
    case 0x23:
      carMoveAB(convertToInt(I2cSubCmd), convertToInt(I2cArg1));
      break;
      ///////////////////////////////////////////////////////////////////////////////////////


      ///////////////////////// Run car in direction at speed ///////////////////////////////
      /*
        0x31ZZYY	Run car in direction at speed YY
            |  \----	Speed (-127 - 127)
              ------	Direction
                      0x00	STOP
                      0x01	FORWARD
                      0x02	BACKWARD
                      0x03	SLIDE_RIGHT
                      0x04	SLIDE_LEFT
                      0x05	DIAG_FWD_LEFT
                      0x06	DIAG_FWD_RIGHT
                      0x07	DIAG_BACK_LEFT
                      0x08	DIAG_BACK_RIGHT
                      0x09	ROTATE_LEFT
                      0x0A	ROTATE_RIGHT
      */
    case 0x31:
      moveInDirection((CarMoveDirections)I2cSubCmd, convertToInt(I2cArg1));
      break;
      ///////////////////////////////////////////////////////////////////////////////////////

    case 0x10:  // Motors basic controll
      switch (I2cSubCmd) {
        case 0x00:  // Disable motors
          disableMotors();
          break;
        case 0x01:  // Enable motors
          enableMotors();
          break;
      }
      break;

    default:
      Serial.print("E: unknow packet type: \n");
      DebugI2C(buffer, bytes);
  }
}


void I2C_RX_REQ(int bytes) {
}

int8_t convertToInt(byte raw) {
  int signedValue;

  if (raw & 0x80) {
    // Záporné číslo: maskujeme MSB, výsledek negujeme
    signedValue = -(raw & 0x7F);
  } else {
    // Kladné číslo
    signedValue = raw;
  }

  //DEBUG_DEBUG("Raw: 0x%02X", raw);
  //DEBUG_DEBUG("Signed (signed-magnitude): %d", signedValue);
  return signedValue;
}
