void Humid_Pres_Temp() {
  DateTime now = rtc.now;
  if (now.hour() < 6) {
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
    myFileB.println(bme.readPressure() / 100.0F);
    myFileB.print(',');
    myFileB.print(bme.readHumidity());
    myFileB.close();

    delay(60000);
  }
  else {
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
    myFileB.println(bme.readPressure() / 100.0F);
    myFileB.print(',');
    myFileB.print(bme.readHumidity());
    myFileB.close();

    delay(30000);
  }

}
