#include <Wire.h>

String msg;

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(115200);           /* start serial for debug */
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  msg="";
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    msg = msg + c;
  }
  Serial.println("Message recieved is:");
  Serial.println(msg);
  if (msg == "TurnOnLED") {
    digitalWrite(LED_BUILTIN, HIGH);

  }
  if (msg == "TurnOffLED") {
    digitalWrite(LED_BUILTIN, LOW);

  }


  Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write("Message recieved! Thank you!");  /*send string on request */
}
