#ifndef SENSE_H
#define SENSE_H

void sense_init();
void sense_loop();

void boot_sequence(); //boot sequence lighting
void renderLEDs(int dutyCycle, int mph);
int computeMPH(unsigned long time);
int cleanDutyCycle(int dutyCycle);
int calcMax(int arr[], int size);

#endif // !SENSE_H