#ifndef SENSE_H
#define SENSE_H

void sense_init();
void sense_loop();

void IRAM_ATTR risingInterrupt();

#endif // !SENSE_H