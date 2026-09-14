# Port status: ESP32-S3 N16R8

## Verified software target

- PlatformIO environment: `ESP32-S3-N16R8`
- Chip: ESP32-S3, 240 MHz
- Flash: 16 MB in QIO mode
- PSRAM: 8 MB in OPI mode
- Arduino framework: Espressif32 platform 6.7.0 / Arduino-ESP32 2.0.16 (IDF 4.4.7)

This project intentionally stays on Arduino-ESP32 2.x because its DCC RMT driver uses the IDF 4 RMT API. Arduino-ESP32 3.x / IDF 5 is not compatible with this source yet.

## Hardware configuration

The firmware is configured for an **L298P Arduino Motor Shield** connected to the ESP32-S3 by jumper wires, with 1.5 A current protection and 3.3 V-safe current-sense dividers. The exact pin map and safe power-up procedure are in `CONNECTIONS_L298P.md`.

Wi-Fi credentials and the network host name are stored privately in `config.h`; do not publish that file.

The original Arduino Mega occupancy-sensor mapping is kept in `mySetup.mega-legacy.h`. Add the ESP32-S3 GPIO mapping to `mySetup.h` only after the actual sensor wiring is known.

## Build

```bash
uv tool run platformio run -e ESP32-S3-N16R8
```

The firmware binary will be placed under `.pio/build/ESP32-S3-N16R8/`.
