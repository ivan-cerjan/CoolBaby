#include <Arduino.h>

#define RELAY_PIN 25

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    Serial.println("Relay test ready.");
}

void loop() {
    Serial.println("Fan ON");
    digitalWrite(RELAY_PIN, HIGH);
    delay(2000);

    Serial.println("Fan OFF");
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
}