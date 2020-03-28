#include <Encoder.h>

Encoder myEnc(D1, D2);


long oldPosition  = -999;
boolean isButtonPressed = false;
long lastUpdateMillis = 0;

void handleKey() {
  isButtonPressed = true;  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
   pinMode(D3, INPUT_PULLUP);
   attachInterrupt(D3, handleKey, RISING);
}


void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  // software debounce
  if (isButtonPressed &amp;&amp; millis() - lastUpdateMillis &gt; 50) {
    isButtonPressed = false;
    lastUpdateMillis = millis();
    // Reset the counter
    myEnc.write(0);
  }
}
