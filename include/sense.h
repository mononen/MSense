#ifndef SENSE_H
#define SENSE_H

struct Pulse {
  unsigned long rising;
  unsigned long falling;
  int time;
};

void sense_init();
void sense_loop();

void IRAM_ATTR pinInterrupt();

#endif // !SENSE_H