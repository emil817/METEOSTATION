void setup() {
  sensors.begin();
  sensors.setResolution(DS18B20_Resolution);

  byte capla[8] = {0b00000,0b00100,0b01110,0b01110,0b11111,0b11111,0b01110,0b00000};
  byte Press[8] = {0b00100,0b00100,0b10101,0b01110,0b00100,0b00000,0b11111,0b11111};
  byte gradys[8] = {0b00000,0b01100,0b01100,0b00000,0b00000,0b00000,0b00000,0b00000};
  byte SUN[8] = {0b00000,0b00100,0b10001,0b01110,0b01110,0b01110,0b10001,0b00100};
  byte Tem[8] = {0b00100,0b01010,0b01010,0b01010,0b01010,0b10001,0b01010,0b00100};
  
  lcd.begin();  
  lcd.noBacklight();
  lcd.clear();
  lcd.createChar(0, capla);
  lcd.createChar(7, Press);
  lcd.createChar(1, gradys);
  lcd.createChar(2, SUN);
  lcd.createChar(3, Tem);
  delay(3000);

  unsigned statusb;
  statusb = bme.begin(bme280_I2C_addres);
  
  mySerial.begin(9600);

  SD.begin(SD_CS_pin);

  mhz19.begin(MHZ_TX, MHZ_RX);
  mhz19.setAutoCalibration(false);
  mhz19.getStatus();
}
