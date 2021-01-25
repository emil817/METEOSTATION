#define lcd_I2C_addres 0x23

#define bme280_I2C_addres 0x76

#define DS18B20_Pin 4
#define DS18B20_Resolution 12

#define SD_CS_pin 10

#define temt6000_pin A2

#define bluetoothTx 8
#define bluetoothRx 7

#define Lcd_ON_time 30  // Время работы дисплея в секундах
#define Lcd_Update_time 3 //Время обновления дисплея в секундах

#define BT_ON_time 60 // Время работы блютуза в секундах
#define BT_Update_time 3 //Время обновления блютуза в секундах

/***********************************************************/
#define Lcd_ON_timeMill (Lcd_ON_time * 1000)
#define Lcd_Update_timeMill (Lcd_Update_time * 1000)
#define BT_ON_timeMill (BT_ON_time * 1000)
#define BT_Update_timeMill (BT_Update_time * 1000)
