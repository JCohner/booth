#include <Arduino.h>
#include <math.h>
#include <stdint.h>
#include "neo.h"


void Neo::tick(){
  for (int i = 0; i < LED_COUNT; i++){
    leds_[i] = CRGB((i+255) % 255 , 0, 0);
  }
  // blur1d(leds_, 20, 172);
  FastLED.show();
}

void Neo::math(){
  static uint32_t tick_c = 0;
  tick_c++;
  switch(algo_){
    case Algo::SINE:
      for (int i = 0; i < LED_COUNT; i++){
        // for (int j = 0; j < 3; j++){
          // leds_[i] = CRGB(200, 200, 0);
          
          // leds_[i] = (int) (amplitude_[j] * (1 + sin(2 * M_PI * (tick_c + offset_[i]) * frequency_[j]))/2.0);
          // if (tick_c % 100 == 0){
          //   Serial.print(color_map[i][j]);
          //   Serial.print("\t");
          // }
        // }
        // if (tick_c % 100 == 0) Serial.print("\r\n");
      }
      break;
  }
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