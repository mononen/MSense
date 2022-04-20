#include <Arduino.h>
#include <pulse.h>
#include <queue>

#include "sense.h"

#define inPin 5 //gpio pin 5, marked as D1 on the board

std::vector<Pulse> pulseList; 

void risingInterrupt() {
  pulseList.insert(pulseList.begin(), Pulse(micros()));
}

void sense_init() {
  delay(3000);

  //init the queue of pulses
  pulseList = std::vector<Pulse>();

  Serial.begin(115200);
  pinMode(inPin, INPUT);

  // pinMode(LED_BUILTIN, OUTPUT);

  //hooks interrupt to pin
  attachInterrupt(digitalPinToInterrupt(inPin), risingInterrupt, RISING);

}

void sense_loop() {

  while(!pulseList.empty()) {
    Pulse p = pulseList[0]; //gets the first pulse in the queue data
    // int t = p.computeTime(); //computes the time of the pulse
    pulseList.erase(pulseList.begin()); //erases the pulse from the list
    // digitalWrite(LED_BUILTIN, HIGH);
    // Serial.println("pulse");
    Serial.println("----Pulse found with rising: " + String(p.getRising()));
    // p.log(); //prints the pulse to the serial monitor
  }
  Serial.println("N");
  // digitalWrite(LED_BUILTIN, LOW);
}