
//////////// Initiering ///////////

//inkluderer nødvendige bibloteker
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
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

// Definerer id og password til netværksforbindelse som NodeMCU anvender
const char* ssid = "Powerpuff Pigerne"; //Indsæt navnet på jeres netværk her
const char* password = "BlomstogBobbel"; //Indsæt password her

// Definerer information til mqtt serveren
const char *mqtt_server = "hairdresser.cloudmqtt.com"; //navn på mqtt-server. Find navnet på cloudmqtt-hjemmesiden
const int mqtt_port = 15743; // Definerer porten
const char *mqtt_user = "Freddy"; // Definerer mqtt-brugeren
const char *mqtt_pass = "Freddy"; // Definerer koden til mqtt-brugeren
//
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String payload; // Definerer variablen 'payload' i det globale scope (payload er navnet på besked-variablen)
/////// INITIERING SLUT //////////

//
//
//
//
//
//

/////// FUNKTIONSOPSÆTNING ////////


// Opretter en placeholder for callback-funktionen til brug senere. Den rigtige funktion ses længere nede.
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length);

// Opretter en klient der kan forbinde til en specifik internet IP adresse.
WiFiClient espClient; // Initialiserer wifi bibloteket ESP8266Wifi, som er inkluderet under "nødvendige bibloteker"

// Opretter forbindelse til mqtt klienten:
PubSubClient client(mqtt_server, mqtt_port, callback, espClient); // Initialiserer bibloteket for at kunne modtage og sende beskeder til mqtt. Den henter fra definerede mqtt server og port. Den henter fra topic og beskeden payload

/////// FUNKTIONSOPSÆTNING SLUT /////////

//
//
//
//
//
//

///////// CALLBACKFUNKTION ////////

// Definerer callback funktionen der modtager beskeder fra mqtt
// OBS: den her funktion kører hver gang MCU'en modtager en besked via mqtt
void callback(char* byteArraytopic, byte* byteArrayPayload, unsigned int length) {
  // Konverterer indkomne besked (topic) til en string:
  String topic;
  topic = String(byteArraytopic);
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");
  // Konverterer den indkomne besked (payload) fra en array til en string:
  // Topic == Temperaturmaaler, Topic == Kraftsensor
  payload = ""; // Nulstil payload variablen så forloopet ikke appender til en allerede eksisterende payload
  if (topic == "20.3") {
    payload = ""; // Nulstil payload variablen så forloopet ikke appender til en allerede eksisterende payload
    for (int i = 0; i < length; i++) {
      payload += (char)byteArrayPayload[i];
      // For-loop: tag hvert tegn i hele længden af den inkomne besked, og konverter denne til en char. Append tegnene 1 efter 1:
      // Eksempel:
      // Besked = Study Abroad
      // Length = 12
      // Loop 1 = "S"
      // Loop 2 = "St" osv.
      // Loop (length) = "Study Abroad"

      if (payload == "On") {
        // Definerer funktion som bruges til at styre temperaturmåling
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("TurnOnLED");  /* Turn on LED */
        Wire.endTransmission();    /* stop transmitting */

        Wire.requestFrom(8, 9); /* request & read data of size 13 from slave */
        while (Wire.available()) {
          char c = Wire.read();
          Serial.print(c);
        }
        Serial.println();
        delay(1000);
        client.publish("Status", "Arduino LED is turned on.");
      }
      else if (payload == "Off") {
        // Definerer funktion som bruges til at styre temperaturmåling
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("TurnOffLED");  /* Makes the LED turn off*/
        Wire.endTransmission();    /* stop transmitting */

        Wire.requestFrom(8, 10); /* request & read data of size 13 from slave */
        while (Wire.available()) {
          char c = Wire.read();
          Serial.print(c);
        }
        Serial.println();
        delay(1000);

        client.publish("Status", "Arduino LED is turned off.");
      }
    }
  }
  Serial.print(payload);
  //client.publish("mqtt", String(payload).c_str()); // Publish besked fra MCU til et valgt topic. Husk at subscribe til topic'et i NodeRed.
}


///////// CALLBACK SLUT /////////

//
//
//
//
//
//

/////// OPSÆTNING AF WIFI-FORBINDELSE  ///////////


// Opretter forbindelse til WiFi
void setup_wifi() {
  // Forbinder til et WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


// Opretter forbindelse til mqtt server. Dette gentages ved manglende forbindelse til WiFi, server osv.
void reconnect() {
  // Fortsætter til forbindelsen er oprettet
  while (!client.connected()) {
    Serial.print("Forsøger at oprette MQTT forbindelse...");

    if (client.connect("UNIQUE_CLIENT_NAME", mqtt_user, mqtt_pass)) { // Forbinder til klient med mqtt bruger og password
      Serial.println("connected");
      // Derudover subsribes til topic "Test" hvor NodeMCU modtager payload beskeder fra
      client.subscribe("Test");


      // Hvis forbindelsen fejler køres loopet igen efter 5 sekunder indtil forbindelse er oprettet
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Venter 5 sekunder før den prøver igen
      delay(5000);
    }
  }
}

///////// OPSÆTNING AF WIFI SLUT /////////

//
//
//
//
//
//

///////// SETUP ///////////
void setup() {
  Serial.begin(115200); // Åbner serial porten og sætter data raten til 115200 baud
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
  delay(1000);
  setup_wifi(); // Kører WiFi loopet og forbinder herved.
  client.setServer(mqtt_server, mqtt_port); // Forbinder til mqtt serveren (defineret længere oppe)
  client.setCallback(callback); // Ingangsætter den definerede callback funktion hver gang der er en ny besked på den subscribede "cmd"- topic
}
//////// SETUP SLUT ////////

//
//
//
//
//
//

/////// LOOP /////////

void loop() {
  // Hvis der opstår problemer med forbindelsen til mqtt broker oprettes forbindelse igen ved at køre client loop
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

//////// Loop slut ////////
