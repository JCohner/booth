# Booth Controller

Using NeoPixels with FastLED library we are controlling a custom built DJ booths lighting

### Notes:
Added: `void SERCOM5_Handler() __attribute__((weak));` to the relevant variants.cpp file such that I could overwrite the SERCOM5 handler being used for Serial1 to parse out the DMX messages