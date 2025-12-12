
#include "macros.h"
#include "config.h"
#include "Arduino_DebugUtils.h"
#include "motor.h"
#include <ezLED.h>


ezLED led(EXP_LED);

unsigned long currentMillis, lastMillis;


double motor1Enc_step;

#define Serial Serial

#define FW_VERSION "0.2.1"
#define HW_VERSION "0.1.0"

const char* vFW = FW_VERSION;
const char* vHW = HW_VERSION;

void setup() {
  Serial.begin(115200);
  //waitForSerial(2000, &Serial);

  pinMode(EXP_LED, OUTPUT);

  // Setup debug output
  Debug.setDebugOutputStream(&Serial);
  Debug.setDebugLevel(DBG_VERBOSE);
  Debug.timestampOn();

  setupData();
  carSetup();
  setupI2c();

  Serial.println(F("START MARS-Engineers expander code " __FILE__ " from " __DATE__ " FW ver.: " FW_VERSION " HW ver.: " HW_VERSION "\r\n"));


  //delay(6000);
  led.blinkNumberOfTimes(100, 100, 2);  // Blink two times
}

void loop() {
  loopI2c();  // Handle I2c que
}

void setup1() {}

void loop1() {
  led.loop();
}


// Wait for serial or timeout
void waitForSerial(const long timeout, Stream* port) {
  unsigned long previousMillis = millis();
  while (!Serial || (millis() - previousMillis) > timeout) {
    delay(1);
  }
}
