






void setup() {
  // put your setup code here, to run once:

  // Blink at start
  pinMode(EXP_LED, OUTPUT);
  digitalWriteFast(EXP_LED, HIGH);
  delay(100);
  digitalWriteFast(EXP_LED, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
}
