void SD_Write()
{
  static byte LMin = 0;
  RTC.read(tm);
  if((tm.Minute == 0 || tm.Minute == 15 || tm.Minute == 30 || tm.Minute == 45) and tm.Minute != LMin)
  {
    String nameF = GetFileName();
    if(!SD.exists(nameF.c_str()))
    {
       File MFile = SD.open(nameF.c_str(), FILE_WRITE);
       MFile.println("Month;Day;Time;Temperature inside;Pressure;Temperature outside;Humidity;Light;");
       MFile.close();
    }
    LMin = tm.Minute;
    File MFile = SD.open(nameF.c_str(), FILE_WRITE);
    String record = GetTime1() + String(bme.readTemperature()) + ";" + String(int((bme.readPressure() / 100.0F) * 0.75)) + ";" + String(sensors.getTempCByIndex(0))  + ";" + String(bme.readHumidity()) + ";" + String(int(analogRead(temt6000_pin) * 0.9765625)) + ";";
    MFile.println(record);
    MFile.close();
  }
}
String GetFileName()
{
    RTC.read(tm);
    String NameR = ("M_" + String(tm.Month) + "," + String(tmYearToCalendar(tm.Year)) + ".csv");
    return NameR;
}
String GetTime1()
{
  RTC.read(tm);
  String TimeR = String(tm.Month) + ";" + String(tm.Day) + ";" + String(tm.Hour) + ":" + String(tm.Minute) + ";";
  return TimeR;
}
