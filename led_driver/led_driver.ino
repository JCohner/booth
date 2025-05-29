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

uint8_t done_buff[100] = {0};
uint8_t buff[100] = {0};
char term_char = '\r';
int ii = 0;

void TC5_Handler(void) {
  light_cont.dmx_update(done_buff, 1);
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

void loop() {
  // read in master commands
  if (Serial1.available() > 0) {
    // read the incoming byte:
    auto incoming_byte = Serial1.read();
    buff[ii++] = incoming_byte;
    //Serial.print("Read byte: ");
    //Serial.print(incoming_byte, HEX); 

    if (incoming_byte == term_char){
      fast_samd21_tc5_stop();
      for (int i = 0; i < ii; i++){
        done_buff[i] = buff[i];
      }
      fast_samd21_tc5_configure(30000); 
      ii =0;
    }
  }
}