#include "rtu.h"

static void crc16(uint8_t data,uint16_t* crc)
{
    uint8_t i=0;
    while(i<8)
    {
        *crc ^= ((uint16_t)data);
shift:  *crc >>=1;
        if(*crc&0x0001)
            *crc ^=0xa001;
        else
            goto shift;
        i++;
    }
}

static int address(int addr)
{
    if(addr>=0 && addr <=3)
        return 0;
    else if(addr==0x0010 || addr ==0x0011)
        return 4;
    else if(addr>=0x0100 && addr <= 0x0120)
        return 5;
    else if(addr>=0x0200 && addr <= 0x0220)
        return 38;
    else if(addr>=0x01000 && addr <=0x01002)
        return 71;
    else 
        return -1;
}
//exception code:0x02:非法数据地址  0x03:非法数据  0x10 无权限
//　0x11: 寄存器长度溢出
static void exceptAns(uint8_t func,uint8_t exCode)
{
    uint16_t crc=0xffff;
    txBuf.tail = 0;
    PUTINTOBUF(txBuf,gModbusAddr);
    crc16(gModbusAddr,&crc);
    
    //txBuf[1] = 0x80+func;
    PUTINTOBUF(txBuf,0x80+func);
    crc16(0x80+func,&crc);
    PUTINTOBUF(txBuf,exCode);
    crc16(exCode,&crc);
    PUTINTOBUF(txBuf,(uint8_t)(crc & 0x00ff));
    PUTINTOBUF(txBuf,(uint8_t)((crc>>8) & 0x00ff));
}

static int okToParse(void)
{
    uint16_t regAddr;
    uint16_t regNum;
    int tmp = 0;
    if(rxBuf.tail>=2 && rxBuf.buf[1]==0x03 && rxBuf.tail==8)
        return 1; //OK
    if(rxBuf.tail>=2 && rxBuf.buf[1]==0x10 && rxBuf.tail>=6)
    {
        regAddr = (rxBuf.buf[2]<<8) + rxBuf.buf[3];
        regNum = rxBuf.buf[5];
        tmp = regNum*2;
        if(regAddr<=0x0100 && (regAddr+regNum)>=0x0100)
            tmp += 2;
        else if(regAddr <=0x0200 && (regAddr+regNum)>=0x0200)
            tmp += 2;
        else if(regAddr <=0x0100 && (regAddr+regNum)>=0x0200)
            tmp += 4;
        if(rxBuf.tail == tmp + 8)
            return 1;
    }
    return 0;
}

