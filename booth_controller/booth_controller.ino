#include "controller.h"

Controller controller(6);


void TC5_Handler(void) {
  controller.tick();
  TC5->COUNT16.INTFLAG.bit.MC0 = 1; // clears the interrupt
}


void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  while(!Serial){;}
  controller.setup();
  delay(100);
}

char buff[100] = {0};
char termination_char = '\r';
int ii = 0;

void loop() {
  delay(100);
  // if command available write
  if (Serial.available() > 0){
    auto incoming_byte = Serial.read();
    buff[ii++] = incoming_byte;
    Serial.print("Read byte: ");
    Serial.println(incoming_byte);

    if (incoming_byte == termination_char){
      Serial.print("Read string: ");
      Serial.println(buff);
      controller.enqueue_message(buff, ii);
      memset(buff, 0, 100*sizeof(char));
      ii =0;
    }
  }
}
