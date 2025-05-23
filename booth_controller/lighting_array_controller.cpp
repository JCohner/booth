#include <Arduino.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/dtostrf.h>

#include "dmx.h"

#include "lighting_array_controller.h"

void LightingArrayController::setup(){
  FastLED.addLeds<NEOPIXEL, CONTROL_PIN>(leds_, LED_COUNT).setCorrection(TypicalLEDStrip);;  // GRB ordering is assumed
  FastLED.setBrightness( 255 );

  // setup rectangles
  rects_[0] = Rectangle(0, 18); // 1st
  rects_[1] = Rectangle(18, 16); // 2nd
  rects_[2] = Rectangle(34, 12); // 3rd 
  rects_[3] = Rectangle(46, 12); // 4th
  rects_[4] = Rectangle(58, 24); // 5th
  rects_[5] = Rectangle(82, 42); // 6th
  rects_[6] = Rectangle(124, 22); // 7th 
  rects_[7] = Rectangle(146, 17); // 8th
  rects_[8] = Rectangle(163, 16); // 9th
  rects_[9] = Rectangle(179, 18); // 10th 
  rects_[10] = Rectangle(197, 18); // 11th
  rects_[11] = Rectangle(215, 12); // 12th 
  rects_[12] = Rectangle(227, 12); // 13th 
  rects_[13] = Rectangle(239, 30); // 14th


  int gen_off = 0;
  Serial.print("leds is at: ");
  Serial.println((int)leds_);

  for (int i = 0; i < NUM_RECTANGLES; i++){
    Serial.print("Assigning ");
    Serial.println((int)(leds_ + gen_off));
    rects_[i].leds_ = leds_ + gen_off;
    gen_off += rects_[i].count();
  }
}

void LightingArrayController::dmx_update(uint8_t* dmx_frame, uint16_t channels){
  uint16_t dmx_i_ = 1;
  for (int i = 0; i < NUM_RECTANGLES; i++){
    rects_[i].dmx_update(dmx_frame[dmx_i_], dmx_frame[dmx_i_+1], dmx_frame[dmx_i_+2]);
    dmx_i_ += 3;
  }
  FastLED.show();
}