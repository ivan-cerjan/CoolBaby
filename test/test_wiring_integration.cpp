#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <TFT_eSPI.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
TFT_eSPI tft = TFT_eSPI();

#define RELAY_PIN 25

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("=== Wiring Integration Test ===");

    //1. Relay pin check
    Serial.println("[1/3] Testing relay pin...");
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("[1/3] Relay pin toggled OK (check for click/LED)");

    //2. I2C sensor check
    Serial.println("[2/3] Testing I2C sensor...");
    Wire.begin(21, 22);
    if (!mlx.begin())
    {
        Serial.println("[2/3] FAILED — MLX90614 not found on I2C bus!");
        Serial.println("       Check SDA/SCL wiring, or a power rail conflict with the display/relay.");
        while (1) { delay(1000); }
    }
    Serial.println("[2/3] MLX90614 found OK");

    //3. SPI display check
    Serial.println("[3/3] Testing SPI display...");
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Wiring OK!");
    Serial.println("[3/3] Display initialized OK");

    Serial.println("=== All components responded. Check display and relay physically. ===");
}

void loop()
{
    float temp = mlx.readObjectTempC();
    Serial.print("Live reading: ");
    Serial.print(temp);
    Serial.println(" °C");
    delay(1000);
}