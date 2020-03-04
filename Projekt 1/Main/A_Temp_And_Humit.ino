
void Temp_And_Pressure() {

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  Serial.println();
  // Test-print to the serial monitor
  
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
