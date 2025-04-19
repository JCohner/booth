#ifndef __NEO_H__
#define __NEO_H__

#include <Adafruit_NeoPixel.h>

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60

enum Color {
  RED = 0, 
  GREEN = 1, 
  BLUE = 2
};


class Neo {
public:
  Neo(int control_pin=6) : control_pin_(control_pin) {};
  void setup();
  void enqueue_message(char * buff, int size);
private:
  int control_pin_;
  Adafruit_NeoPixel strip;
  int color_map[3][LED_COUNT];
};

#endif /* __NEO_H__ */