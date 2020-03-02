
#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"
#include "PinSetup.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

RTC_DS1307 rtc;
File myFile;

unsigned long delayTime;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  if (not SD.exists("DatA.txt")) {
    myFile = SD.open("DatA.txt", FILE_WRITE);
    myFile.print("DATE, TIME, TEMP *C, HUMIDITY");
    myFile.println();
    myFile.close();
  }
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to DatA.txt...");
    myFile.close();
  }
  //Testing if RTC is working
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  
  // creates a new data file if one does not already exist
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  Serial.println(F("BME280 test"));
  bool status;
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("-- Default Test --");
  delayTime = 1000;
  Serial.println();

}



void loop() {
  Temp_And_Humit();
  delay(delayTime);
}
