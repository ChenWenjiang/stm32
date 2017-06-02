#include "switch.h"
#include "globalvar.h"

static void Switch_RCC_Config(void){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG,ENABLE);
}

static void Switch_GPIO_Config(void){
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOD,&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOG,&GPIO_InitStructure);
}

void Switch_Config(void){
  Switch_RCC_Config();
  Switch_GPIO_Config();
}


unsigned char Read_Set_LED_Switch(void){
  unsigned char tmp = 0;
  tmp = GPIO_ReadInputData(GPIOD);
  tmp &= 0x3f;
  tmp >>=3;
  return tmp;
}

unsigned char Read_Set_Arg_Switch(void){
  unsigned short tmp = 0;
  tmp = GPIO_ReadInputData(GPIOG);
  tmp >>=10;
  return (unsigned char)(tmp & 0x0f);
}

void setInputNumber(void){
  uint8_t tmp = 0xff;
  tmp = Read_Set_LED_Switch();
  switch(tmp){
    case 0:
      gInputNumber = 12;
      break;
    case 1:
      gInputNumber = 16;
      break;
    case 2:
      gInputNumber = 22;
      break;
    case 3:
      gInputNumber = 24;
      break;
    case 4:
      gInputNumber = 32;
      break;
    default:
      gInputNumber = 32;
  }
}
