void LCDInformation()
{

  if (digitalRead(5) == HIGH)
  {
    if (flag_on_lcd == 0)
    {
      flag_on_lcd = 1;
      lcd.backlight();
      start_ = millis();
      LCD_Data();
      last_min = millis();
    }
    else
    {
      start_ = millis();
    }
  }

  if (flag_on_lcd == 1)
  {
    if (millis() - last_min > 3000  && flag_on_lcd == 1)
    {
      LCD_Data();
      last_min = millis();
    }

    if (millis() - start_ > 30000  && flag_on_lcd == 1)
    {
      flag_on_lcd = 0;
      lcd.clear();
      lcd.noBacklight();
    }
  }

}

void print2digits(int number)
{
  if (number >= 0 && number < 10)
  {
    lcd.print('0');
  }
  lcd.print(number);
}

void LCD_Data()
{
  sensors.requestTemperatures();
  lcd.clear();
  RTC.read(tm);
  lcd.setCursor(0, 0); print2digits(tm.Hour); lcd.print(':'); print2digits(tm.Minute);
  lcd.print(" "); lcd.print(tm.Day); lcd.print('/'); lcd.print(tm.Month); lcd.print('/'); lcd.print(tmYearToCalendar(tm.Year));

  lcd.setCursor(0, 1); lcd.print("Temp: "); lcd.print(int(bme.readTemperature())); lcd.setCursor(9, 1); lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(12, 1); lcd.print(char(3)); lcd.print(int(sensors.getTempCByIndex(0))); lcd.setCursor(17, 1); lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(0, 2); lcd.print(char(0)); lcd.print(int(bme.readHumidity())); lcd.setCursor(3, 2); lcd.print(" %");
  lcd.setCursor(2, 3); lcd.print(char(7)); lcd.print(int((bme.readPressure() / 100.0F) * 0.75)); lcd.setCursor(6, 3); lcd.print(" mm");
  lcd.setCursor(9, 2); lcd.print(char(2)); lcd.print(" "); lcd.print(int(analogRead(temt6000_pin) * 0.9765625));  lcd.setCursor(14, 2); lcd.print(" lux");
}

void BT()
{
  //Temp ;press;temp::outside; Humidity;  Light;
  if (BlueT_on == 0)
  {
    if (mySerial.available() != 0)
    {
      BlueT_on = 1;
      start_B = millis();
    }
  }
  if (BlueT_on == 1)
  {
    if (millis() - LtimeBlt > 3000)
    {
      LtimeBlt = millis();
      String Send_BT = "";
      sensors.requestTemperatures();
      Send_BT = String(bme.readTemperature()) + ";" + String(int((bme.readPressure() / 100.0F) * 0.75)) + ";" + String(sensors.getTempCByIndex(0))  + ";" + String(bme.readHumidity()) + ";" + String(int(analogRead(temt6000_pin) * 0.9765625)) + ";";
      mySerial.print(Send_BT);
    }

    if (millis() - BlueT_on > 60000)
    {
      BlueT_on = 0;
    }
  }
}

void SD_Write()
{
  static LMin = 0;
  RTC.read(tm);
  if((tm.Minute == 0 || 15 || 30 || 45) && tm.Minute != LMin)
  {
    if(!SD.exists(GetFileName()))
    {
       MFile = SD.open(GetFileName(), FILE_WRITE);
       MFile.println("День" + ";" + "Время" + ";" + "Температура дома" + ";" + "Давление" + ";" + "Температура на улице" + ";" + "Влажность" + ";" + "Освещённость" + ";");
       MFile.close();
    }
    LMin = tm.Minute();
    MFile = SD.open(GetFileName(), FILE_WRITE);
    String record = GetTime + String(bme.readTemperature()) + ";" + String(int((bme.readPressure() / 100.0F) * 0.75)) + ";" + String(sensors.getTempCByIndex(0))  + ";" + String(bme.readHumidity()) + ";" + String(int(analogRead(temt6000_pin) * 0.9765625)) + ";";
    MFile.println(record);
    MFile.close();
  }
}
String GetFileName()
{
    RTC.read(tm);
    String NameR = String(tm.Month) + "." + String(tmYearToCalendar(tm.Year));
    return NameR;
}
String GetTime()
{
  RTC.read(tm);
  String TimeR = String(tm.Day) + ";" + String(tm.Hour) + ":" + String(tm.Minute) + ";";
  return TimeR;
}
