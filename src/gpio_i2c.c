#include "gpio_i2c.h"

void I2C_GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void I2C_Delay(void){
    volatile uint8_t i = 50;
    while(i){
        i--;
    }
}

void delay5ms(void){
    volatile int i = 5000000;
    while(i){
        i--;
    }
}

BOOLEN I2C_Start(void){
    SDA_H;
    SCL_H;
    I2C_Delay();
    if(!SDA_read)
        return FALSE;
    SDA_L;
    I2C_Delay();
    if(SDA_read)
        return FALSE;
    SDA_L;
    I2C_Delay();
    return TRUE;
}

void I2C_Stop(void){
    SCL_L;
    I2C_Delay();
    SDA_L;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SDA_H;
    I2C_Delay();
}

void I2C_Ack(void){
    SCL_L;
    I2C_Delay();
    SDA_L;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SCL_L;
    I2C_Delay();
}

void I2C_NoAck(void){
    SCL_L;
    I2C_Delay();
    SDA_H;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    SCL_L;
    I2C_Delay();
}

BOOLEN I2C_WaitAck(void){
    BOOLEN rv=TRUE;
    SCL_L;
    I2C_Delay();
    SDA_H;
    I2C_Delay();
    SCL_H;
    I2C_Delay();
    if(SDA_read){
        rv = FALSE;
    }
    SCL_L;
    I2C_Delay();
    return rv;
}

void I2C_SendByte(unsigned char SendByte){
    uint8_t i = 8;
    while(i--){
        SCL_L;
        I2C_Delay();
        if(SendByte &0x80)
            SDA_H;
        else
            SDA_L;
        SendByte <<= 1;
        I2C_Delay();
        SCL_H;
        I2C_Delay();
    }
    SCL_L;
}

unsigned char I2C_ReadByte(void){
    uint8_t i = 8;
    unsigned char ReceiveByte = 0;
    SDA_H;
    while(i--){
        ReceiveByte <<=1;
        SCL_L;
        I2C_Delay();
        SCL_H;
        I2C_Delay();
        if(SDA_read)
            ReceiveByte |= 0x01;
    }
    SCL_L;
    return ReceiveByte;
}

uint8_t Single_Write(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data){
    if(!I2C_Start())
        return 1;
    I2C_SendByte((SlaveAddress)&0xfe);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 2;
    }
    I2C_SendByte(REG_Address);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 3;
    }
    I2C_SendByte(REG_data);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 4;
    }
    I2C_Stop();
    delay5ms();
    return 0;
}

uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t * data){
    if(!I2C_Start())
        return 1;
    I2C_SendByte(SlaveAddress&0xfe);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 2;
    }
    I2C_SendByte(REG_Address);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 3;
    }
    I2C_Start();
    I2C_SendByte(SlaveAddress | 0x01);
    if(!I2C_WaitAck()){
        I2C_Stop();
        return 4;
    }
    *data = I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    return 0;
}
    
    

    

