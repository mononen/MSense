#include <Arduino.h>
#include <FastLED.h>

#include "sense.h"

#define inPin 5 //gpio pin 5, marked as D1 on the board

//LED driver stuff
#define ledPin 4 //gpio pin 4, marked as D2 on the board
#define numLeds 31 //number of leds in the strip
CRGB leds[numLeds]; //array of leds
#define BRIGHTNESS 50 //brightness of the leds
#define hsvGreen 100 //green hsv color value
#define hsvRed 0 //red hsv color value
int dutyLeds = 0; //number of leds to light up for the duty cycle

//Queue of pulses
#define pulseBufferSize 32
Pulse pulseBuffer[pulseBufferSize]; //buffer for pulse data
int pulseBufferIndex = 0; //index of the next pulse to be added to the buffer

//globals
int onTime, offTime, dutyCycle, dutyCycleClean, mph;
float period;

unsigned long gt, lt; //timing for greater than and less than 50% duty cycle

//duty cycle buffer stuff
#define bufLen 15 //length of the buffer
int buf[bufLen] = {0}; //buffer to write the rolling median to
int bufIdx = 0; //index of the current element in the buffer

void pinInterrupt() {
  if (digitalRead(inPin) == HIGH) { //investigate direct port read
    pulseBuffer[pulseBufferIndex].rising = micros();
  } else {
    pulseBuffer[pulseBufferIndex].falling = micros();
    pulseBuffer[pulseBufferIndex].isRead = false;
    pulseBufferIndex++;
    if (pulseBufferIndex >= pulseBufferSize) {
      pulseBufferIndex = 0;
    }
  }
}

void sense_init() {
  delay(3000);

  FastLED.addLeds<WS2812B, ledPin, GRB>(leds, numLeds); //add leds to the strip
  FastLED.setMaxRefreshRate(0, false);

  boot_sequence();

  Serial.begin(115200);
  pinMode(inPin, INPUT);

  //hooks interrupt to pin
  attachInterrupt(digitalPinToInterrupt(inPin), pinInterrupt, CHANGE);
}


void boot_sequence() { //boot sequence lighting
  for (int i = 0; i < numLeds; i++){
    leds[i] = CRGB::White; //set all leds to black
  }
  FastLED.show(); //show the leds

  delay(2000); //wait for the arduino to boot up

  for (int i = 0; i < numLeds; i++){
    leds[i] = CRGB::Black; //set all leds to black
  }
  FastLED.show(); //show the leds

  delay(1000);

  for (int i = 0; i < numLeds; i++){
    leds[i] = CRGB::Yellow; //set all leds to black
  }
  FastLED.show(); //show the leds
}

Pulse p, p2;
int idx;
bool lt50 = false; //flag for less than 50% duty cycle
float mphtmp = 0; //temporary variable for mph

unsigned long start, end;

void sense_loop() {
  idx = pulseBufferIndex;
  p2 = pulseBuffer[idx]; //gets the first pulse in the queue data
  pulseBuffer[idx].isRead = true; //'erases' the pulse from the list
  if (idx == 0) {
    p = pulseBuffer[pulseBufferSize - 1]; //gets the last pulse in the queue data
  } else {
    p = pulseBuffer[idx - 1]; //gets the previous pulse in the queue data
  }
  onTime = p.falling - p.rising; //calculates the on time
  offTime = p2.rising - p.falling; //calculates the off time
  // Serial.print("offTime: " + String(offTime) + " p2rising " + String(p2.rising) + " p.falling " + String(p.falling));
  period = (float)(offTime + onTime); //calculates the period
  dutyCycle = (onTime / period) * 100; //calculates the duty cycle
  dutyCycleClean = cleanDutyCycle(dutyCycle); //cleans the duty cycle
  // Serial.println(" onTime: " + String(onTime) + " offTime: " + String(offTime) + " dutyCycle: " + String(dutyCycle));
  
  renderLEDs(dutyCycleClean - 40, 10); //trimming the first 40% of the duty cycle
  FastLED.show();
}

//dutyCycle is the duty cycle in percent (40-100)
void renderLEDs(int dutyCycle, int mph) { 
  int dutyLeds = dutyCycle * numLeds / 100;

  for (int i = 0; i < numLeds; i++) { //span all the LEDS for drawing the duty cycle
    if (i < dutyLeds) {
      leds[i] = CHSV(hsvRed, 255, BRIGHTNESS); // make red
    } else {
      leds[i] = CHSV(hsvGreen, 255, BRIGHTNESS); //draw background green
    }
  }
  //draw the MPH
  leds[mph] = CHSV(0, 0, BRIGHTNESS); //make white
}

float mphbuf = 0.0; //buffer to store the mph

int computeMPH(unsigned long time) {
  mphbuf = (float)time * 2; //multiply by 2 to get the full cycle timing
  mphbuf = (time / 1000000.0); //convert microseconds to seconds
  mphbuf = 1.0/mphbuf; //invert
  mphbuf = mphbuf / 15.0; //divide by pole count
  mphbuf = mphbuf * 60.0; //convert to minutes

  if (mphbuf > 900) { //trying to do my best to catch erroneous readings
    return -1;
  }

  mphbuf = mphbuf * 33.0; //convert to inches per minute
  mphbuf = mphbuf / 63360.0; //convert to miles per minute
  mphbuf = mphbuf * 60.0; //convert to miles per hour

  return static_cast<int>(mphbuf);
}

int calcMax(int arr[], int size) {
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

int cleanDutyCycle(int dutyCycle) {
  buf[bufIdx] = dutyCycle;
  bufIdx++;
  if (bufIdx == bufLen) {
    bufIdx = 0;
  }
  int max = calcMax(buf, bufLen);
  if (max > 100) {
    mph = 0;
    return 0;
  } 
  return max;
}