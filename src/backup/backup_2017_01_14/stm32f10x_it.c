#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h" 
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
//#include "globalvar.h"


uint8_t uart4_data[10] = "abcdefghi";
void UART4_IRQHandler(void)
{
    static int i = 0;
    if(!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10)){
        USART_ClearITPendingBit(UART4,USART_IT_RXNE);
        goto haha;
    }
    if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
    {
            
        uart4_data[i++] = USART_ReceiveData(UART4);
        if(i==10)
            GPIO_ResetBits(GPIOA,GPIO_Pin_10);
        USART_ClearITPendingBit(UART4,USART_IT_RXNE);
        //buf[ptr++]=USART_ReceiveData(USART3);
    }
haha:   
    if(USART_GetFlagStatus(UART4,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(UART4,USART_FLAG_ORE);
        USART_ReceiveData(UART4);
    }
}

//#include "i2c.h"
/**
  * @brief  This function handles I2C1 Event interrupt request, tx, rx 
  *         buffer and number of bytes will be changed.
  * @param  None
  * @retval None
  */
//
//void I2C1_EV_IRQHandler(void)
//{
//    uint32_t i2cEvent;
//    I2C_param_struct __IO *pI2C_param;
//
//    pI2C_param = ARC_get_I2C_param();
//    i2cEvent = I2C_GetLastEvent(I2C1);
//    
//    switch (i2cEvent)
//    {
//        case I2C_EVENT_MASTER_MODE_SELECT:/* EV5 */
//            if(pI2C_param->I2C_DIRECTION == ARC_I2C_DIRECTION_TX)
//            {
//                I2C_Send7bitAddress(I2C1, pI2C_param->DeviceAddr, I2C_Direction_Transmitter);
//            }
//            else
//            {
//                I2C_Send7bitAddress(I2C1, pI2C_param->DeviceAddr, I2C_Direction_Receiver);
//            }
//            break;
//
//        /* Master Transmitter -------------------------------------------------------*/
//        case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:
//            I2C_SendData(I2C1, pI2C_param->SubAddr);
//            if(pI2C_param->TxNumOfBytes == 0)
//                I2C_ITConfig(I2C1, I2C_IT_BUF, DISABLE);
//            break;
//           
//        case I2C_EVENT_MASTER_BYTE_TRANSMITTING:  /* Without BTF, EV8 */     
//            if(pI2C_param->TX_I2C_Index < pI2C_param->TxNumOfBytes)
//            {
//                I2C_SendData(I2C1, pI2C_param->TxData[pI2C_param->TX_I2C_Index++]);
//            }
//            else 
//            {      
//                I2C_ITConfig(I2C1, I2C_IT_BUF, DISABLE);
//            }
//            break;
//
//        case I2C_EVENT_MASTER_BYTE_TRANSMITTED: /* With BTF EV8-2 */
//           if(pI2C_param->TX_Generate_stop == 1)
//           {
//             I2C_GenerateSTOP(I2C1, ENABLE);
//             I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
//           }
//           else
//           {
//             pI2C_param->I2C_DIRECTION = ARC_I2C_DIRECTION_RX;
//             I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
//             I2C_GenerateSTART(I2C1, ENABLE);
//           }
//           break;
//
//        /* Master Receiver -------------------------------------------------------*/
//        case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
//            if(pI2C_param->RX_I2C_Index == (pI2C_param->RxNumOfBytes - 1))
//            {
//                I2C_AcknowledgeConfig(I2C1, DISABLE);
//                I2C_GenerateSTOP(I2C1, ENABLE);
//            }
//            break;
//
//        case I2C_EVENT_MASTER_BYTE_RECEIVED:
//            pI2C_param->RxData[pI2C_param->RX_I2C_Index++] = I2C_ReceiveData (I2C1);
//            if(pI2C_param->RX_I2C_Index == (pI2C_param->RxNumOfBytes - 1))
//            {
//                I2C_AcknowledgeConfig(I2C1, DISABLE);
//                I2C_GenerateSTOP(I2C1, ENABLE);
//            }
//            break;
//
//        default:
//            break;
//    }
//
//}
//
///**
//  * @brief  This function handles I2C1 Error interrupt request.
//  * @param  None
//  * @retval None
//  */
//void I2C1_ER_IRQHandler(void)
//{
//    uint32_t __IO SR1Register =0;
//
//    /* Read the I2C1 status register */
//    SR1Register = I2C1->SR1;
//    /* If AF = 1 */
//    if ((SR1Register & 0x0400) == 0x0400)
//    {
//        I2C1->SR1 &= 0xFBFF;
//        SR1Register = 0;
//    }
//    /* If ARLO = 1 */
//    if ((SR1Register & 0x0200) == 0x0200)
//    {
//        I2C1->SR1 &= 0xFBFF;
//        SR1Register = 0;
//    }
//    /* If BERR = 1 */
//    if ((SR1Register & 0x0100) == 0x0100)
//    {
//        I2C1->SR1 &= 0xFEFF;
//        SR1Register = 0;
//    }
//    /* If OVR = 1 */
//    if ((SR1Register & 0x0800) == 0x0800)
//    {
//        I2C1->SR1 &= 0xF7FF;
//        SR1Register = 0;
//    }
//}
//

