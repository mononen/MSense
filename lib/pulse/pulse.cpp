#include "pulse.h"


Pulse::Pulse(unsigned long r) {
  rising = r;
}

void Pulse::fallingTime(unsigned long f) {
  falling = f;
}

int Pulse::computeTime() {
  time = falling - rising;
  return (int)time;
}
