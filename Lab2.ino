// int n = 0;
// unsigned long ultimulPas = 0;
 
// void setup() {
//   for (int i = 8; i <= 13; i++) pinMode(i, OUTPUT);
// }
 
// void loop() {
//   if (millis() - ultimulPas >= 500) {
//     ultimulPas = millis();
//     for (int i = 0; i < 6; i++) {
//       digitalWrite(8 + i, (n >> i) & 1);  
//     }
//     n = (n + 1) % 64;
//   }
// }
// void setup() {
//   for (int i = 8; i <= 13; i++) {
//     pinMode(i, OUTPUT);
//   }
//   Serial.begin(9600);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     int valoare = Serial.parseInt();

//     if (valoare >= 0 && valoare <= 63) {
//       for (int i = 0; i < 6; i++) {
//         digitalWrite(8 + i, bitRead(valoare, i));
//       }
//       Serial.println(valoare);
//     } else {
//       Serial.println("valoare invalida (0-63)");
//     }
//   }
// }
int led = 9;         
int luminozitate = 0;
int pas = 5;
unsigned long ultimulPas = 0;
 
void setup() {
  pinMode(led, OUTPUT);
}
 
void loop() {
  if (millis() - ultimulPas >= 30) {  
    ultimulPas = millis();
    analogWrite(led, luminozitate);
    luminozitate += pas;
    if (luminozitate <= 0 || luminozitate >= 255) pas = -pas;  
  }
}


// int pin = 12;
// int timpHigh = 0;
// unsigned long start = 0;

// void setup() {
//   pinMode(pin, OUTPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     float volti = Serial.parseFloat();
//     if (volti >= 0 && volti <= 5) {
//       timpHigh = volti / 5.0 * 2000;
//       Serial.println(volti);
//     }
//   }

//   if (micros() - start >= 2000) {
//     start = micros();
//   }

//   if (micros() - start < timpHigh) {
//     digitalWrite(pin, HIGH);
//   } else {
//     digitalWrite(pin, LOW);
//   }
// }
