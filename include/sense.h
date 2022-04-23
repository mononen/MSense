#ifndef SENSE_H
#define SENSE_H

struct Pulse {
  unsigned long rising;
  unsigned long falling;
  unsigned long fallingEnd;
};

void sense_init();
void sense_loop();

void IRAM_ATTR pinInterrupt();

void boot_sequence(); //boot sequence lighting
void renderLEDs();
int computeMPH(unsigned long time);
int cleanDutyCycle(int dutyCycle);
int calcMax(int arr[], int size);

#endif // !SENSE_H