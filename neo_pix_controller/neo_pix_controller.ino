#include "neo.h"
Neo neo(6);

ISR(TIMER2_COMPA_vect)
{
  OCR2A += 156;// Timer Preloading
  // Handle The 10ms Timer Interrupt
  // This triggers the tick function of the robot to check state
  neo.tick();
}

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  neo.setup();

  // Thanks to this lovely little calculator: https://deepbluembedded.com/arduino-timer-calculator-code-generator/
  TCCR2A = 0;           // Init Timer2A
  TCCR2B = 0;           // Init Timer2B
  TCCR2B |= B00000111;  // Prescaler = 1024
  OCR2A = 156;        // Timer Compare2A Register
  TIMSK2 |= B00000010;  // Enable Timer COMPA Interrupt
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
      neo.enqueue_message(buff, ii);
      memset(buff, 0, 100*sizeof(char));
      ii =0;
    }
  }
}
