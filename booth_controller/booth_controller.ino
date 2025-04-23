#include "controller.h"

Controller controller(6);

ISR(TIMER1_COMPA_vect)
{
  static float avg = 30000;
  static uint16_t num_samples = 1;
  unsigned long start = micros();

  OCR1A += 60000; // Advance The COMPA Register
  controller.tick();
  avg += (1.0 / ((float) num_samples++)) * ((micros() - start) - avg);
  if (num_samples % 100 == 0){
    Serial.print("Loop period: ");
    Serial.println(avg);
    avg = 30000;
    num_samples = 1;
  }
}


void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  while(!Serial){;}
  controller.setup();

  // Thanks to this lovely little calculator: https://deepbluembedded.com/arduino-timer-calculator-code-generator/
  // 30 ms timer
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000010;  // Prescaler = 8
  OCR1A = 60000;        // Timer Compare1A Register
  //TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
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
