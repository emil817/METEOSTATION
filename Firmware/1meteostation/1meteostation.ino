#define lcd_I2C_addres 0x23  // Адрес диплея

#define bme280_I2C_addres 0x76   // Адрес датчика BME280

#define DS18B20_Pin 3  // Пин к которому поключён DS18B20
#define DS18B20_Resolution 12

//#define SD_CS_pin 10

#define temt6000_pin A0   // Пин к которому поключён датчик освещённости


#define RTC_RST 10
#define RTC_DAT 12
#define RTC_CLK 11

#define MHZ_TX 5  // Пины подключения датчика углекислого газа
#define MHZ_RX 4

#define WakeButton 2  // Пин к которому подключена кнопка для включения дисплея

#define Lcd_ON_time 30  // Время работы дисплея в секундах
#define Lcd_Update_time 3 // Время обновления дисплея в секундах

#define BT_ON_time 60 // Время работы блютуза в секундах
#define BT_Update_time 3 // Время обновления блютуза в секундах

/***********************************************************/
#define Lcd_ON_timeMill (Lcd_ON_time * 1000)
#define Lcd_Update_timeMill (Lcd_Update_time * 1000)
#define BT_ON_timeMill (BT_ON_time * 1000)
#define BT_Update_timeMill (BT_Update_time * 1000)
