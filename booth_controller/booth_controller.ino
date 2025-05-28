#include "wiring_private.h"
#include "lighting_array_controller.h"

#include "dmx.h"
DMX dmx;

LightingArrayController light_cont(7);


// make 3rd serial // from this hero: https://stackoverflow.com/a/71871680/3140063
Uart mySerial (&sercom0, 5, 6, SERCOM_RX_PAD_1, UART_TX_PAD_0);

// Attach the interrupt handler to the SERCOM
void SERCOM0_Handler()
{
    mySerial.IrqHandler();
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
  Serial.begin(9600);
  while(!Serial){;}
  
  // DMX Receiving 
  Serial1.begin(250000);
  dmx.setup();

  // Slave Communication
  mySerial.begin(9600);
  pinPeripheral(5, PIO_SERCOM_ALT); // RX
  pinPeripheral(6, PIO_SERCOM_ALT); // TX

  //light_cont.setup();

  delay(100);
}

void loop() {
  // map dmx to light controller in 3 channel mode:
  static int egg = 0;
  uint8_t* data;
  uint16_t num_slots = dmx.get_dmx_packet(&data);
  
  // communicate to controllers
 for (int i = 0; i < 10; i++){
   mySerial.write(data[i]);
  }
  mySerial.write("\r");
  Serial.println(egg++);
  //light_cont.dmx_update(data, num_slots);
  //delay(30);
}
