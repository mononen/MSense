#include "pulse.h"


Pulse::Pulse(unsigned long r) {
  rising = r;
}

void Pulse::fallingTime(unsigned long f) {
  falling = f;
}

int Pulse::computeTime() {
  time = (int)(falling - rising);
  return time;
}

unsigned long Pulse::getRising() {
  return rising;
}

unsigned long Pulse::getFalling() {
  return falling;
}

int Pulse::getTime() {
  return time;
}