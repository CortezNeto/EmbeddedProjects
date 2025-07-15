#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3); // RX, TX

void setup() {
  espSerial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(8, HIGH);
}

void loop() {
  if (espSerial.available()) {
    String comando = espSerial.readStringUntil('\n');
    Serial.println(comando);
    comando.trim();
    Serial.println(comando);
    if (comando == "on") {
      digitalWrite(13, HIGH);
      Serial.println("on");
      for(int i = 0; i < 6400; i++) {
        digitalWrite(9, LOW);
        delayMicroseconds(50);
        digitalWrite(9, HIGH);
        delayMicroseconds(50);
      }
    } else if (comando == "off") {
      digitalWrite(13, LOW);
      Serial.println("off");
    } 
  } else {
    Serial.println("Error");
    delay(1000);
  }
}
