#include <stdint.h>
#include <fast_samd21_tc5.h>
#include "lighting_array_controller.h"

LightingArrayController light_cont(6);

void setup() {
  Serial.begin(9600);
  while(!Serial){;}

  // Slave Receiving 
  Serial1.begin(250000);

  light_cont.setup();

  fast_samd21_tc5_configure(30000); // 30 ms
}

uint8_t other_buff[100] = {0};
uint8_t done_buff[100] = {0};
uint8_t buff[100] = {0};
uint8_t * ptr = done_buff;
char term_char = '\r';
int ii = 0;

void TC5_Handler(void) {
  light_cont.dmx_update(ptr, 1);
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void loop() {
  // read in master commands
  if (Serial1.available() > 0) {
    // read the incoming byte:
    auto incoming_byte = Serial1.read();
    buff[ii++] = incoming_byte;
    if (incoming_byte == term_char){
      if (ptr == other_buff){
        for (int i = 0; i < ii; i++){
          done_buff[i] = buff[i];
        }
        fast_samd21_tc5_disable();
        ptr = done_buff;
        fast_samd21_tc5_start();
      } else if (ptr == done_buff){
        for (int i = 0; i < ii; i++){
          other_buff[i] = buff[i];
        }
        fast_samd21_tc5_disable();
        ptr = other_buff;
        fast_samd21_tc5_start();
      }
      ii =0;
    }
  }
}