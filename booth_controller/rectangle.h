#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <stdint.h>
#include <FastLED.h>

class Rectangle {
public:
  Rectangle() {}
  Rectangle(int start, int count);
  int count(){return count_;}
  void dmx_update(uint8_t r, uint8_t g, uint8_t b);
  CRGB* leds_;
  static volatile uint8_t master_dimmer_; 
private:
  int global_start_;
  int global_stop_;
  int count_;
};

#endif /* __RECTANGLE_H__ */