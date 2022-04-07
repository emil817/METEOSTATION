void loop() {
  BT();
  LCDInformation();
}

void LCDInformation()
{
  static bool flag_on_lcd = false;
  static long last_min = 0;
  static long start_lcd = 0;
  
  if (digitalRead(WakeButton) == HIGH)  // Включение дисплея
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

  if (flag_on_lcd == true)   // Проверка на выключение дисплея и обновление информации на нём
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

void LCD_Data() // Функция вывода информации на дисплей
{
  sensors.requestTemperatures();
  lcd.clear();
  watch.gettime();
  lcd.setCursor(0, 0); print2digits(watch.Hours); lcd.print(':'); print2digits(watch.minutes);
  lcd.print(" "); lcd.print(watch.day); lcd.print('/'); lcd.print(watch.month); lcd.print('/'); lcd.print(watch.gettime("Y"));

  lcd.setCursor(0, 1); lcd.print("Temp:"); lcd.print(int(bme.readTemperature()));lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(12, 1); lcd.print(char(3)); lcd.print(int(sensors.getTempCByIndex(0)));lcd.print(char(1)); lcd.print("C");
  lcd.setCursor(0, 2); lcd.print(char(0)); lcd.print(int(bme.readHumidity())); lcd.setCursor(3, 2); lcd.print(" %");   lcd.setCursor(9, 2); lcd.print(char(2)); lcd.print(int(analogRead(temt6000_pin) * 0.9765625));  lcd.setCursor(13, 2); lcd.print("lux");
  lcd.setCursor(0, 3); lcd.print(char(7)); lcd.print(int((bme.readPressure() / 100.0F) * 0.75)); lcd.setCursor(5, 3); lcd.print("mm"); lcd.setCursor(9, 3); lcd.print(int(mhz19.getPPM())); lcd.setCursor(13, 3); lcd.print("ppm");
}

void BT() 
{
  // Temp;press;temp-outside;Humidity;Light;CO2;

  static bool BlueT_on = false;
  static long start_B = 0;
  static long LtimeBlt = 0;

  if (Serial.available())
  {
    BlueT_on = true;
    start_B = millis();
  }
  if (BlueT_on == true) // Отправление данных по bluetooth
  {
    if (millis() - LtimeBlt > BT_Update_timeMill)
    {
      LtimeBlt = millis();
      String Send_BT = "";
      sensors.requestTemperatures();
      Send_BT = String(bme.readTemperature()) + ";" + String(int((bme.readPressure() / 100.0F) * 0.75)) + ";" + String(sensors.getTempCByIndex(0))  + ";" + String(bme.readHumidity()) + ";" + String(int(analogRead(temt6000_pin) * 0.9765625)) + ";" + String(int(mhz19.getPPM())) + ";";
      Serial.println(Send_BT);
    }
    if (millis() - start_B > BT_ON_timeMill)
    {
      BlueT_on = false;
    }
  }
}
