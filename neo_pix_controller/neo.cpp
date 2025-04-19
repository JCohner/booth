#include <Arduino.h>
#include "neo.h"

void Neo::tick(){
  for (int i = 0; i < LED_COUNT; i++){
    strip.setPixelColor(i, color_map[i][0], color_map[i][1], color_map[i][2]);
  }
  strip.show();
}

void Neo::setup(){
  // Declare our NeoPixel strip object:
  strip = Adafruit_NeoPixel(LED_COUNT, control_pin_, NEO_GRB + NEO_KHZ800);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pix_index_ = 0;
}

void Neo::enqueue_message(char * buff, int size){
  if (size <= 0) return;
  char egg[100];
  int val = atoi(buff+1);
  Color color = NONE;
  switch(buff[0]){
    case 'q':
      memset(color_map, 0, sizeof(color_map));
    case 'r':
      color = RED;
      break;
    case 'g':
      color = GREEN;
      break;
    case 'b':
      color = BLUE;
      break;
    case 'p':
      color = PIXEL; 
      if (val >= LED_COUNT){
        Serial.println("INDEXED OUT OF BOUND PIXEL");
        return;
      }
      pix_index_ = val;
      break;
    default:
      return;
  }

  if (color != PIXEL){
    sprintf(egg, "Setting %c to value: %d at pixel index %d", buff[0], val, pix_index_);
    color_map[pix_index_][color] = val;
  } else if (color == PIXEL){
    sprintf(egg, "Updating pix_index to: %d", pix_index_);
  }
  Serial.println(egg);

}