/**********************************************************

        +------------------------------------------------+
        |   振南电子  USART的发送和接收演示程序 |
        +------------------------------------------------+

  此源码版权属 振南电子 全权享有，如欲引用，敬请署名并告知
        严禁随意用于商业目的，违者必究，后果自负
         振南电子 产品网站 http://www.znmcu.cn/
         论坛     http://bbs.znmcu.cn/
							  
***********************************************************/
#include "stm32f10x_lib.h"



void RCC_Configuration(void);
void NVIC_Configuration(void);
void USART_Config(void);
void USART1_Puts(char * str);//输出字符串
void USART1_Putc(char c);//输出一个字符
unsigned char USART1_ReceiveChar(void);//接收一个字符

char rbuff[100];


int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();
  
       
  /* NVIC configuration */
  NVIC_Configuration();
  USART_Config();
  while(1){}
  
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;
  
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO|RCC_APB2Periph_USART1, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  }
    
}

void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    

    /* Configure USART1_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART1_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //USART工作在异步模式下
    USART_InitStructure.USART_BaudRate = 9600;//波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数据位数
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No ;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送接收均使能
    /* Configure the USARTx */ 
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    /* Enable the USARTx */
    USART_Cmd(USART1, ENABLE);
    
}

void USART1_Putc(char c)
{
    USART_SendData(USART1, c);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void USART1_Puts(char * str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }

}

unsigned char USART1_ReceiveChar(void)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return(USART_ReceiveData(USART1));
}


/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef  NVIC_InitStructure;
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//配置优先级组为第1组（抢占式优先级有1位，副优先级有3位）
  //配置USART中断
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;//中断通道为RTC全局中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//副优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断通道使能
  NVIC_Init(&NVIC_InitStructure);//初始化NVIC结构体
}




