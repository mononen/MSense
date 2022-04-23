#include <Arduino.h>
#include <pulse.h>
#include <queue>

#include "sense.h"

#define inPin 12 //gpio pin 5, marked as D1 on the board

std::queue<Pulse> pulseQueue; 

Pulse ptmp = Pulse(0);

void inputPinInterrupt() {
  if (digitalRead(inPin) == HIGH) {
    ptmp.setFallingEnd(micros()); //set falling end time for previous pulse
    pulseQueue.push(ptmp); //push previous pulse to queue
    ptmp = Pulse(micros()); //new pulse
  } else {
    ptmp.setFalling(micros()); //set falling time for current pulse
  }

}

void sense_init() {
  delay(3000);
  //init the queue of pulses
  pulseQueue = std::queue<Pulse>();
  ptmp = Pulse(100);

  Serial.begin(115200);
  pinMode(inPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  //hooks interrupt to pin
  attachInterrupt(digitalPinToInterrupt(inPin), inputPinInterrupt, CHANGE);
}

void sense_loop() {

  while(!pulseQueue.empty()) {
    Pulse p = pulseQueue.front();
    pulseQueue.pop();
    p.computeTime();
    Serial.print("R: ");
    Serial.print(p.getRising());
    Serial.print(" F: ");
    Serial.print(p.getFalling());
    Serial.print(" FEnd: ");
    Serial.print(p.getFallingEnd());
    Serial.print(" T: ");
    Serial.println(p.getTime());
  }

  Serial.println("Nothing in queue");
  digitalWrite(LED_BUILTIN, LOW);
}