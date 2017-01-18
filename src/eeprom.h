#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "gpioi2c_config.h"

//EEPROM address
#define ALARMHISTORY 0    //0~255 store the history of alarm
#define ALARMNEWEST  256  //256 store the next history of alarm location
#define LEDCOLOR     257  //257~260 store the color of led
#define RS485CONFIG  261  //261 store the cofiguration information of RS485
#define MODBUSADDR   262  //262 store the address of MODBUS
#define ALARMHISTORYNUM 263
uint8_t eeprom_store_history(void);
uint8_t eeprom_load(void);
uint8_t eeprom_store_color(void);
uint8_t eeprom_store_rs485config(void);
uint8_t eeprom_store_modbusaddr(void);
uint8_t eeprom_clear_history(void);

#endif