//unsigned char buf[128];
//int ptr=0;
//uint8_t d='a';
//void USART3_IRQHandler(void)
//{
//    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
//    {
//        d = USART_ReceiveData(USART3);
//        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//        //buf[ptr++]=USART_ReceiveData(USART3);
//    }
//    if(USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET)
//    {
//        USART_ClearFlag(USART3,USART_FLAG_ORE);
//        USART_ReceiveData(USART3);
//    }
//}
////1ms定时器，如果连续采样低电平50次，
////则认为已经按下按键。
//void TIM3_IRQHandler(void)  
//{  
//    const uint8_t CNTTIMES = 25;
//    static uint8_t inCnt[INPUTNUM] = {0};
//    uint8_t i = 0;
//    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){
// //input alarm check
//        for(i=0;i<ALARMNUM;i++)
//        {
//            if(GPIO_ReadInputDataBit(gMap[i].addr,
//                        gMap[i].loc) ==Bit_RESET)
//                inCnt[i]++;
//            else
//                inCnt[i]=0;
//
//            if(inCnt[i]>=CNTTIMES)
//            {
//                regs[i+6].val = 1;
//                regs[5].val |= (1<<i);
//            }
//            else
//            {
//                regs[i+6].val = 0;
//                regs[5].val &= (~(1<<i));
//            }
//        }
//        if(regs[5].val!=0)
//            regs[3].val = 1;
//        else
//            regs[3].val = 0;
////button input
//        for(i=ALARMNUM;i<INPUTNUM;i++)
//        {
//            if(GPIO_ReadInputDataBit(gMap[i].addr,gMap[i].loc)==Bit_RESET)
//                inCnt[i]++;
//            else
//                inCnt[i] = 0;
//            if(inCnt[i]>=CNTTIMES)
//                gButtonInputFlag |= (1<<(i-ALARMNUM));
//            else
//                gButtonInputFlag &= (~(1<<(i-ALARMNUM)));
//        } 
//        
//        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//    }
//}
//
////1s定时，芯片正在运行的指示灯，闪烁表示正在运行，不闪烁表示有问题，程序没有运行
//volatile int8_t outputLock;
//uint32_t output1;//低16位
//uint32_t output2;//高16位
//void conv(uint32_t out,uint32_t color){
//    int i = 0;
//    output1 = 0;
//    output2 = 0;
//    for(i=0;i<16;i++){//低16位
//        if(out&(1<<i)){
//            if(color&(1<<i))//red
//                output1 +=(1<<(i<<1)); 
//            else   //yellow
//                output1 +=(2<<(i<<1));
//        }
//    }
//    for(i=0;i<16;i++){//高16位
//        if(out&(1<<(i+16))){
//            if(color&(1<<(16+i)))//red
//                output2 +=(1<<(i<<1));
//            else 
//                output2 +=(2<<(i<<1));
//        }
//    }
///*    int i = 0;
//    output = 0;
//    for(i=0;i<32;i++){
//        if(out&(1<<i)){
//            if(color&(1<<i))//red
//                output += (1<<(i<<1));
//            else
//                output += (2<<(i<<1));
//        }
//    }*/
//}
//uint8_t cnt = 0; //整体计数，0～72，用来控制数据信号
//uint8_t icnt = 1; //内部计数，0～1，用来控制时钟和锁存信号
//void TIM4_IRQHandler(void){
//    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET){
//        if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)!=Bit_RESET){
//            GPIO_ResetBits(GPIOD,GPIO_Pin_2);
//        }else{
//            GPIO_SetBits(GPIOD,GPIO_Pin_2);
//        }
//
//        //USART_SendData(USART3,d);
//        //while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
///*
//        if(outputLock==0){
//            twinkFlag++;
//            twinkFlag %= 2;
//            if(twinkFlag==0){
//   */            /* if(gLight==0)
//                    gLight = 0x80000000;
//                else
//                    gLight >>=1;*/
//     /*           gLight = regs[5].val;
//                gTwink = gLight;
//                out = gLight;
//            }else
//                out =gTwink ^ gLight; 
//            conv(out,gColor);
//            cnt = 0;
//            icnt = 1;
//            outputLock = 1;
//        }*/
//        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//    }
//}
////1ms定时，将LED状态输:出。
//
//#define SETSHIFTCLK      GPIO_SetBits(GPIOE,GPIO_Pin_0)
//#define RESETSHIFTCLK    GPIO_ResetBits(GPIOE,GPIO_Pin_0)
//#define SETSHIFTDAT      GPIO_SetBits(GPIOE,GPIO_Pin_2)
//#define RESETSHIFTDAT    GPIO_ResetBits(GPIOE,GPIO_Pin_2)
//#define SETLATCH         GPIO_SetBits(GPIOE,GPIO_Pin_1)
//#define RESETLATCH       GPIO_ResetBits(GPIOE,GPIO_Pin_1)
//
//void TIM5_IRQHandler(void){
//    uint8_t pwr = 0x4;
//    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET){
//        if(outputLock){
//            if(icnt){   //时钟下降沿,锁存上升沿,数据移位
//                if(cnt==68){
//                    SETLATCH;
//                }else{
//                    RESETLATCH;
//                    if(cnt<4){
//                        if(pwr&(1<<(cnt)))
//                            SETSHIFTDAT;
//                        else
//                            RESETSHIFTDAT;
//                    }else if(cnt<36){
//                        if(output2 & (1<<(35-cnt)))
//                            SETSHIFTDAT;
//                        else
//                            RESETSHIFTDAT;
//                    }else{
//                        if(output1 & (1<<(67-cnt)))
//                            SETSHIFTDAT;
//                        else
//                            RESETSHIFTDAT;       
//                    }   
//              /*      }else{
//                        if((output>>(cnt-4)) & 1)
//                            SETSHIFTDAT;
//                        else
//                            RESETSHIFTDAT;
//                    }*/
//                }
//                RESETSHIFTCLK;
//                if(cnt==69){
//                    cnt=0;
//                }else{
//                    cnt++;
//                }
//                icnt = 0;
//            }else{        //时钟上升沿,锁存下降沿
//                if(cnt==69){
//                    RESETSHIFTCLK;
//                    outputLock = 0;
//                }else{
//                    SETSHIFTCLK;
//                }
//                RESETLATCH;
//                icnt=1;
//            }
//        }
//       TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//清中断
//    }
//}
///*
//#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
//#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
//#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//void TIM6_IRQHandler(void)
//{
//   static int i2cCnt = 0;
//    static int i2cByteCnt = 0;
//
//    int i;
//    if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
//    {
//        //addr
//        if(i2cByteCnt==0)
//        {
//            if(i2cCnt==0)
//            {
//                SETSCL;
//                SETSDA;
//            }
//            else if(i2cCnt==1)    //start 
//            {
//                RESETSDA;
//            }
//            else if(i2cCnt==2)
//            {
//                RESETSCL;
//            } 
//            else if(i2cCnt < 27) //data
//            {
//                if(i2cCnt%3==0)
//                {
//                    i = i2cCnt/3;
//                    RESETSCL;
//                    if(gI2cData[i2cByteCnt] & (1<< (8-i)))  //data
//                        SETSDA;
//                    else
//                        RESETSDA;
//                }
//                else if(i2cCnt%3==1)
//                {
//                    SETSCL;
//                }
//                else //(i2cCnt%3==2)
//                {
//                    RESETSCL;
//                }
//            }
//            else if(i2cCnt==27)
//            {
//                SETSDA;
//                SETSCL;
//            }
//            else if(i2cCnt==28)
//            {
//                gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
//                if(gI2cAck)
//                {
//                    i2cCnt = 29;
//                    i2cByteCnt = gI2cNBytes - 1;
//                    gI2cErr = -2;
//                }
//            }
//            else if(i2cCnt==29)    //ack
//            {
//                RESETSCL;
//                RESETSDA;
//                i2cCnt = -1;
//                i2cByteCnt++;
//            }
//            else if(i2cByteCnt==30)
//            {
//                RESETSCL;
//                RESETSDA;
//            }
//            else if(i2cCnt==31)
//            {
//                SETSCL;
//            }
//            else if(i2cCnt==32)
//            {
//                SETSDA;
//                i2cCnt = -1;
//                i2cByteCnt = 0;
//                //TODO turn off timer
//            }
//        }
//        // 以上是设备地址写入
//        else if(gI2cRW==0)
//        {
//            if(i2cCnt<24) //data
//            {
//                if(i2cCnt%3==0)
//                {
//                    i = i2cCnt/3;
//                    RESETSCL;
//                    if(gI2cData[i2cByteCnt] & (1<< (7-i)))  //data
//                        SETSDA;
//                    else
//                        RESETSDA;
//                }
//                else if(i2cCnt%3==1)
//                {
//                    SETSCL;
//                }
//                else //(i2cCnt%3==2)
//                {
//                    RESETSCL;
//                }
//            }
//            else if(i2cCnt==24)
//            {
//                SETSDA;
//                SETSCL;
//            }
//            else if(i2cCnt==25)
//            {
//                gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
//                if(gI2cAck)
//                {
//                    i2cCnt=26;
//                    i2cByteCnt = gI2cNBytes - 1;
//                    gI2cErr = -3;
//                }
//            }
//            else if(i2cCnt==26)    //ack
//            {
//                RESETSCL;
//                RESETSDA;
//            }
//            else if(i2cCnt==27)
//            {
//                if(i2cByteCnt+1==gI2cNBytes)
//                {
//                    RESETSCL;
//                    RESETSDA;
//                }
//                else
//                {
//                    i2cByteCnt++;
//                    i2cCnt = -1;
//                }
//            }
//            else if(i2cCnt==28)
//            {
//                SETSCL;
//            }
//            else if(i2cCnt==29)
//            {
//                SETSDA;
//                i2cByteCnt = 0;
//                i2cCnt = -1;
//                //TODO turn off timer
//            }
//        }
//        else 
//        {            
//            if(i2cCnt<24) //data
//            {
//                if(i2cCnt%3==0)
//                {
//                    SETSCL;
//                    //GPIO_SetBits(,);//TODO clk
//                }
//                else if(i2cCnt%3==1)
//                {
//                    i = i2cCnt/3;
//                    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
//                        gI2cData[i2cByteCnt] |= (1<<(7-i));
//                    else
//                        gI2cData[i2cByteCnt] &= ~(1<<(7-i));
//                }
//                else
//                {
//                    RESETSCL;
//                }
//            }
//            else if(i2cCnt==24)
//            {
//                if(i2cByteCnt+1==gI2cNBytes)
//                    SETSDA;
//                else
//                    RESETSDA;               //ack
//            }
//            else if(i2cCnt==25)
//            {
//                SETSCL;
//            }
//            else if(i2cCnt==26)
//            {
//                RESETSCL;
//            }
//            else if(i2cCnt==27)
//            {
//                RESETSDA;
//            }
//            else if(i2cCnt==28)
//            {
//                if(i2cByteCnt+1==gI2cNBytes)
//                    SETSCL;
//                else
//                {
//                    i2cByteCnt++;
//                    i2cCnt = -1;
//                }
//            }
//            else if(i2cCnt==29)
//            {
//                SETSDA;
//                i2cByteCnt = 0;
//                i2cCnt = -1;
//                //TODO turn off timer
//            }
//        }
//        i2cCnt++;
//        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//    }
//}*/