void parse(void)
{
    int i,j;
    uint8_t func;
    uint8_t highByte;
    uint8_t lowByte;
    uint16_t addr;
    uint16_t length;
    uint16_t crc=0xffff;
    uint16_t crctmp;
    uint16_t crctmp2;
    uint16_t crcin;
    uint32_t regstmp[32];
    uint32_t regVal = 0;
    
    if(!okToParse)
        goto the_end;
    
    rxBuf.head = 0;
    func = GETFROMBUF(rxBuf);
    if(func!=gModbusAddr)
    {
        CLEARBUF(rxBuf);
        goto the_end;
    }
    crc16(func,&crc);
    func = GETFROMBUF(rxBuf);
    if(func!=0x03 && func!=0x10)  //func code wrong!!
    {
        CLEARBUF(rxBuf);
        exceptAns(0x03); //illegal data
        goto tx_int_en;
    }
    crc16(func,&crc);
    crctmp = crc;  //used for 0x03func

    //addr
    highByte = GETFROMBUF(rxBuf);
    crc16(highByte,&crc);
    lowByte = GETFROMBUF(rxBuf);
    crc16(lowByte,&crc);
    addr = highByte;
    addr = (addr<<8) + lowByte;
    //length
    highByte = GETFROMBUF(rxBuf);
    crc16(highByte,&crc);
    lowByte = GETFROMBUF(rxBuf);
    crc16(lowByte,&crc);
    length = highByte;
    length = (length << 8) + lowByte;
    crctmp2 = crc; //used for 0x10func

    if(func == 0x03)
    {
        if(address(addr+length-1)!=address(addr))
        {
            CLEARBUF(rxBuf);
            exceptAns(0x11); //reg length overflow
            goto tx_int_en;
        }
        lowByte = GETFROMBUF(rxBuf);
        highByte = GETFROMBUF(rxBuf);
        crcin = highByte;
        crcin = (crcin<<8) + lowByte;
        if(crc !=crcin)
        {
            CLEARBUF(rxBuf);
            exceptAns(0x03); //illegel data
            goto tx_int_en;
        }
        //answer
        txBuf.tail = 0;
        PUTINTOBUF(txBuf,gModbusAddr);   //modbus addr
        PUTINTOBUF(txBuf,0x03);         //code 
        PUTINTOBUF(txBuf,(uint8_t)((length>>8)&0xff));  //length
        crc16((uint8_t)((length>>8) & 0xff),&crctmp);
        PUTINTOBUF(txBuf,(uint8_t)(length & 0xff));
        crc16((uint8_t)(length&0xff),&crctmp);
        
        j = address(addr);   //reg index
        j = addr - regs[j].addr + j;
        for(i=0;i<length;i++)   //data
        {
            if(j+i == 5 || j+i==38) // 4 Bytes
            {
                highByte = (uint8_t)((regs[j+i].val>>24) & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);

                highByte = (uint8_t)((regs[j+i].val>>16) & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);

                highByte = (uint8_t)((regs[j+i].val>>8) & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
                
                highByte = (uint8_t)(regs[j+i].val & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
            }
            else // 2 Bytes
            {
                highByte = (uint8_t)((regs[j+i].val>>8) & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
                
                highByte = (uint8_t)(regs[j+i].val & 0x00ff);
                PUTINTOBUF(txBuf,highByte);
                crc16(highByte,&crctmp);
            }
        }
        PUTINTOBUF(txBuf,(uint8_t)(crctmp & 0x00ff));    //crc
        PUTINTOBUF(txBuf,(uint8_t)(crctmp>>8)&(0x00ff));
        goto tx_int_en;
    }
    //func == 0x10
    if(func==0x10)
    {
        j = address(addr);
        j = addr - regs[j].addr + j;
        for(i = 0;i<length;i++)   //registers' value
        {
            if(regs[j+i].mod==0) //read only
            {
                CLEARBUF(rxBuf);
                exceptAns(0x10); 
                goto tx_int_en;
            }
            highByte = GETFROMBUF(rxBuf);
            crc16(highByte,&crc);
            lowByte = GETFROMBUF(rxBuf);
            crc16(lowByte,&crc);
            regVal = highByte;
            regVal = (regVal<<8)+lowByte;
            if(regs[j+i].len==4)
            {
                highByte = GETFROMBUF(rxBuf);
                crc16(highByte,&crc);
                lowByte = GETFROMBUF(rxBuf);
                crc16(lowByte,&crc);
                regVal = (regval<<8)+highByte;
                regVal = (regVal<<8)+lowByte;
            }
            regstmp[i] = regVal;
        }
        lowByte = GETFROMBUF(rxBuf);
        highByte = GETFROMBUF(rxBuf);  //crc
        crcin = highByte;
        crcin = (crcin << 8) + lowByte;
        if(crcin!=crc)
        {
            CLEARBUF(rxBuf);
            exceptAns(0x03); //illegel data
            goto tx_int_en;
        }
        //assign value to regs
        for(i=0;i<length;i++)
        {
            regs[j+i] = regstmp[i];
        }
        //answer
        PUTINTOBUF(txBuf,gModbusAddr);
        PUTINTOBUF(txBuf,0x10);
        highByte = (uint8_t)((addr>>8)&0x00ff);
        lowByte = (uint8_t)(addr & 0x00ff);
        PUTINTOBUF(txBuf,highByte);
        PUTINTOBUF(txBuf,lowByte);
        highByte = (uint8_t)((length>>8)&0x00ff);
        lowByte = (uint8_t)(length & 0x00ff);
        PUTINTOBUF(txBuf,highByte);
        PUTINTOBUF(txBuf,lowByte);
        PUTINTOBUF(txBuf,(uint8_t)(crctmp2 &0x00ff));
        PUTINTOBUF(txBuf,(uint8_t)((crctmp2>>8)&0x00ff));
        // TODO reconfig usart and bus address
        //
        //
    }   
tx_int_en:
    //TODO turn on tx interrupt
the_end:
    //nothing here
}

