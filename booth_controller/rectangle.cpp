#include <stdint.h>
#include "rectangle.h"
#include <Arduino.h> //debug

//uint16_t Rectangle::id_ = 0;

Rectangle::Rectangle(int start, int count){
  global_start_ = start;
  count_ = count;
  global_stop_ = global_start_ + count_;
  // Serial.println(id_);
  // id_++;
} 

void Rectangle::dmx_update(uint8_t r, uint8_t g, uint8_t b){
  Serial.print("Writing: 0x");
  Serial.print(r, HEX);
  Serial.print(g, HEX);
  Serial.println(b, HEX);
  for (int i = 0; i < count_; i++){
    leds_[i] = CRGB(r, g, b);
  }
}

void Rectangle::update(uint32_t tick){
  static uint8_t rval, bval, gval;
  static float j[3] = {0};
  for (int i = 0; i < count_; i++){
    rval = amplitude_[0] * (1 + sin(2 * PI * (tick + j[0]) * frequency_[0]))/2.0;
    gval = amplitude_[1] * (1 + sin(2 * PI * (tick + j[1]) * frequency_[1]))/2.0;
    bval = amplitude_[2] * (1 + sin(2 * PI * (tick + j[2]) * frequency_[2]))/2.0;
    j[0] += offset_[0];
    j[1] += offset_[1];
    j[2] += offset_[2];
    leds_[i] = CRGB(rval, gval, bval);
  }
}
