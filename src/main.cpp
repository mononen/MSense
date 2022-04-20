#include <Arduino.h>

#include "sense.h"

extern "C" void setup() {
  sense_init();
}

extern "C" void loop() {
  sense_loop();
}