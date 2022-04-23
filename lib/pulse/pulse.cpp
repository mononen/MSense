#include "pulse.h"


Pulse::Pulse(unsigned long r) {
  rising = r;
}

void Pulse::setFalling(unsigned long f) {
  falling = f;
}

void Pulse::setFallingEnd(unsigned long f) {
  fallingEnd = f;
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
unsigned long Pulse::getFallingEnd() {
  return fallingEnd;
}
int Pulse::getTime() {
  return time;
}