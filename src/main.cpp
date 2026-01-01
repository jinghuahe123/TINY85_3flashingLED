#include <Arduino.h>

/*
  Features to add?
   - shift register for more led
   - more efficient pwm with direct register manipulation
*/

#define LED_COUNT 3
#define GND_COUNT 2 // for digispark tiny85 w.o. adapter (data pins on breadboard only)

const int ledPins[LED_COUNT] = {0, 1, 4};
unsigned long previousMillis[LED_COUNT] = {0};
unsigned long intervals[LED_COUNT] = {2, 3, 5}; // unsigned long for time value even though it will never increment above 5
int brightness[LED_COUNT] = {0};
int currentBrightness[LED_COUNT] = {0};

const int gndPins[GND_COUNT] = {2, 3};

int updateLED(int index, unsigned long currentMillis) {
  if (currentMillis - previousMillis[index] >= intervals[index]) {
    previousMillis[index] = currentMillis;
    
    if (currentBrightness[index] < brightness[index]) {
      currentBrightness[index]++;
      analogWrite(ledPins[index], currentBrightness[index]);
    } 
    else if (currentBrightness[index] > brightness[index]) {
      currentBrightness[index]--;
      analogWrite(ledPins[index], currentBrightness[index]);
    } 
    else {
      brightness[index] = random(256);
      intervals[index] = random(1, 6);
    }
  }

  return currentBrightness[index];
}

void setup() {
  for(int i=0; i<LED_COUNT; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  for (int i=0; i<GND_COUNT; i++) {
    pinMode(gndPins[i], OUTPUT);
    digitalWrite(gndPins[i], LOW);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  for(int i=0; i<LED_COUNT; i++) {
    updateLED(i, currentMillis);
  }
}

