#include <Arduino.h>
#include <pulse.h>

#include "sense.h"

#define inPin 12 //gpio pin 5, marked as D1 on the board

#define buflen 10
Pulse pulseArr [buflen] = Pulse(0);
int bufptr = 0;

Pulse ptmp = Pulse(0);

void inputPinInterrupt() {
  if (digitalRead(inPin) == HIGH) {
    ptmp.setFallingEnd(micros()); //set falling end time for previous pulse
    memcpy(&pulseArr[bufptr % buflen], &ptmp, sizeof(Pulse)); //copy temporary pulse to current pulse
    bufptr++; //increment buffer pointer
    ptmp = Pulse(micros()); //new pulse
  } else {
    ptmp.setFalling(micros()); //set falling time for current pulse
  }
}

void sense_init() {
  delay(3000);

  ptmp = Pulse(100);

  Serial.begin(921600);
  pinMode(inPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  //hooks interrupt to pin
  attachInterrupt(digitalPinToInterrupt(inPin), inputPinInterrupt, CHANGE);
}

int readPtr = 0;
Pulse p = Pulse(0);

void sense_loop() {

  while (readPtr < bufptr) {
    p = pulseArr[readPtr % buflen];
    digitalWrite(LED_BUILTIN, HIGH);
    readPtr++;
  }

  Serial.println("Nothing in queue");
  digitalWrite(LED_BUILTIN, LOW);
}