#ifndef _RS485_CONFIG_H_
#define _RS485_CONFIG_H_
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define RS485_TX_ENABLE (GPIO_ResetBits(GPIOA,GPIO_Pin_10))
#define RS485_RX_ENABLE (GPIO_SetBits(GPIOA,GPIO_Pin_10))
#define RS485_CAN_TX     (!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10))
#define RS485_CAN_RX     (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10))
#define RS485_CAN_NOT_RX     (!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10))
#define RS485_CAN_NOT_TX     (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10))
//void RS485_UART4_Config(void);
//void RS485_GPIO_Config(void);
//void RS485_RCC_Config(void);
//void RS485_NVIC_Config(void);
void RS485_Config(void);
int print(uint8_t * str,int len);
#endif
