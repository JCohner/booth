#include <Arduino.h>
#include "neo.h"

void Neo::setup(){
  // Declare our NeoPixel strip object:
  strip = Adafruit_NeoPixel(LED_COUNT, control_pin_, NEO_GRB + NEO_KHZ800);
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void Neo::enqueue_message(char * buff, int size){
  if (size <= 0) return;
  switch(buff[0]){
    case 'r':
      char egg[100];
      sprintf(egg, "got red of val: %d", atoi(buff+1));
      Serial.println(egg);
      break;
  }

}