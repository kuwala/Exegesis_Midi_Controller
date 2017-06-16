# Exegsis Midi controller
### Version 1:
A device to control NeoPixel Leds with midi notes. It uses
different Midi Channels 0 , 1 , 2 to control the R, G, B color
values of particular pixels on the strip.
It uses Midi Note values as the positions for a STEP of color.

## Changing number of led lights
To change the number of LEDS you plan to use change these defines
In the Exeg

```
#define NUM_LEDS 300
#define LED_STEP_WIDTH 6

```
## Libraries
FastLED
