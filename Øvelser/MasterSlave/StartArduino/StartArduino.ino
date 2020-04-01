#include <Wire.h>
String test;
char test1;
void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  test = "";
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    test1 = (c);
    test = test + test1;
    Serial.print(c);           /* print the character */
  }
  Serial.println();             /* to newline */
  Serial.print(test);
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write("Hello NodeMCU");  /*send string on request */
}
