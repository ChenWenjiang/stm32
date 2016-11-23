#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h"  
  
void TIM3_IRQHandler(void)  
{  
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  
    
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==Bit_RESET)  
  {  
    GPIO_SetBits(GPIOA,GPIO_Pin_2);  
  }else{  
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);  
  }  
}

void EXTI3_IRQHandler(void)
{
    uint16_t i=0;
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        while(i++<5000)
        {
            if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)==Bit_SET)
                goto clear;
        }

        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==Bit_RESET)
        {
            GPIO_SetBits(GPIOA,GPIO_Pin_1);
        }
        else
        {
            GPIO_ResetBits(GPIOA,GPIO_Pin_1);  
        }
    }
clear:    
    EXTI_ClearITPendingBit(EXTI_Line3);
}
