#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

const char* ssid = "Powerpuff Pigerne"; // HINT: create a hotspot with your phone..
const char* password = "BlomstogBobbel";

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int test = 0;
String key = "http://api.openweathermap.org/data/2.5/weather?lat=48.21&lon=16.37&appid=95fb8a0ca887dc68309f34e8d20c8ceb&units=metric&cnt=3";
void setup() {
  Serial.begin(115200);
  u8g2.begin();
  //connect to the wifi access point
  WiFi.begin(ssid, password);

  //wait until connected - might take a while

  Serial.print("Connecting  ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected ! \n");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http; //Declare an object of class HTTPClient
    // Vienna: http://api.openweathermap.org/data/2.5/weather?lat=48.21&lon=16.37&appid=95fb8a0ca887dc68309f34e8d20c8ceb&units=metric&cnt=3
    // Copenhagen: http://api.openweathermap.org/data/2.5/forecast?q=Copenhagen,dk&appid=95fb8a0ca887dc68309f34e8d20c8ceb&units=metric&cnt=3
    // REMEMBER to replace YOURKEY from the url with your own key
    key = "http://api.openweathermap.org/data/2.5/forecast?q=Copenhagen,dk&appid=8fb15d49e0d25afbf7373135bb753782&units=metric&cnt=3";
    http.begin(key); //Specify request destination
    int httpCode = http.GET(); //Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString(); //Get the request response payload - the json object as a plain text

      //define a json object buffer
      DynamicJsonDocument jsonBuffer(1024);

      //try convert the plain text to an arduino - json object
      DeserializationError success = deserializeJson(jsonBuffer, payload);

      // if conversion not successful:
      // NOTE: there are two cases this can fail: if the json object is too big for the arduino
      // OR the communication protocol to the api is secure: e.g. 'https' instead of 'http'
      // There are solutions to both, but not relevant for this exercise..

      if (!success) {
        Serial.println("deserialization failed");
        delay(1000);
        return;
      }
    }

    //if it is successful, let's grab a data fragment and show it on the serial terminal:

    // the first forecast in the json object is at jsonBuffer['list'][0]
    String timestamp = jsonBuffer["list"][0]["dt_txt"];
    Serial.print("The time for this forecast: ");
    Serial.println(timestamp);

    // The 'weather' in the first position in the list, is actually a list, with only one element...
    String desc = jsonBuffer["list"][0]["weather"][0]["description"];
    Serial.print("The weather will be: ");
    Serial.println(desc);

    // The ArduinoJson library also has a utility function to 'pretty print' json objects, try:
    serializeJsonPretty(jsonBuffer["list"][0], Serial);
    //or
    Serial.println("\nThe full forecast Json looks like this: ");
    serializeJsonPretty(jsonBuffer, Serial);
    float temp = jsonBuffer["list"][0]["main"]["temp"];
    Serial.print("TEMPERATUR HER MAKKER:");
    Serial.println(temp);
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.setCursor(0, 10);
    u8g2.print(timestamp);
    u8g2.setCursor(0, 30);
    u8g2.print(desc);
    u8g2.setCursor(0, 40);
    u8g2.print(String(temp));
    u8g2.setCursor(30, 40);
    u8g2.print("C");
    u8g2.sendBuffer();          // transfer internal memory to the display
  }

  http.end(); //Close connection
}
/*
  Forecast time date
  Forecast description: e.g. 'few clouds'
  Forecast temperature in C
*/

//Send a request every 5 min
delay(5 * 60 * 1000);
}
