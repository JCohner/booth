#include <stdint.h>

#include <Arduino.h>

#include "dmx.h"

DMX::DMX(){
  _slots = DMX_MAX_SLOTS;
  //zero buffer including _dmxData[0] which is start code
  memset(_dmxData, 0, DMX_MAX_SLOTS+1);
}

void DMX::setup(){
  _next_read_slot = 0;              
  _dmx_read_state = DMX_STATE_IDLE;
}

void DMX::break_received(){
  // if we are already reading
  if (_dmx_read_state == DMX_READ_STATE_RECEIVING){
    if (_next_read_slot > 1) {  // we are already in packet (not double break)
      if (_receivedData[0] == 0){  // conforms to DMX 
        // Serial.print("early number of slots: ");
        // Serial.println(_next_read_slot);
        packet_complete();
      }
    } 
  }
  _dmx_read_state = DMX_READ_STATE_START;   //break causes spurious 0 byte on next interrupt, ignore...
  _next_read_slot = 0;
  _packet_length = DMX_MAX_FRAME;           // default to receive complete frame

}

void DMX::packet_complete(){
  if ( _receivedData[0] == 0 ) {        //zero start code is DMX
      if ( _next_read_slot > DMX_MIN_SLOTS ) {
        _slots = _next_read_slot - 1;       //_next_read_slot represents next slot so subtract one
        for(int j=0; j<_next_read_slot; j++) {  //copy dmx values from read buffer
          // Serial.print("Chan: ");
          // Serial.print(j);
          // Serial.print(": ");
          // Serial.println(_receivedData[j]);
          _dmxData[j] = _receivedData[j];
        }
  
        data_ready_ = true;
      }
  }
  reset_frame();
}

void DMX::byte_received(uint8_t byte){
  if (_dmx_read_state == DMX_READ_STATE_RECEIVING){
    _receivedData[_next_read_slot] = byte;

    if (_next_read_slot  == 2){
      if (_receivedData[0] != 0){
        _dmx_read_state = DMX_STATE_IDLE;
      } 
    }

    _next_read_slot++;
    // Serial.println(_next_read_slot);
    if ( _next_read_slot >= _packet_length ) {    //reached expected end of packet
      packet_complete();
      // Serial.print("Read this number of slots: ");
      // Serial.println(_next_read_slot);
    }
  } else if (_dmx_read_state == DMX_READ_STATE_START) {
    _dmx_read_state = DMX_READ_STATE_RECEIVING;
  }
}

uint8_t DMX::get_channel(uint16_t channel){
  if (channel < DMX_MAX_FRAME){
    return _dmxData[channel];
  }
}

uint16_t DMX::get_dmx_packet(uint8_t** data){
  *data = _dmxData;
  return _slots; // return number of populated slots
}