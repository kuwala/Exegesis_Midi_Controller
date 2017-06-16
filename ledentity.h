#ifndef LEDENTITY_H
#define LEDENTITY_H
// #include <Adafruit_NeoPixel.h>
#include "FastLED.h"
// #define NUM_LEDS 8
#endif

class LEDEntity {
  int state;
  CRGB* leds;
  LEDEntity(CRGB* setLeds) {
    leds = setLeds;
    state = 0;
  }
  void update() {
    state = ((state+1) % 2);
  }
  void draw() {
    if(state==1) {
      // strip_p->setPixelColor(index, strip_p->Color(255,0,0));
      leds[0] = CRGB::Red;
    } else {
      leds[0] = CRGB::Black;
      // strip_p->setPixelColor(index, strip_p->Color(0,0,255));
    }

  }



};
//
// #endif
