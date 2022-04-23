#include <Arduino.h>

#include "sense.h"

void setup() {
  sense_init();
}

 void loop() {
  sense_loop();
}