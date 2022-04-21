#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "sense.h"

extern "C" void setup() {
  WiFi.mode(WIFI_OFF);
  sense_init();
}

extern "C" void loop() {
  sense_loop();
}