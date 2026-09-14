# DCC-EX pro ESP32 DevKit V1 + L298P, ovládání z Rocrailu

Funkční lokální DCC centrála pro **klasický ESP32 DevKit V1 / ESP32-WROOM** a Arduino Motor Shield s L298P. Je určená pro lokální síť a Rocrail; při startu jsou koleje bezpečně bez napětí.

> Zdrojový základ je DCC-EX (GPLv3). Tento repozitář obsahuje lokální konfiguraci pro ESP32 DevKit V1 a L298P.

## Ověřený stav

- PlatformIO sestavení pro `ESP32` proběhlo úspěšně na Arduino-ESP32 2.0.16 / ESP-IDF 4.4 (`espressif32 @ 6.7.0`).
- DCC výstup ověřen dekodérem: lokomotiva reagovala na F0 (světla).
- Rocrail je připojen přes TCP port `2560`.
- Zapojení A0 → GPIO36 je v tomto vydání sestavené, ale proudovou kalibraci a skutečné vypnutí při zkratu je potřeba ověřit samostatně na kolejích.

## Zapojení kanálu MAIN / A

| ESP32 DevKit V1 | L298P Arduino Motor Shield | Význam |
|---|---|---|
| GND | GND | společná signálová zem |
| GPIO4 | D3 / PWM-A | povolení můstku |
| GPIO5 | D12 / DIR-A | DCC fáze |
| GPIO18 | D9 / BRAKE-A | brzda můstku |
| VP / GPIO36 | výstup děliče z A0 | měření proudu MAIN |

### A0 a napěťový dělič

`A0` ze shieldu může mít až 5 V a **nesmí jít přímo do ESP32**.

```text
Shield A0 → vstup děliče 10 kΩ / 20 kΩ → výstup děliče → VP / GPIO36
Shield GND ───────────────────────────────────────────→ GND ESP32
```

GPIO36/VP je pouze vstup, proto je pro analogové měření vhodný.

## Napájení a bezpečnost

- Shield a ESP32 musí mít společné GND.
- Nikdy nepropojuj `5V` shieldu s `3V3` ESP32.
- Při USB napájení ESP32 lze napájet pouze logiku shieldu ve směru `ESP32 5V/VBUS → shield 5V`; nikdy opačně.
- Než připojíš samostatné motorové napájení, ověř, že se jeho `Vin` nevrací do USB/ESP32.
- Firmware nezačne s napětím na MAIN automaticky. Napájení kolejí zapínej až z Rocrailu.

## Nastavení pro GitHub a vlastní síť

Soubor `config.h` je záměrně ignorovaný Gitem, aby se do GitHubu neuložilo Wi-Fi heslo.

1. Zkopíruj `config.h.example` jako `config.h`.
2. Doplň název a heslo své 2,4GHz Wi-Fi.
3. Ponech `WIFI_FORCE_AP false` pro připojení do domácí LAN.

## Sestavení

Nainstaluj PlatformIO a v kořeni projektu spusť:

```bash
platformio run -e ESP32
```

Výsledek je v `.pio/build/ESP32/firmware.bin`. Tento soubor se do GitHubu běžně nedává, protože firmware s `config.h` může obsahovat Wi-Fi údaje.

## Nahrání

ESP32 DevKit V1 může vyžadovat ruční režim nahrávání:

1. Podrž **BOOT**.
2. Spusť upload pro příslušný sériový port.
3. Po dokončení BOOT pusť; pokud je potřeba, krátce stiskni **EN/RESET**.

Příklad pro Windows:

```bash
platformio run -e ESP32 --target upload --upload-port COM17
```

## Nastavení Rocrailu

V Rocrailu nastav digitální centrálu:

| Položka | Hodnota |
|---|---|
| Knihovna | `dccpp` |
| Rozhraní | TCP |
| Host | DHCP IP ESP32 nebo `dccex-devkit.local`, pokud funguje mDNS |
| Port | `2560` |
| Zapnout výkon při startu | ne |

Po změně IP adresy ESP32 uprav host v `rocrail.ini` a restartuj Rocrail. Teprve potom zapni napájení kolejí z Rocview.
