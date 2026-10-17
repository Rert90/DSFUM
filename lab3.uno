const int pins[6] = {8, 9, 10, 11, 12, 13};

int anim[6] = {0, 0, 0, 0, 0, 0};
unsigned long duration[6] = {1000, 1000, 1000, 1000, 1000, 1000};
unsigned long tStart[6] = {0, 0, 0, 0, 0, 0};
byte brightness[6] = {0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    int p = Serial.parseInt();
    Serial.read();
    String tip = Serial.readStringUntil(',');
    tip.trim();
    long t = Serial.parseInt();
    if (t <= 0) t = 1000;

    int idx = p - 8;
    if (idx >= 0 && idx < 6) {
      duration[idx] = t;
      tStart[idx] = millis();

      if (tip == "off")        anim[idx] = 0;
      else if (tip == "fadein")    anim[idx] = 1;
      else if (tip == "fadeout")   anim[idx] = 2;
      else if (tip == "fadeinout") anim[idx] = 3;
      else if (tip == "blink")     anim[idx] = 4;
    }
  }

  unsigned long now = millis();
  for (int i = 0; i < 6; i++) {
    if (anim[i] == 0) {
      brightness[i] = 0;
      continue;
    }

    unsigned long elapsed = (now - tStart[i]) % duration[i];

    if (anim[i] == 1) {
      brightness[i] = (elapsed * 255UL) / duration[i];
    } 
    else if (anim[i] == 2) {
      brightness[i] = 255 - ((elapsed * 255UL) / duration[i]);
    } 
    else if (anim[i] == 3) {
      unsigned long jumatate = duration[i] / 2;
      if (elapsed < jumatate)
        brightness[i] = (elapsed * 255UL) / jumatate;
      else
        brightness[i] = 255 - (((elapsed - jumatate) * 255UL) / jumatate);
    } 
    else if (anim[i] == 4) {
      brightness[i] = (elapsed < duration[i] / 2) ? 255 : 0;
    }
  }

  static byte pwmCounter = 0;
  pwmCounter++;
  for (int i = 0; i < 6; i++) {
    digitalWrite(pins[i], brightness[i] > pwmCounter ? HIGH : LOW);
  }
}
