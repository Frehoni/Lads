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
File myFileA;
File myFileB;

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
    myFileA = SD.open("DatA.txt", FILE_WRITE);
    myFileA.print("DATE, TIME, TEMP \(C\), PRESSURE \(hPa\)");
    myFileA.println();
    myFileA.close();
  }
  // if the file opened okay, write to it:
  if (myFileA) {
    Serial.println("Writing to DatA.txt...");
    myFileA.close();
  }
  if (not SD.exists("DatB.txt")) {
    myFileB = SD.open("DatB.txt", FILE_WRITE);
    myFileB.print("DATE, TIME, TEMP \(C\), PRESSURE \(hPa\), HUMIDITY \(%\) ");
    myFileB.println();
    myFileB.close();
  }
  // if the file opened okay, write to it:
  if (myFileB) {
    Serial.println("Writing to DatB.txt...");
    myFileB.close();
  }
  //Testing if RTC is working
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // creates a new data file if one does not already exist
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  Serial.println(F("BME280 test"));
  bool status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("-- Default Test --");
  delayTime = 2000;
  Serial.println();

}



void loop() {
  sensorValue = analogRead(analogInPin);
  if (sensorValue < (1024 / 2)) {
    Temp_And_Humit();
    delay(delayTime);
  }
  else {
    Humid_Pres_Temp();
  }
}
