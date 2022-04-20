#include <Arduino.h>
#include <pulse.h>
#include <queue>

#include "sense.h"

#define inPin 5 //gpio pin 5, marked as D1 on the board

std::vector<Pulse> pulseList; 

// void risingInterrupt() {
//   pulseQueue.push(Pulse(micros()));
// }

// void fallingInterrupt() {
//   pulseQueue.back().fallingTime(micros());
// }

void inputPinInterrupt() {
  if (digitalRead(inPin) == HIGH) {
    pulseList.insert(pulseList.begin(), Pulse(micros()));
    // pulseQueue.push(Pulse(micros()));
  } else {
    pulseList[pulseList.size() - 1].fallingTime(micros());
    // pulseQueue.back().falling = micros();
  }

}

void sense_init() {
  delay(3000);
  //init the queue of pulses
  pulseList = std::vector<Pulse>();

  Serial.begin(115200);
  pinMode(inPin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  //hooks interrupts to pin
  // attachInterrupt(digitalPinToInterrupt(inPin), risingInterrupt, RISING);
  // attachInterrupt(digitalPinToInterrupt(inPin), fallingInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(inPin), inputPinInterrupt, CHANGE);
}

void sense_loop() {

  while(!pulseList.empty()) {
    Pulse p = pulseList[0]; //gets the first pulse in the queue data
    p.computeTime(); //computes the time of the pulse
    pulseList.erase(pulseList.begin()); //erases the pulse from the list
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Pulse found");
    // p.log(); //prints the pulse to the serial monitor
  }
  Serial.println("Nothing in queue");
  digitalWrite(LED_BUILTIN, LOW);
}