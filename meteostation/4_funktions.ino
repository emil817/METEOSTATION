void LCDInformation()
{
  static bool flag_on_lcd = false;
  static long last_min = 0;
  static long start_lcd = 0;
  
  if (digitalRead(5) == HIGH)
  {
    if (flag_on_lcd == false)
    {
      flag_on_lcd = 1;
      lcd.backlight();
      start_lcd = millis();
      LCD_Data();
      last_min = millis();
    }
    else
    {
      start_lcd = millis();
    }
  }

  if (flag_on_lcd == true)
  {
    if (millis() - last_min > Lcd_Update_timeMill)
    {
      LCD_Data();
      last_min = millis();
    }

    if (millis() - start_lcd > Lcd_ON_timeMill)
    {
      flag_on_lcd = false;
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

  lcd.setCursor(0, 1); lcd.print("Temp: "); lcd.print(int(bme.readTemperature()));lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(12, 1); lcd.print(char(3)); lcd.print(int(sensors.getTempCByIndex(0)));lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(0, 2); lcd.print(char(0)); lcd.print(int(bme.readHumidity())); lcd.setCursor(3, 2); lcd.print(" %");
  lcd.setCursor(2, 3); lcd.print(char(7)); lcd.print(int((bme.readPressure() / 100.0F) * 0.75)); lcd.setCursor(6, 3); lcd.print(" mm");
  lcd.setCursor(9, 2); lcd.print(char(2)); lcd.print(" "); lcd.print(int(analogRead(temt6000_pin) * 0.9765625));  lcd.setCursor(14, 2); lcd.print(" lux");
}

void BT()
{
  //Temp ;press;temp::outside; Humidity;  Light;

  static bool BlueT_on = false;
  static long start_B = 0;
  static long LtimeBlt = 0;
  if (BlueT_on == false)
  {
    if (mySerial.available() != 0)
    {
      BlueT_on = true;
      start_B = millis();
    }
  }
  if (BlueT_on == true)
  {
    if (millis() - LtimeBlt > BT_Update_timeMill)
    {
      LtimeBlt = millis();
      String Send_BT = "";
      sensors.requestTemperatures();
      Send_BT = String(bme.readTemperature()) + ";" + String(int((bme.readPressure() / 100.0F) * 0.75)) + ";" + String(sensors.getTempCByIndex(0))  + ";" + String(bme.readHumidity()) + ";" + String(int(analogRead(temt6000_pin) * 0.9765625)) + ";";
      mySerial.print(Send_BT);
    }
    if (millis() - start_B > BT_ON_timeMill)
    {
      BlueT_on = false;
    }
  }
}
