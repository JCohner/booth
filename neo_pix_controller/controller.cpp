#include <Arduino.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "controller.h"


void Controller::tick(){
  static uint8_t rval, bval, gval;
  static uint32_t tick = 0;
  tick++;
  for (int i =0; i < 4; i++){
    Rectangle rect = rects_[i];
    rect.update(tick);
  }
  FastLED.show();
}

void Controller::setup(){
  FastLED.addLeds<NEOPIXEL, CONTROL_PIN>(leds_, LED_COUNT).setCorrection( TypicalLEDStrip );;  // GRB ordering is assumed
  FastLED.setBrightness( 255 );

  // setup rectangles
  rects_[0] = Rectangle(0, 5);
  rects_[1] = Rectangle(5, 10);
  rects_[2] = Rectangle(15, 20);
  rects_[3] = Rectangle(35, 10);
  rects_[4] = Rectangle(45, 14);

  int gen_off = 0;
  Serial.print("leds is at: ");
  Serial.println((int)leds_);

  for (int i = 0; i < 4; i++){
    Serial.print("Assigning ");
    Serial.println((int)(leds_ + gen_off));
    rects_[i].leds_ = leds_ + gen_off;
    gen_off += rects_[i].count();
  }
}

void Controller::enqueue_message(char * buff, int size){
  if (size <= 0) return;
  char egg[100];
  int val;
  int rect;
  float valf;
  int ind = 3;
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
      Serial.println(buff[1]);
      rect = atoi(&buff[1]);
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