# ESP32 DevKit V1 — safe DCC-EX commissioning build

This folder builds DCC-EX for a **classic ESP32 DevKit V1 / ESP32-WROOM**.

## Verified build target

- PlatformIO environment: `ESP32`
- Board definition: `esp32dev`
- Framework: Arduino-ESP32 2.0.16 / ESP-IDF 4.4 (`espressif32 @ 6.7.0`)
- Serial port to use after build: `COM17`

## Channel A wiring (L298P Arduino Motor Shield)

| ESP32 DevKit GPIO | Shield pin | Purpose |
|---:|---|---|
| GND | GND | shared signal ground |
| GPIO4 | D3 / PWM-A | bridge enable |
| GPIO5 | D12 / DIR-A | DCC phase |
| GPIO18 | D9 / BRAKE-A | bridge brake |

Leave **A0 and A1 disconnected** for the first commissioning build. They can be 5 V outputs and must never go directly to ESP32 GPIO. Before locomotive operation, connect A0 through a 10 kΩ / 20 kΩ divider to GPIO36 and change the current-sense setting.

## Power safety

- Do not connect shield `5V` to ESP32 `3V3`.
- With USB powering ESP32, only `ESP32 5V/VBUS -> shield 5V logic` is allowed; never reverse it.
- Shield and ESP32 must share GND.
- Verify the shield's `Vin` trace is isolated before external motor power is attached.
- The firmware does **not** enable MAIN automatically. Do not test with a locomotive until the physical output is checked.

## First network access

At boot it creates only the local access point `DCC-EX-DEVKIT` (password `dcc-test-2026`) and listens on TCP port 2560. This avoids storing home Wi-Fi credentials while commissioning.

## Build and upload

```bash
platformio run -e ESP32
platformio run -e ESP32 --target upload --upload-port COM17
```

The build must finish before upload. Upload success alone does not prove DCC waveform or safe shield wiring.
