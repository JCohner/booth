#include "neo.h"

void Neo::setup(){
  // Declare our NeoPixel strip object:
  strip = Adafruit_NeoPixel(LED_COUNT, control_pin_, NEO_GRB + NEO_KHZ800);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void Neo::enqueue_message(char * buff, int size){

}