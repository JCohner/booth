#include "lighting_array_controller.h"
#include "dmx.h"

LightingArrayController light_cont(6);
DMX dmx;

// Handler for updating lighting array
void TC5_Handler(void) {
  light_cont.tick();
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}

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

char buff[100] = {0};
char termination_char = '\r';
int ii = 0;

void loop() {

}
