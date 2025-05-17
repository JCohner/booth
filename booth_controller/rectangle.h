#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include <stdint.h>
#include <FastLED.h>

class Rectangle {
public:
  Rectangle() {}
  Rectangle(int start, int count);
  int count(){return count_;}
  int global_start() {return global_start_;}
  int global_stop() {return global_stop_;}
  void update(uint32_t tick);
  void dmx_update(uint8_t r, uint8_t g, uint8_t b);
  void set_amplitude(int idx, float value) {amplitude_[idx] = value;}
  void set_frequency(int idx, float value) {frequency_[idx] = value;}
  void set_offset(int idx, float value) {offset_[idx] = value;}
  CRGB* leds_;
private:
  static uint16_t id_;
  int global_start_;
  int global_stop_;
  int count_;
  float amplitude_[3];
  float frequency_[3];
  float offset_[3];
};

#endif /* __RECTANGLE_H__ */