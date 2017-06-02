#ifndef _SWITCH_H_
#define _SWITCH_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"


void Switch_Config(void);
unsigned char Read_Set_LED_Switch(void);
unsigned char Read_Set_Arg_Switch(void);

void setInputNumber(void);

#endif
