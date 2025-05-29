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
  rects_[0] = Rectangle(647,22);  // rect #22
  rects_[1] = Rectangle(669,12);  // rect #33
  rects_[2] = Rectangle(681,30);  // rect #24
  rects_[3] = Rectangle(711,24);  // rect #35
  rects_[4] = Rectangle(735,36);  // rect #23
  rects_[5] = Rectangle(771,36);  // rect #25
  rects_[6] = Rectangle(807,16);  // rect #36
  rects_[7] = Rectangle(823,18);  // rect #37
  rects_[8] = Rectangle(841,20);  // rect #44
  rects_[9] = Rectangle(861,12);  // rect #38
  rects_[10] = Rectangle(873,16);  // rect #45
  rects_[11] = Rectangle(889,36);  // rect #39
  rects_[12] = Rectangle(925,14);  // rect #47
  rects_[13] = Rectangle(939,9);  // rect #40
  rects_[14] = Rectangle(948,32);  // rect #43
  rects_[15] = Rectangle(980,6);  // rect #49
  rects_[16] = Rectangle(986,16);  // rect #48
  rects_[17] = Rectangle(1002,22);  // rect #41
  rects_[18] = Rectangle(1024,22);  // rect #46
  rects_[19] = Rectangle(1046,12);  // rect #42
  // end of rectangles
  
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