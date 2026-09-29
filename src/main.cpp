#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <TFT_eSPI.h>
#include "../include/Config.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
TFT_eSPI tft = TFT_eSPI();

unsigned long lastUpdate = 0;

void startScreen(float temp)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Food temp:");

    tft.setTextSize(3);
    tft.setCursor(10, 50);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println(temp, 1);

    tft.setTextSize(2);
    tft.setCursor(10, 100);
}

void showStatus(float temp, bool isCooling)
{
    startScreen(temp);

    if (isCooling)
    {
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.println("Cooling...");
    }
    else
    {
        tft.setTextColor(TFT_CYAN, TFT_BLACK);
        tft.println("Ready!");
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    Wire.begin(21, 22);

    if (!mlx.begin())
    {
        Serial.println("MLX90614 sensor missing");
        while (1)
        {
            delay(1000);
        }
    }

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.println("Ready!");

    Serial.println("Sensor, display and relay ready.");
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate < UPDATE_INTERVAL_MS)
    {
        return;
    }
    lastUpdate = currentMillis;

    float objectTemp = mlx.readObjectTempC();
    bool isCooling = objectTemp > TEMP_THRESHOLD;

    digitalWrite(RELAY_PIN, isCooling ? HIGH : LOW);

    showStatus(objectTemp, isCooling);

    Serial.print("Food: ");
    Serial.print(objectTemp);
    Serial.print(" °C | Fan: ");
    Serial.println(isCooling ? "ON" : "OFF");
}