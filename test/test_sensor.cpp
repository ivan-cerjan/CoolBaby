#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
    Serial.begin(115200);
    delay(1000);

    Wire.begin(21, 22); //SDA, SCL

    if (!mlx.begin()) {
        Serial.println("Can't find MLX90614 sensor. Check wires!");
        while (1) {
            delay(1000);
        }
    }

    Serial.println("MLX90614 sensor ready.");
}

void loop() {
    float objectTemp = mlx.readObjectTempC();
    float ambientTemp = mlx.readAmbientTempC();

    Serial.print("Food temp: ");
    Serial.print(objectTemp);
    Serial.print(" °C | Ambient: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");

    delay(1000);
}