#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(lcd_I2C_addres, 20, 4);

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;

//#include <SPI.h>
//#include <SD.h>


#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS DS18B20_Pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <iarduino_RTC.h>
iarduino_RTC watch(RTC_DS1302, RTC_RST, RTC_CLK, RTC_DAT);


//#define SEALEVELPRESSURE_HPA (1013.25)

#include <MHZ19_uart.h>
MHZ19_uart mhz19;
