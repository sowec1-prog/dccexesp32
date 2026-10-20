#ifndef DCCEX_OTA_SERVICE_H
#define DCCEX_OTA_SERVICE_H

/*
 * Optional LAN-only Arduino OTA service for the ESP32 command station.
 * It is compiled only when ENABLE_OTA is true in the ignored config.h.
 *
 * The normal DCC-EX mDNS responder is already started by WifiESP, so
 * ArduinoOTA's own mDNS start is disabled. Upload by the ESP's LAN IP.
 */
#if defined(ARDUINO_ARCH_ESP32) && defined(ENABLE_OTA) && ENABLE_OTA

#include <ArduinoOTA.h>

#ifndef OTA_HOSTNAME
  #error "ENABLE_OTA requires OTA_HOSTNAME in config.h"
#endif
#ifndef OTA_PASSWORD_HASH
  #error "ENABLE_OTA requires OTA_PASSWORD_HASH in config.h"
#endif
#ifndef OTA_PORT
  #define OTA_PORT 3232
#endif

namespace OtaService {

inline bool& started() {
  static bool value = false;
  return value;
}

inline void begin() {
  // Do not offer firmware upload when the command station fell back to AP mode.
  if (WiFi.status() != WL_CONNECTED) {
    DIAG(F("OTA disabled: WiFi station is not connected"));
    return;
  }

  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPort(OTA_PORT);
  ArduinoOTA.setPasswordHash(OTA_PASSWORD_HASH);
  // WifiESP already owns mDNS for the DCC-EX hostname.
  ArduinoOTA.setMdnsEnabled(false);

  ArduinoOTA.onStart([]() {
    // A firmware write must never leave traction power enabled.
    TrackManager::setTrackPower(TRACK_ALL, POWERMODE::OFF);
    CommandDistributor::broadcastPower();
    DIAG(F("OTA start: all track power forced OFF"));
  });
  ArduinoOTA.onEnd([]() {
    DIAG(F("OTA complete: rebooting into the new firmware"));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    DIAG(F("OTA error %u; existing firmware remains active"), (unsigned)error);
  });

  ArduinoOTA.begin();
  started() = true;
  DIAG(F("OTA ready on LAN port %d"), OTA_PORT);
}

inline void loop() {
  if (started()) ArduinoOTA.handle();
}

}  // namespace OtaService

#else

namespace OtaService {
inline void begin() {}
inline void loop() {}
}  // namespace OtaService

#endif  // ESP32 && ENABLE_OTA
#endif  // DCCEX_OTA_SERVICE_H
