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
  // rects_[0] = Rectangle(0,12);  // rect #4
  // rects_[1] = Rectangle(12,12);  // rect #13
  // rects_[2] = Rectangle(24,24);  // rect #5
  // rects_[3] = Rectangle(48,18);  // rect #1
  // rects_[4] = Rectangle(66,16);  // rect #9
  // rects_[5] = Rectangle(82,12);  // rect #3
  // rects_[6] = Rectangle(94,18);  // rect #10
  // rects_[7] = Rectangle(112,12);  // rect #12
  // rects_[8] = Rectangle(124,42);  // rect #6
  // rects_[9] = Rectangle(166,17);  // rect #8
  // rects_[10] = Rectangle(183,22);  // rect #7
  // rects_[11] = Rectangle(205,18);  // rect #11
  // rects_[12] = Rectangle(223,16);  // rect #2
  // rects_[13] = Rectangle(239,48);  // rect #19
  // rects_[14] = Rectangle(287,30);  // rect #28
  // rects_[15] = Rectangle(317,14);  // rect #16
  // rects_[16] = Rectangle(331,9);  // rect #26
  // rects_[17] = Rectangle(340,18);  // rect #27
  // rects_[18] = Rectangle(358,30);  // rect #14
  // rects_[19] = Rectangle(388,12);  // rect #15
  // rects_[20] = Rectangle(400,34);  // rect #17
  // rects_[21] = Rectangle(434,22);  // rect #29
  // rects_[22] = Rectangle(456,30);  // rect #18
  // rects_[23] = Rectangle(486,15);  // rect #31
  // rects_[24] = Rectangle(501,14);  // rect #20
  // rects_[25] = Rectangle(515,16);  // rect #32
  // rects_[26] = Rectangle(531,16);  // rect #30
  // rects_[27] = Rectangle(547,76);  // rect #21
  // rects_[28] = Rectangle(623,24);  // rect #34
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
  // rects_[13] = Rectangle(292,9);  // rect #40
  // rects_[14] = Rectangle(948,32);  // rect #43
  // rects_[15] = Rectangle(980,6);  // rect #49
  // rects_[16] = Rectangle(986,16);  // rect #48
  // rects_[17] = Rectangle(1002,22);  // rect #41
  // rects_[18] = Rectangle(1024,22);  // rect #46
  // rects_[19] = Rectangle(1046,12);  // rect #42
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