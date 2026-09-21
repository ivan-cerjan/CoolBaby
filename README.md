# CoolBaby

An ESP32-based device that reads baby food temperature with a no contact IR sensor and blows a fan until it's safe to serve.

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Framework](https://img.shields.io/badge/framework-Arduino-teal)
![Build](https://img.shields.io/badge/build-PlatformIO-orange)

## Why
I'm tired of blowing on my kids food all the time.

## Quick Look

- **What it does:** Measures food temperature without touching it, shows it live on a TFT screen, and runs a fan automatically until the food cools to a safe temperature
- **Hardware:** ESP32 + MLX90614 IR temperature sensor + TFT display + relay-controlled fan
- **Software:** Built with VSCode + PlatformIO

## Features

- Non-contact temperature reading via the MLX90614 IR sensor (I2C)
- Live temperature readout on a TFT display
- Automatic fan control via relay once a temperature threshold is exceeded
- Non-blocking main loop using `millis()` timing

## Hardware

| Component | Model |
|---|---|
| Microcontroller | ESP32 Board (ELEGOO ESP-WROOM-32) |
| Temperature sensor | Hailege MLX90614 non-contact IR sensor |
| Display | 1.8" TFT LED display (GERUI 128x160, ST7735 driver) |
| Relay | ELEGOO 4-Channel 5V Relay Module (probably an overkill but it's what I had) |
| Fan | Any 5V DC cooling fan (I use 30-40mm) |

## Testing hardware

Each hardware component has a standalone test in `test/`, useful for isolating wiring issues without running the full application.

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

- [PlatformIO](https://platformio.org/) (VSCode extension or CLI)
- ESP32 board, MLX90614 sensor, TFT display, and relay wired per the diagram above

### Setup

1. Clone the repository
2. Build, upload, open the serial monitor:
```bash
   pio run --target upload
   pio device monitor
```
   or use the PlatformIO extension for VSCode

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
- [ ] Adjustable temperature threshold
- [ ] Status LED indicator
- [ ] Stronger fan for better airflow

## License

MIT
