#ifndef __NEO_H__
#define __NEO_H__

#include <FastLED.h>

#include "rectangle.h"

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60
#define CONTROL_PIN 6

enum class Color {
  RED = 0, 
  GREEN = 1, 
  BLUE = 2,
  // Below are state machine hackery
  PIXEL = 3, 
  NONE = 4
};

enum class Algo {
  NONE = 0,
  SINE = 1
};

class Neo {
public:
  Neo(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  void enqueue_message(char * buff, int size);
  void tick();
private:
  CRGB leds_[LED_COUNT];
  int control_pin_;

  Rectangle rects_[4];
};

#endif /* __NEO_H__ */