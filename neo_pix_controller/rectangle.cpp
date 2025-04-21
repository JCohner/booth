#include <stdint.h>
#include "rectangle.h"
#include <Arduino.h> //debug

void Rectangle::update(uint32_t tick){
  static uint8_t rval, bval, gval;
  for (int i = 0; i < count_; i++){
    int j = 0;
    rval = amplitude_[0] * (1 + sin(2 * M_PI * (tick + j) * frequency_[0]))/2.0;
    gval = amplitude_[1] * (1 + sin(2 * M_PI * (tick + j) * frequency_[1]))/2.0;
    bval = amplitude_[2] * (1 + sin(2 * M_PI * (tick + j) * frequency_[2]))/2.0;
    j += 10;
    leds_[i] = CRGB(rval, gval, bval);
  }
}
