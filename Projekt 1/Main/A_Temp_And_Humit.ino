
void Temp_And_Humit() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
    Serial.print(1.8 * bme.readTemperature() + 32);
    Serial.println(" *F");*/

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  //Serial.print("Approx. Altitude = ");
  //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  //Serial.println(" m");

  //Serial.print("Humidity = ");
  //Serial.print(bme.readHumidity());
  //Serial.println(" %");

  Serial.println();
  DateTime now = rtc.now();
  myFileA = SD.open("DatA.txt", FILE_WRITE);
  myFileA.print(now.year(), DEC);
  myFileA.print('/');
  myFileA.print(now.month(), DEC);
  myFileA.print('/');
  myFileA.print(now.day(), DEC);
  myFileA.print(",");
  myFileA.print(now.hour(), DEC);
  myFileA.print(':');
  myFileA.print(now.minute(), DEC);
  myFileA.print(':');
  myFileA.print(now.second(), DEC);
  myFileA.print(',');
  myFileA.print(bme.readTemperature());
  myFileA.print(',');
  myFileA.println(bme.readPressure() / 100.0F);
  myFileA.close();
}
