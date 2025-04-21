#include <stdint.h>
#include "rectangle.h"
#include <Arduino.h> //debug

void Rectangle::update(uint32_t tick){
  static uint8_t rval, bval, gval;
  static uint32_t j = 0;
  for (int i = 0; i < count_; i++){
    rval = amplitude_[0] * (1 + sin(2 * M_PI * tick * frequency_[0]));
    gval = amplitude_[1] * (1 + sin(2 * M_PI * tick * frequency_[1]));
    bval = amplitude_[2] * (1 + sin(2 * M_PI * tick * frequency_[2]));
    leds_[i] = CRGB(rval, gval, bval);
  }
}
