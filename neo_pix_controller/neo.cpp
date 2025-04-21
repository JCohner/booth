#include <Arduino.h>
#include <math.h>
#include <stdint.h>
#include "neo.h"


void Neo::tick(){
  FastLED.show();
}

void Neo::math(){
  static unsigned int tick = 0;
  static uint8_t rval, bval, gval;
  tick++;
  for (int i = 0; i < LED_COUNT; i++){
    rval = amplitude_[0] * (1 + sin(2 * M_PI * tick * frequency_[0]));
    bval = amplitude_[1] * (1 + sin(2 * M_PI * tick * frequency_[1]));
    gval = amplitude_[2] * (1 + sin(2 * M_PI * tick * frequency_[2]));
    leds_[i] = CRGB(rval, bval, gval);
  }
  if (tick % 10 == 0)
    Serial.println(gval);
}

void Neo::setup(){
  FastLED.addLeds<NEOPIXEL, CONTROL_PIN>(leds_, LED_COUNT).setCorrection( TypicalLEDStrip );;  // GRB ordering is assumed
  FastLED.setBrightness( 255 );
  pix_index_ = 0;
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

  if (color != Color::PIXEL && color != Color::NONE){
    sprintf(egg, "Setting %c to value: %d at pixel index %d", buff[0], val, pix_index_);
    color_map[pix_index_][(int)color] = val;
  } else if (color == Color::PIXEL){
    sprintf(egg, "Updating pix_index to: %d", pix_index_);
  }
  Serial.println(egg);

}