#include <Wire.h>

char message;

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
  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print("Message recieved is:");
    Serial.print(c);           /* print the character */
    if (c == 'TurnOnLED') {
      digitalWrite(LED_BUILTIN, HIGH);
      //Wire.write("LED is On");
      message = 'LED is On';
    }
    if (c == 'TurnOffLED') {
      digitalWrite(LED_BUILTIN, LOW);
      //Wire.write("LED is Off");
      message = 'LED is Off';
    }
    else {
      message = 'NoMessage';

    }


  }
  Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write(message);  /*send string on request */
}
