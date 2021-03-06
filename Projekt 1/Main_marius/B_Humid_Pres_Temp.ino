void Humid_Pres_Temp() {
  DateTime now = rtc.now();
  if (now.hour() < 6) {
    // between 00:00 - 06:00
    
    Serial.print("Night - Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println("%");
    Serial.println();
    // Test-prints to the serial monitor
    
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
    // Print to DatB
    
    delay(600000);
    // 10-minute delay
  }
  else {
    // between 06:00 - 24:00
    
    Serial.print("Day - Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println("%");
    Serial.println();
    // Test-print to the serial monitor
    
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
    //Print to DatB
    
    delay(300000);
    // 5-minute delay
  }

}
