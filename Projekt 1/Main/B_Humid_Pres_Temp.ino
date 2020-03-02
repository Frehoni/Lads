void Humid_Pres_Temp() {
  DateTime now = rtc.now;
  if (now.hour() < 6) {
    myFile = SD.open("DatB.txt", FILE_WRITE);
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(",");
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(',');
    myFile.print(bme.readTemperature());
    myFile.print(',');
    myFile.println(bme.readPressure() / 100.0F);
    myFile.print(',');
    myFile.print(bme.readHumidity());
    myFile.close();

    delay(60000);
  }
  else {
    myFile = SD.open("DatB.txt", FILE_WRITE);
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(",");
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(',');
    myFile.print(bme.readTemperature());
    myFile.print(',');
    myFile.println(bme.readPressure() / 100.0F);
    myFile.print(',');
    myFile.print(bme.readHumidity());
    myFile.close();

    delay(30000);
  }

}
