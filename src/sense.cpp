#include <Arduino.h>

#include "sense.h"

#define inPin 5 //gpio pin 5, marked as D1 on the board

#define pulseBufferSize 32

Pulse pulseBuffer[pulseBufferSize]; //buffer for pulse data
int pulseBufferIndex = 0; //index of the next pulse to be added to the buffer

void pinInterrupt() {
  if (digitalRead(inPin) == HIGH) { //investigate direct port read
    pulseBuffer[pulseBufferIndex].rising = micros();
    pulseBufferIndex++;
    if (pulseBufferIndex >= pulseBufferSize) {
      pulseBufferIndex = 0;
    }
  } else {
    pulseBuffer[pulseBufferIndex].falling = micros();
  }
}

void sense_init() {
  delay(3000);

  Serial.begin(115200);
  pinMode(inPin, INPUT);

  // pinMode(LED_BUILTIN, OUTPUT);

  //hooks interrupt to pin
  attachInterrupt(digitalPinToInterrupt(inPin), pinInterrupt, CHANGE);
}

Pulse p;
int idx;

void sense_loop() {

  while(pulseBuffer[pulseBufferIndex].rising != 0) {
    idx = pulseBufferIndex;
    p = pulseBuffer[idx]; //gets the first pulse in the queue data
    // Serial.println("----Pulse found with rising: " + String(p.rising) + " falling: " + String(p.falling));
    Serial.println("idx is: " + String(idx) + " rising: " + String(p.rising) + " falling: " + String(p.falling));

    pulseBuffer[idx].rising = 0; //'erases' the pulse from the list
    // p.log(); //prints the pulse to the serial monitor
  }
  // Serial.println("N");
  // digitalWrite(LED_BUILTIN, LOW);
}