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
  // Serial.print("Writing: 0x");
  // Serial.print(r, HEX);
  // Serial.print(g, HEX);
  // Serial.println(b, HEX);
  for (int i = 0; i < count_; i++){
    leds_[i] = CRGB(r, g, b);
  }
}