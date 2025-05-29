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
  rects_[0] = Rectangle(0,22);  // rect #22
  rects_[1] = Rectangle(22,12);  // rect #33
  rects_[2] = Rectangle(34,30);  // rect #24
  rects_[3] = Rectangle(64,24);  // rect #35
  rects_[4] = Rectangle(88,36);  // rect #23
  rects_[5] = Rectangle(124,36);  // rect #25
  rects_[6] = Rectangle(160,16);  // rect #36
  rects_[7] = Rectangle(176,18);  // rect #37
  rects_[8] = Rectangle(194,20);  // rect #44
  rects_[9] = Rectangle(214,12);  // rect #38
  rects_[10] = Rectangle(226,16);  // rect #45
  rects_[11] = Rectangle(242,36);  // rect #39
  rects_[12] = Rectangle(278,14);  // rect #47
  rects_[13] = Rectangle(292,9);  // rect #40
  rects_[14] = Rectangle(301,32);  // rect #43
  rects_[15] = Rectangle(333,6);  // rect #49
  // rects_[16] = Rectangle(339,16);  // rect #48
  // rects_[17] = Rectangle(355,22);  // rect #41
  // rects_[18] = Rectangle(377,22);  // rect #46
  // rects_[19] = Rectangle(399,12);  // rect #42
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