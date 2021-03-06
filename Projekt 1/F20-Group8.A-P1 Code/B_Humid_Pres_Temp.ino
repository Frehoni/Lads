void Humid_Pres_Temp() {
  DateTime now = rtc.now(); //Gets current date and time
  if (now.hour() < 6) {
    if (millis() >= time_nowB1 + periodB1) {
      time_nowB1 += periodB1;
      //constantly adding a delay of PeriodB1= 10 min.
      // between 00:00 - 06:00
      
      Serial.println("Det er nat!");
      Serial.print("Temperature = ");
      Serial.print(bme.readTemperature());
      Serial.println(" *C");
      Serial.print("Pressure = ");
      Serial.print(bme.readPressure() / 100.0F);
      Serial.println(" hPa");
      Serial.print("Humidity = ");
      Serial.print(bme.readHumidity());
      Serial.println(" \(\%\)");
      Serial.println();
      // Test-prints to the serial monitor

      myFileB = SD.open("DatB.txt", FILE_WRITE);
      myFileB.print(now.year(), DEC);
      myFileB.print('/');
      myFileB.print(now.month(), DEC);
      myFileB.print('/');
      myFileB.print(now.day(), DEC);
      myFileB.print(',');
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
      // Print to DatB

    }
  }
  else {
    // between 06:00 - 24:00
    if (millis() >= time_nowB2 + periodB2) {
      time_nowB2 += periodB2;
      //constantly adding a delay of PeriodB2= 5 min.
      
      Serial.println("Det er dag!");
      Serial.print("Temperature = ");
      Serial.print(bme.readTemperature());
      Serial.println(" *C");
      Serial.print("Pressure = ");
      Serial.print(bme.readPressure() / 100.0F);
      Serial.println(" hPa");
      Serial.print("Humidity = ");
      Serial.print(bme.readHumidity());
      Serial.println(" \(\%\)");
      Serial.println();
      // Test-print to the serial monitor

      myFileB = SD.open("DatB.txt", FILE_WRITE);
      myFileB.print(now.year(), DEC);
      myFileB.print('/');
      myFileB.print(now.month(), DEC);
      myFileB.print('/');
      myFileB.print(now.day(), DEC);
      myFileB.print(',');
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
      //Print to DatB
    }

  }

}
