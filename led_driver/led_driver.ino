#include <stdint.h>

#include "lighting_array_controller.h"

LightingArrayController light_cont(6);

void setup() {
  Serial.begin(9600);
  while(!Serial){;}

  // Slave Receiving 
  Serial1.begin(9600);

  light_cont.setup();
}

uint8_t buff[50] = {0};
char term_char = '\r';
int ii = 0;

void loop() {
  delay(30);
  // read in master commands
  if (Serial1.available() > 0) {
    // read the incoming byte:
    auto incoming_byte = Serial1.read();
    buff[ii++] = incoming_byte;
    Serial.print("Read byte: ");
    Serial.println(incoming_byte);

    if (incoming_byte == term_char){
      Serial.print("Read buff");
      //Serial.println(buff);
      // light LEDs
      //light_cont.dmx_update(buff, 1);
      memset(buff, 0, 50*sizeof(char));
      ii =0;
    }
  }
}