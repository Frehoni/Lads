#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"
#include "PinSetup.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

RTC_DS1307 rtc;
File myFileA;
File myFileB;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  pinMode(buttonPin, INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Time should be stored correctly.
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

  //Making a second file, DatB, and opening.

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

  Serial.println(F("BME280 test"));
  bool status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("-- Default Test --");
  Serial.println();
}
void loop() {
  if (millis() >= time_now + period) {
    buttonState = digitalRead(buttonPin);
    time_now += period;
    if (buttonState == HIGH) {
      while (digitalRead(buttonPin) == HIGH);
      n++;
      Serial.println(n);
    }
  }

  if (n % 2 == 0) { //Part A
    if (millis() >= time_nowA + periodA) {
      time_nowA += periodA;
      Temp_And_Pressure();
    }
    //Serial.println("Part A");
  }


  else if (n % 2 != 0) { //Part B
    Humid_Pres_Temp();
    //Serial.println("Part B");
  }
  //Serial.println(n);
}
