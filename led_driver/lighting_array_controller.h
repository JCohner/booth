#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <FastLED.h>
#include "rectangle.h"

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 339
#define CONTROL_PIN 7
#define NUM_RECTANGLES 16

class LightingArrayController {
public:
  LightingArrayController(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  // void enqueue_message(char * buff, int size); // rellic
  void dmx_update(uint8_t* dmx_frame, uint16_t num_channels);
  void tick();
private:
  CRGB leds_[LED_COUNT];
  int control_pin_;

  Rectangle rects_[NUM_RECTANGLES];
};

#endif /* __CONTROLLER_H__ */