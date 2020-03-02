void Humid_Pres_Temp() {
  DateTime now = rtc.now();
  if (now.hour() < 6) {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print('Humidity = ');
    Serial.print(bme.readHumidity());
    Serial.println(' \(\%\)');
    Serial.println();
    myFileB = SD.open("DatB.txt", FILE_WRITE);
    myFileB.print(now.year(), DEC);
    myFileB.print('/');
    myFileB.print(now.month(), DEC);
    myFileB.print('/');
    myFileB.print(now.day(), DEC);
    myFileB.print(",");
    myFileB.print(now.hour(), DEC);
    myFileB.print(':');
    myFileB.print(now.minute(), DEC);
    myFileB.print(':');
    myFileB.print(now.second(), DEC);
    myFileB.print(',');
    myFileB.print(bme.readTemperature());
    myFileB.print(',');
    myFileB.print(bme.readPressure() / 100.0F);
    myFileB.print(',');
    myFileB.println(bme.readHumidity());
    myFileB.close();
    delay(6000);
  }
  else {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print('Humidity = ');
    Serial.print(bme.readHumidity());
    Serial.println(' \(\%\)');
    Serial.println();
    myFileB = SD.open("DatB.txt", FILE_WRITE);
    myFileB.print(now.year(), DEC);
    myFileB.print('/');
    myFileB.print(now.month(), DEC);
    myFileB.print('/');
    myFileB.print(now.day(), DEC);
    myFileB.print(",");
    myFileB.print(now.hour(), DEC);
    myFileB.print(':');
    myFileB.print(now.minute(), DEC);
    myFileB.print(':');
    myFileB.print(now.second(), DEC);
    myFileB.print(',');
    myFileB.print(bme.readTemperature());
    myFileB.print(',');
    myFileB.print(bme.readPressure() / 100.0F);
    myFileB.print(',');
    myFileB.println(bme.readHumidity());
    myFileB.close();
    delay(3000);
  }

}
