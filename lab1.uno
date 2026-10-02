void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  if (Serial.available() > 0) {
    int sentByte = Serial.read();
    if (sentByte == '1') {
      Serial.print("pornit");
      Serial.println(sentByte);
      digitalWrite(LED_BUILTIN, HIGH);
    }
    if (sentByte == '2') {
      Serial.print("oprit");
      Serial.println(sentByte);
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (sentByte == '3') {
      Serial.print("blink");
      Serial.println(sentByte);

      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }
}
