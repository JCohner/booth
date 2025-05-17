#ifndef __DMX_H__
#define __DMX_H__

#include <stdint.h>


//***** baud rate defines
#define DMX_DATA_BAUD 250000
#define DMX_BREAK_BAUD  90000

#define DMX_MAX_SLOTS 512
#define DMX_MIN_SLOTS 24
#define DMX_MAX_FRAME 513

//***** states indicate current position in DMX stream
#define DMX_STATE_BREAK 0
#define DMX_STATE_START 1
#define DMX_STATE_DATA 2
#define DMX_STATE_IDLE 3

//***** states indicate current position in DMX stream
#define DMX_READ_STATE_IDLE 0
#define DMX_READ_STATE_RECEIVING 1
#define DMX_READ_STATE_START   2

class DMX {
public:
  DMX();
  void setup();
  void byte_received(uint8_t byte);
  void break_received(void);
  bool is_data_ready() {return data_ready_;}
  uint16_t get_dmx_packet(uint8_t** data);
  uint8_t get_channel(uint16_t channel);

private:
  volatile bool data_ready_; 
  uint8_t _dmxData[DMX_MAX_FRAME];
  uint8_t  _dmx_read_state;
  uint8_t _transaction;
  uint16_t  _next_read_slot;
  uint16_t  _packet_length;
  uint16_t  _slots;
  uint8_t  _receivedData[DMX_MAX_FRAME];
  void reset_frame() { _dmx_read_state = DMX_READ_STATE_IDLE; }
  void packet_complete();
};


#endif /* __DMX_H__ */