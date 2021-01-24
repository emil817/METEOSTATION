#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x23, 20, 4);

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;

#include <SPI.h>
#include <SD.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <TimeLib.h>
#include <DS1307RTC.h>
tmElements_t tm;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8);


//#define SEALEVELPRESSURE_HPA (1013.25)


#define temt6000_pin A2

bool flag_on_lcd = 0;
long last_min;
long start_;
long start_B;
long LtimeBlt;
bool BlueT_on = 0;
