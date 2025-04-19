#ifndef __NEO_H__
#define __NEO_H__

#include <Adafruit_NeoPixel.h>

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 16

enum class Color {
  RED = 0, 
  GREEN = 1, 
  BLUE = 2,
  // Below are state machine hackery
  PIXEL = 3, 
  NONE = 4
};

enum class Algo {
  NONE = 0,
  SINE = 1
};

class Neo {
public:
  Neo(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  void enqueue_message(char * buff, int size);
  void tick();
  void math();
private:
  int control_pin_;
  Adafruit_NeoPixel strip;
  int color_map[LED_COUNT][3];
  int pix_index_;
  // Algorithm stuff
  Algo algo_;
  float frequency_[3];
  float amplitude_[3];
  float offset_[LED_COUNT];
};

#endif /* __NEO_H__ */