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
  rects_[0] = Rectangle(0,18);
  rects_[1] = Rectangle(18,16);
  rects_[2] = Rectangle(34,12);
  rects_[3] = Rectangle(46,12);
  rects_[4] = Rectangle(58,24);
  rects_[5] = Rectangle(82,42);
  rects_[6] = Rectangle(124,22);
  rects_[7] = Rectangle(146,18);
  rects_[8] = Rectangle(164,16);
  rects_[9] = Rectangle(180,18);
  rects_[10] = Rectangle(198,18);
  rects_[11] = Rectangle(216,12);
  rects_[12] = Rectangle(228,12);
  rects_[13] = Rectangle(240,30);
  rects_[14] = Rectangle(270,12);
  rects_[15] = Rectangle(282,14);
  rects_[16] = Rectangle(296,34);
  rects_[17] = Rectangle(330,30);
  rects_[18] = Rectangle(360,48);
  rects_[19] = Rectangle(408,14);
  rects_[20] = Rectangle(422,76);
  rects_[21] = Rectangle(498,22);
  rects_[22] = Rectangle(520,36);
  rects_[23] = Rectangle(556,30);
  rects_[24] = Rectangle(586,36);
  rects_[25] = Rectangle(622,9);
  rects_[26] = Rectangle(631,18);
  rects_[27] = Rectangle(649,30);
  rects_[28] = Rectangle(679,22);
  rects_[29] = Rectangle(701,16);
  rects_[30] = Rectangle(717,15);
  rects_[31] = Rectangle(732,16);
  rects_[32] = Rectangle(748,12);
  rects_[33] = Rectangle(760,24);
  rects_[34] = Rectangle(784,24);
  rects_[35] = Rectangle(808,16);
  rects_[36] = Rectangle(824,18);
  rects_[37] = Rectangle(842,12);
  rects_[38] = Rectangle(854,36);
  rects_[39] = Rectangle(890,9);
  rects_[40] = Rectangle(899,22);
  rects_[41] = Rectangle(921,12);
  rects_[42] = Rectangle(933,32);
  rects_[43] = Rectangle(965,20);
  rects_[44] = Rectangle(985,16);
  rects_[45] = Rectangle(1001,22);
  rects_[46] = Rectangle(1023,14);
  rects_[47] = Rectangle(1037,16);
  rects_[48] = Rectangle(1053,6);
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