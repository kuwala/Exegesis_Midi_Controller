#include <Arduino.h>
#include "FastLED.h"
#include "ledentity.h"

#include <Bounce.h>

#define LEDPIN 1
#define NUM_LEDS 300
#define LED_STEP_WIDTH 6

#define KNOB1PIN A0
#define KNOB2PIN A1
#define KNOB3PIN A2
#define KNOB4PIN A3

unsigned long timer = 0;
unsigned long tickInterval = 50; // ms

CRGB leds[NUM_LEDS];
// LEDEntity ent = LEDEntity(&leds);

int lastNoteIndex = 0;
int ledIndex = 0;

// Midi Out Variables
elapsedMillis msec = 0; // timer
const int updateTime = 20; // 20 millis
const int channel = 1;
const int controllerA0 = 20;
const int controllerA1 = 21;
const int controllerA2 = 22;
const int controllerA3 = 23;

int knobDebounce = 6;
int a0Value = 0;
int a0Previous = 0;
int a1Value = 0;
int a1Previous = 0;
int a2Value = 0;
int a2Previous = 0;
int a3Value = 0;
int a3Previous = 0;


/* Use "Tools > USB Type > MIDI" */

void setup() {

  Serial.begin(115200);
  Serial.println("Starting Midi~>Light Thingy");

  FastLED.addLeds<NEOPIXEL, LEDPIN>(leds, NUM_LEDS);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);

}

void loop() {
  usbMIDI.read();
  // if ( millis() - timer > tickInterval) {
  //   // update all LEDEntities
  //   // updateLEDS();
  //   // ent.update();
  //   // ent.draw();
  //   timer = millis();
  // }

  if (msec > updateTime) {
    //analog read
    msec = 0;
    a0Value = analogRead(KNOB1PIN) / 8 ;
    a1Value = analogRead(KNOB2PIN) / 8 ;
    a2Value = analogRead(KNOB3PIN) / 8 ;
    a3Value = analogRead(KNOB4PIN) / 8 ;

    if(a0Value != a0Previous) {
      usbMIDI.sendControlChange(controllerA0, a0Value, channel);
      a0Previous = a0Value;

      Serial.println();
      Serial.print("Knob1 Value: ");
      Serial.println(a0Value);
    }

    if(abs(a1Value - a1Previous) > knobDebounce) {
      usbMIDI.sendControlChange(controllerA1, a1Value, channel);
      a1Previous = a1Value;

      Serial.println();
      Serial.print("Knob2 Value: ");
      Serial.println(a1Value);
    }

    if(abs(a2Value - a2Previous) > knobDebounce) {
      usbMIDI.sendControlChange(controllerA2, a2Value, channel);
      a2Previous = a2Value;

      Serial.println();
      Serial.print("Knob3 Value: ");
      Serial.println(a2Value);
    }

    if(abs(a3Value - a3Previous) > knobDebounce) {
      usbMIDI.sendControlChange(controllerA3, a3Value, channel);
      a3Previous = a3Value;

      Serial.println();
      Serial.print("Knob4 Value: ");
      Serial.println(a3Value);
    }

  }
  while (usbMIDI.read()) {
    /* code */
  }

}

void allOff() {
  for (size_t i = 0; i < NUM_LEDS; i++) {
    // strip.setPixelColor(i, strip.Color(0,0,0));
  }
}

int randomColor() {
  // return strip.Color(random(255),random(255),random(255));
  return 0;
}
void OnNoteOn(byte channel, byte note, byte velocity) {
  // Turn on lights
  // lastNoteIndex = ledIndex;
  ledIndex = (int)note*6 % NUM_LEDS;
  int brightness = velocity * 2;
  Serial.println(velocity);
  Serial.println(channel);
  // strip.setPixelColor(lastNoteIndex, strip.Color(0,0,0));
  // strip.setPixelColor(ledIndex, randomColor());
  // strip.show();
  // leds[lastNoteIndex] = CRGB::Black;

  //set color based on channel
  if (channel == B00000001) {
    // leds[ledIndex].r = brightness;
    setLEDS(leds, ledIndex, 0, brightness);
  } else if ( channel == B00000010) {
    // leds[ledIndex].b = brightness;
    setLEDS(leds, ledIndex, 1, brightness);
  } else if ( channel == B00000011) {
    setLEDS(leds, ledIndex, 2, brightness);
    // leds[ledIndex].g = brightness;
  } else {
    setLEDS(leds, ledIndex, 0, brightness);
    // leds[ledIndex].r = brightness;

  }
  FastLED.show();
  Serial.print("note on");

}
void setLEDS(CRGB* leds, int ledIndex, int rgbIndex, int brightness) {
  leds[ledIndex][rgbIndex] = brightness;
  for (size_t width = 0; width < LED_STEP_WIDTH; width++) {
    int newLEDIndex = (ledIndex + width) % NUM_LEDS;
    leds[newLEDIndex][rgbIndex] = brightness;
  }
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  // Turn off last Light
  int brightness = 0;
  ledIndex = (int)note*6 % NUM_LEDS;
  if (channel == B00000001) {
    // red off
    setLEDS(leds, ledIndex, 0, brightness);
  } else if ( channel == B00000010) {
    // green off
    setLEDS(leds, ledIndex, 1, brightness);
  } else if ( channel == B00000011) {
    // blue off
    setLEDS(leds, ledIndex, 2, brightness);
  } else {
    // red off
    setLEDS(leds, ledIndex, 0, brightness);

  }
  FastLED.show();
}
