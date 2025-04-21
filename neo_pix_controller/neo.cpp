#include <Arduino.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "neo.h"


void Neo::tick(){
  static uint8_t rval, bval, gval;
  static uint32_t tick = 0;
  tick++;
  for (int i =0; i < 5; i++){
    auto rect = rects_[i];
    rect.update(tick);
    int z = 0;
    for (int j = rect.start; j < rect.end; j++){
      leds_[j] = rect.leds_[z++];
    }
  }
  FastLED.show();
}

void Neo::setup(){
  FastLED.addLeds<NEOPIXEL, CONTROL_PIN>(leds_, LED_COUNT).setCorrection( TypicalLEDStrip );;  // GRB ordering is assumed
  FastLED.setBrightness( 255 );
  pix_index_ = 0;

  // setup rectangles
  rects_[0] = Rectangle(0, 5);
  rects_[1] = Rectangle(5, 10);
  rects_[2] = Rectangle(15, 20);
  rects_[3] = Rectangle(35, 10);
  rects_[4] = Rectangle(45, 15);

  for (int i = 0; i < 4; i++){
    rects_[i].leds_ = malloc(rects_[i].count() * sizeof(CRGB));
  }
}

void Neo::enqueue_message(char * buff, int size){
  if (size <= 0) return;
  char egg[100];
  int val;
  float valf;
  int ind = 3;
  Color color = Color::NONE;
  Serial.print("swithcing on: ");
  Serial.println(buff[0]);
  switch(buff[0]){
    case 'q':
      memset(color_map, 0, sizeof(color_map));
      break;
    case 'x':
      switch (buff[1]){
        case 's':
          algo_ = Algo::SINE;
          break;
      }
      break;
    case 'a':
    case 'f':
      valf = atof(buff+2);
      switch(buff[1]){
        case 'r':
          ind = 0;
          break;
        case 'g':
          ind = 1;
          break;
        case 'b':
          ind = 2;  
          break; 
      }
      if (ind != 3){
        char fs[10];
        dtostrf(valf, 4, 2, fs);
        sprintf(egg, "Writing value %c, %c to %s",buff[0], buff[1], fs);
        Serial.println(egg);
        if (buff[0] == 'f'){
          frequency_[ind] = valf;
        } else if (buff[0] == 'a'){
          amplitude_[ind] = valf;
        }
      }
      break;
  }
}