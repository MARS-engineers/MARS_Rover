#include <Preferences.h>
Preferences data;

long MEDI;
char buffer[11];
String serialData;
void setupData() {
  data.begin("Robotrix-Rover-ONE");  // use "my-app" namespace

  delay(100);
  if (not data.isKey("MEDI")) {
MEDI_JUMP:
    while (!Serial) {}
    Serial.print("Waiting for MEDI....\n");
    while (!Serial.available()) {}
    Serial.readBytesUntil('\n', buffer, 12);

    Serial.flush();
    MEDI = atol(buffer);
    Serial.printf("MEDI: %ld\n", MEDI);
    Serial.print("Correct? Y/n\n");
    while (!Serial.available()) {}
    Serial.readBytesUntil('\n', buffer, 4);
    if (buffer[0] == 'n') goto MEDI_JUMP;
    data.putLong("MEDI", MEDI);
  }
  MEDI = data.getLong("MEDI");
  Serial.printf("MEDI: %ld\n", MEDI);
}