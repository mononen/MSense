#ifndef SENSE_H
#define SENSE_H

void sense_init();
void sense_loop();

void IRAM_ATTR inputPinInterrupt();

#endif // !SENSE_H