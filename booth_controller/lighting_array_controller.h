#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <FastLED.h>
#include "rectangle.h"

// Setup Custom Parameters
#define LED_COUNT 410
#define NUM_RECTANGLES 20
#define DMX_OFFSET 88
// End Custom Parameters

#define CONTROL_PIN 7
#define MASTER_DMX_DMX_CHANNEL 1 // Don't forget DMX is effectivley 1 indexed. We are putting master dimmer on Chan 1

class LightingArrayController {
public:
  LightingArrayController() {};
  void setup();
  void dmx_update(uint8_t* dmx_frame, uint16_t num_channels);
private:
  CRGB leds_[LED_COUNT];
  uint8_t master_dimmer_;
  Rectangle rects_[NUM_RECTANGLES];
};

#endif /* __CONTROLLER_H__ */