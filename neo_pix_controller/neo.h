#ifndef __NEO_H__
#define __NEO_H__

#include <Adafruit_NeoPixel.h>

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

enum Color {
  RED = 0, 
  GREEN = 1, 
  BLUE = 2,
  // Below are state machine hackery
  PIXEL = 3, 
  NONE = 4
};


class Neo {
public:
  Neo(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  void enqueue_message(char * buff, int size);
  void tick();
private:
  int control_pin_;
  Adafruit_NeoPixel strip;
  int color_map[LED_COUNT][3];
  int pix_index_;
};

#endif /* __NEO_H__ */