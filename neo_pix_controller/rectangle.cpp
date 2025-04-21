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
  // if (j++ % 10 == 0){
  //   // char buff[50];
  //   // sprintf(buff, "wrote to address %X", leds_);
  //   Serial.println((int)leds_);
  // }
  // if (j++ % 10 == 0){
  //   Serial.print(leds_[0].r);
  //   Serial.print("\t");
  //   Serial.print(leds_[0].g);
  //   Serial.print("\t");
  //   Serial.print(leds_[0].b);
  //   Serial.println();
  // }
  // Serial.print(frequency_[0]);
  // Serial.print("\t");
  // Serial.print(frequency_[1]);
  // Serial.print("\t");
  // Serial.print(frequency_[2]);
  // Serial.println();
}
