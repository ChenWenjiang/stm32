#ifndef _OTHER_HW_CONFIG_H_
#define _OTHER_HW_CONFIG_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

#define ALARM_PIN GPIO_Pin_12
#define PRE_ALARM_PIN GPIO_Pin_0

void Other_HW_Config(void);

#define soundAlarm() GPIO_ResetBits(GPIOC,ALARM_PIN)
#define soundPreAlarm() GPIO_ResetBits(GPIOD,PRE_ALARM_PIN)
#define soundAlarmClose() GPIO_SetBits(GPIOC,ALARM_PIN)
#define soundPreAlarmClose() GPIO_SetBits(GPIOD,PRE_ALARM_PIN) 

#endif
