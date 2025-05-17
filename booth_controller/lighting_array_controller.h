#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <FastLED.h>
#include "rectangle.h"

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60
#define CONTROL_PIN 6
#define NUM_RECTANGLES 5

class LightingArrayController {
public:
  LightingArrayController(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  void enqueue_message(char * buff, int size);
  void tick();
private:
  CRGB leds_[LED_COUNT];
  int control_pin_;

  Rectangle rects_[NUM_RECTANGLES];
};

#endif /* __CONTROLLER_H__ */