#ifndef _GPIO_I2C_CONFIG_H_
#define _GPIO_I2C_CONFIG_H_

#include "types.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define SCL_PIN GPIO_Pin_6
#define SDA_PIN GPIO_Pin_7

#define SCL_H GPIO_SetBits(GPIOB,SCL_PIN)
//GPIOB->BSRR = SCL_PIN
#define SCL_L GPIO_ResetBits(GPIOB,SCL_PIN)
//GPIOB->BRR = SCL_PIN

#define SDA_H GPIO_SetBits(GPIOB,SDA_PIN)
//GPIOB->BSRR = SDA_PIN
#define SDA_L GPIO_ResetBits(GPIOB,SDA_PIN)
//GPIOB->BRR = SDA_PIN

#define SCL_read (GPIOB->IDR & SCL_PIN)
//GPIO_ReadOutputDataBit(GPIOB,SCL_PIN)
#define SDA_read (GPIOB->IDR & SDA_PIN)
//GPIO_ReadOutputDataBit(GPIOB,SDA_PIN)
void GPIOI2C_Config(void);
uint8_t Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t* data);
uint8_t Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t * data,int len);
uint8_t Read(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t *data,int len);
#endif
