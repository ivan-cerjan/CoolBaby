# CoolBaby 🍼❄️

An ESP32 device that reads baby food temperature with a no-contact IR sensor and blows a fan until it's safe to serve.

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Framework](https://img.shields.io/badge/framework-Arduino-teal)
![Build](https://img.shields.io/badge/build-PlatformIO-orange)

## Why

I got tired of blowing on my kid's food like a human fan. Turns out I had spare ESP32s lying around from another project, so here we are.

## Quick Look

- **What it does:** Points at food, tells you its temperature, and blasts it with a fan until it's safe to shove in a toddler's mouth
- **Hardware:** ESP32 + MLX90614 IR temperature sensor + TFT display + relay-controlled fan
- **Software:** VSCode + PlatformIO

## Features

- Non-contact temperature reading via the MLX90614 IR sensor (I2C), no need to poke the food
- Live temperature readout on a TFT display
- Fan kicks in automatically once the food's too hot, no button pressing required
- Non-blocking main loop, because `delay()` is for cowards

## Hardware

| Component | Model |
|---|---|
| Microcontroller | ESP32 Board (ELEGOO ESP-WROOM-32) |
| Temperature sensor | Hailege MLX90614 non-contact IR sensor |
| Display | 1.8" TFT LED display (GERUI 128x160, ST7735 driver) |
| Relay | ELEGOO 4-Channel 5V Relay Module (way overkill for one fan, but it's what I had) |
| Fan | Any 5V DC cooling fan (I'm using a 30-40mm one) |

## Testing hardware

Each component has its own standalone test in `test/`, handy for figuring out which wire you messed up without running the whole thing.

```bash
pio run -e test_sensor --target upload    # MLX90614 sensor only
pio run -e test_display --target upload   # TFT display only
pio run -e test_relay --target upload     # Relay/fan only

pio device monitor
```

## Wiring diagram

<table>
<tr valign="top">
<td>

**MLX90614 (I2C)**

| Sensor | ESP32 |
|---|---|
| VIN | 3V3 |
| GND | GND |
| SDA | D21 |
| SCL | D22 |

</td>
<td>

**Display (SPI)**

| Display | ESP32 |
|---|---|
| GND | GND |
| VCC | 3V3 |
| SCL | D18 |
| SDA | D23 |
| RES | D4 |
| DC | D2 |
| CS | D5 |
| BLK | 3V3 |

</td>
<td>

**Relay (fan)**

| Relay | ESP32 |
|---|---|
| VCC | 5V (VIN) |
| GND | GND |
| IN1 | D25 |

</td>
</tr>
</table>

Fan connects through the relay's NO/COM contacts, powered from the same 5V source as the ESP32.

## Getting Started

### Prerequisites

- ESP32 board, MLX90614 sensor, TFT display, and relay wired per the diagram above
- [PlatformIO](https://platformio.org/) (VSCode extension or CLI)

### Setup

1. Clone the repository
2. Build, upload, open the serial monitor:
```bash
   pio run --target upload
   pio device monitor
```
   or use the PlatformIO extension for VSCode, seriously it's great

## Project Structure
```
CoolBaby/
├── include/
├── src/
│ └── main.cpp # Main application logic
├── test/
│ ├── test_sensor.cpp # Standalone MLX90614 sensor test
│ ├── test_display.cpp # Combined sensor + display test
│ └── test_relay.cpp # Standalone relay/fan test
├── platformio.ini # PlatformIO project configuration
├── README.md
└── .gitignore
```


## Roadmap

- [ ] Hysteresis to avoid relay flickering near threshold
- [ ] Adjustable temperature threshold with hardware 
- [ ] Status LED indicator indicating hot/cold
- [ ] Stronger fan for better airflow, possibly a 12V one

## License

MIT
