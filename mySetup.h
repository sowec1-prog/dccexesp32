// ESP32-S3 sensor configuration
//
// The previous Arduino Mega mapping is preserved in mySetup.mega-legacy.h.
// GPIO 23, 24 and 25 from that mapping are not available as usable header pins
// on the standard ESP32-S3 DevKitC-1, so the old numbers must not be copied.
//
// For each sensor, wire a 3.3 V-safe output to a selected ESP32-S3 GPIO and
// then uncomment exactly one line.  The first number is the Rocrail sensor ID;
// the second number is the actual ESP32-S3 GPIO.
//
// SETUP("<S 23 GPIO_NUMBER 1>");
// SETUP("<S 24 GPIO_NUMBER 1>");
// SETUP("<S 25 GPIO_NUMBER 1>");
// SETUP("<S 26 GPIO_NUMBER 1>");
// SETUP("<S 27 GPIO_NUMBER 1>");
// SETUP("<S 28 GPIO_NUMBER 1>");
// SETUP("<S 29 GPIO_NUMBER 1>");
// SETUP("<S 30 GPIO_NUMBER 1>");
// SETUP("<S 31 GPIO_NUMBER 1>");
