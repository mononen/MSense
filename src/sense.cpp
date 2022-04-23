#include <Arduino.h>
#include <pulse.h>
#include <queue>

#include "sense.h"

#define inPin 12 //gpio pin 5, marked as D1 on the board

#define buflen 10
Pulse pulseArr [buflen] = Pulse(0);
int bufptr = 0;

Pulse ptmp = Pulse(0);

void inputPinInterrupt() {
  if (digitalRead(inPin) == HIGH) {
    ptmp.setFallingEnd(micros()); //set falling end time for previous pulse
    memcpy(&ptmp, &pulseArr[bufptr % buflen], sizeof(Pulse)); //copy previous pulse to temporary pulse
    bufptr++; //increment buffer pointer
    ptmp = Pulse(micros()); //new pulse
  } else {
    ptmp.setFalling(micros()); //set falling time for current pulse
  }
}

void sense_init() {
  delay(3000);

  ptmp = Pulse(100);

  Serial.begin(115200);
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
    Serial.print(p.getTime());
    Serial.print("\t");
    Serial.print(p.getRising());
    Serial.print("\t");
    Serial.print(p.getFalling());
    Serial.print("\t");
    Serial.print(p.getFallingEnd());
    Serial.print("\n");
    Serial.println(String(readPtr) + " " + String(bufptr));
    readPtr++;
  }

  Serial.println("Nothing in queue");
  digitalWrite(LED_BUILTIN, LOW);
}