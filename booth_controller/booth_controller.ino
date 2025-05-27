#include "lighting_array_controller.h"
#include "dmx.h"

LightingArrayController light_cont(6);
DMX dmx;

// DMX Input
void SERCOM5_Handler()
{
  if ( SERCOM5->USART.INTFLAG.bit.ERROR ) {
    SERCOM5->USART.INTFLAG.bit.ERROR = 1;   //acknowledge error, clear interrupt
    
    if (SERCOM5->USART.STATUS.bit.FERR){ // silly but universal way they seem to detect new DMX packet
      dmx.break_received();
      return;
    }
  
  }
  if ( SERCOM5->USART.INTFLAG.bit.RXC ) {
    uint8_t incoming_byte = SERCOM5->USART.DATA.reg;       // read buffer to clear interrupt flag
    dmx.byte_received(incoming_byte);
  } // RXC
}

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  while(!Serial){;}
  
  // DMX Receiving 
  Serial1.begin(250000);
  dmx.setup();

  light_cont.setup();
  delay(100);
}

void loop() {
  // map dmx to light controller in 3 channel mode:
  static int egg = 0;
  uint8_t* data;
  uint16_t num_slots = dmx.get_dmx_packet(&data);
  light_cont.dmx_update(data, num_slots);
  //Serial.println(egg++);
  delay(30);
}
