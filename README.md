# Booth Controller

Using ~1000 NeoPixels with FastLED library we are controlling a custom built DJ booths lighting.
The NeoPixels are organzied into rectangles on a DJ of which the light difuses around the rectnagle. 
This is using the SAMD21 broken out via the arduino nano 33 iot board. 

## Code Organization
* `booth_controller` contains the arduino sketch
  * `booth_controller.ino`
    * instantiates the DMX receiver very inspired by [this library](https://github.com/claudeheintz/LXSAMD21DMX/tree/master)
    * instantiates the custom LightingArrayController object
    * overrides the standard Serial1 handler SERCOM5 to specifically parse DMX inputs from the RS485 transciever 
    * sets up the dmx object and light controller
    * grabs dmx data and passes it to the light controller to map to rectangles
  * lighting_array_controller
    * **note** in both .h and .cpp file there is auto generated code parsed from the csv that keeps the rectangles aligned with reality. See rect_gen.py for more. 
    * **important** holds array of CRGB leds from FastLED 
    * handles business logic of holding array of rectangles and passing dmx channels to their relevant rectangle
    * critically calls FastLED.show()
  * rectangle
    * mechanisim to map global array of LEDs to given logical rectangle
    * has rectangle specific dmx_update mechanism which takes mapped dmx channels and translates to LED CRGB values
  * dmx
    * does dmx things, neat protocol. thanks to claudeheintz
* requirements.txt, rect_gen.py, rects.csv
  * all convinience things for autogenerating cpp code to map the rectangles
* Makefile
  * compile - compiles 'primary' and 'secondary' to cover both arduinos
  * deploy_[primary, secondary] - deploys relevant binary to MCU

## TODO attach pictures it looks sweet take my word for it for now.

### Notes:
Added: `void SERCOM5_Handler() __attribute__((weak));` to the relevant variants.cpp file such that I could overwrite the SERCOM5 handler being used for Serial1 to parse out the DMX messages

It seems my one nano was just not powerful enough to write to all 1000+ LEDs, I put another on the DMX bus and mapped it to the channels my first couldn't meet. 