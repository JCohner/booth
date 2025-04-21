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
    Rectangle rect = rects_[i];
    rect.update(tick);
    int z = 0;
    for (int j = rect.global_start(); j < rect.global_stop(); j++){
      leds_[j] = rect.leds_[z++];
      Serial.print("here: ");
      Serial.println((int) rect.leds_);
    }
  }
  FastLED.show();
}

void Neo::setup(){
  FastLED.addLeds<NEOPIXEL, CONTROL_PIN>(leds_, LED_COUNT).setCorrection( TypicalLEDStrip );;  // GRB ordering is assumed
  FastLED.setBrightness( 255 );

  // setup rectangles
  rects_[0] = Rectangle(0, 5);
  rects_[1] = Rectangle(5, 10);
  rects_[2] = Rectangle(15, 20);
  rects_[3] = Rectangle(35, 10);
  rects_[4] = Rectangle(45, 15);

  char buff[100];
  for (int i = 0; i < 4; i++){
    rects_[i].leds_ = calloc(rects_[i].count(), sizeof(CRGB));
    sprintf(buff, "Rect %d allocated %d entries of size %d at location %d",i, rects_[i].count(), sizeof(CRGB), rects_[i].leds_ );
    Serial.println(buff);
  }
}

void Neo::enqueue_message(char * buff, int size){
  if (size <= 0) return;
  char egg[100];
  int val;
  int rect;
  float valf;
  int ind = 3;
  Color color = Color::NONE;
  Serial.print("swithcing on: ");
  Serial.println(buff[0]);
  switch(buff[0]){
    case 'q':
      TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
      //memset(color_map, 0, sizeof(color_map));
      break;
    case 'a':
    case 'f':
      valf = atof(buff+3);
      rect = atoi(buff[1]);
      switch(buff[2]){
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
        sprintf(egg, "For rect %d Writing value %c, %c to %s",rect, buff[0], buff[2], fs);
        Serial.println(egg);
        if (buff[0] == 'f'){
          rects_[rect].set_frequency(ind, valf);
        } else if (buff[0] == 'a'){
          rects_[rect].set_amplitude(ind, valf);
        }
      }
      break;
  }
}