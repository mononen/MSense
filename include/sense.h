#ifndef SENSE_H
#define SENSE_H

void sense_init();
void sense_loop();

void IRAM_ATTR pinInterrupt();

void boot_sequence(); //boot sequence lighting
void renderLEDs();
int computeMPH(unsigned long time);
int cleanDutyCycle(int dutyCycle);
int calcMax(int arr[], int size);

void taskCode( void * parameter );

#endif // !SENSE_H